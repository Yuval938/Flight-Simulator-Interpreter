//
// Created by yuval on 21/12/2019.
//

#include <sstream>
#include "OpenDataServerCommand.h"
#include "globals.h"
#include "ex1.h"
#include "ex1.cpp"
/*
 * convertToDoubleArray will transform a char* buffer to a vector<double>
 * this func will make sure the vector<double> has 36 values. if the first line in the buffer has less than 36 values,
 * we can assume that the line is not a "full" line of values, therefore we will use the following line.
 */
vector<double> convertToDoubleArray(char *buffer) {
    string valuesAsString(buffer);
    vector<double> valuesInDouble;
    string line = valuesAsString.substr(0,valuesAsString.find_first_of('\n'));
    size_t commaNum = std::count(line.begin(), line.end(), ',');
    if(commaNum!=35){            //if there are less than 35 commas we know that the line from the buffer is not "full"
       line = "";                //we will use the following line (starts when the first \n appears until the next \n
        for(int k=0;k<1024;k++){
            if(buffer[k]=='\n'){
                k++;
                while(buffer[k]!='\n'){
                    line+=buffer[k];
                    k++;
                }
                break;
            }
        }
    }

     //now we are certain we have a "full line" , we will separate each value and insert it to the vector
    string::size_type i = 0;
    string::size_type j = line.find(',');

    while (j != string::npos) {
        valuesInDouble.push_back(atof(line.substr(i, j - i).c_str()));
        i = ++j;
        j = line.find(',', j);

        if (j == string::npos)
            valuesInDouble.push_back(atof(line.substr(i, line.length()).c_str()));
    }

    return valuesInDouble;

}
/*
 * execute command in this object will break down the string to an int (port) , the port is calculated
 * via Interpreter (that we made in HW1) in order to treat expressions like 5000+400 (instead of 5400)
 * after that execute() will open a new thread and will run RunServer() on that thread.
 */
int OpenDataServerCommand::execute(string str) {
    cout << "opening data server using this string:     " << str << endl;
    string portStr = str.substr(1, str.find_first_of(")") - 1);
    Interpreter *i = new Interpreter();
    int port = (i->interpret(portStr))->calculate();
    cout << port << endl;
    threads[0] = thread(&OpenDataServerCommand::RunServer, this, port);

    while (isConnected == false) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }


}
/*
 * RunServer() will open a server and will wait for the FlightGear Simulator to connect.
 * way of operation:
 * -opens a server and waits for a request to connect from the Simulator
 * -once the Simulator is connected,the server will receive stats from it (as determined in the generic_small.xml file)
 * -the server will update the values in the map that are corresponding with the input we receive from the Simulator.
 */
int OpenDataServerCommand::RunServer(int PORT) {
    vector<string> XML_Array = makeXmlArray();
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(PORT);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    sockaddr_in ClientAddress;
    int client_socket = accept(socketfd, (struct sockaddr *) &ClientAddress,
                               (socklen_t *) &ClientAddress);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    } else {
        cout << "accepted" << endl;
        isConnected = true;
    }

    close(socketfd); //closing the listening socket

    //reading from client
    char buffer[1024] = {0};
    int i = 0;
    vector<double> values;
    while (!endOfFile) {
        int valread = read(client_socket, buffer, 1024);
        values = convertToDoubleArray(buffer);
        // need to check if this part is still good
        for (int j = 0; j < 36; j++) {
            map<string, Var>::iterator it = SymbolTable.begin();
            for (map<string, Var>::iterator it = SymbolTable.begin(); it != SymbolTable.end(); it++) {
                if (it->second.getType().compare("get") != 0) {
                    //if the var is not <- we will skip him
                    continue;
                } else if (it->second.getSim().compare(XML_Array[j]) == 0) {
                    //found a match
                    it->second.setValue(values[j]);
                    break;
                }
            }

        }
    }


    return 0;


}


//this is some hard-coded stuff : each address belongs to a certain object - as determined by the XML file
vector<string> OpenDataServerCommand::makeXmlArray() {
    vector<string> pString;
    pString.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    pString.push_back("/sim/time/warp");
    pString.push_back("/controls/switches/magnetos");
    pString.push_back("/instrumentation/heading-indicator/offset-deg");
    pString.push_back("/instrumentation/altimeter/indicated-altitude-ft");
    pString.push_back("/instrumentation/altimeter/pressure-alt-ft");
    pString.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    pString.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    pString.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    pString.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
    pString.push_back("/instrumentation/encoder/indicated-altitude-ft");
    pString.push_back("/instrumentation/encoder/pressure-alt-ft");
    pString.push_back("/instrumentation/gps/indicated-altitude-ft");
    pString.push_back("/instrumentation/gps/indicated-ground-speed-kt");
    pString.push_back("/instrumentation/gps/indicated-vertical-speed");
    pString.push_back("/instrumentation/heading-indicator/indicated-heading-deg)");
    pString.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    pString.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    pString.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    pString.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    pString.push_back("/controls/flight/aileron");
    pString.push_back("/controls/flight/elevator");
    pString.push_back("/controls/flight/rudder");
    pString.push_back("/controls/flight/flaps");
    pString.push_back("/controls/engines/engine/throttle");
    pString.push_back("/controls/engines/current-engine/throttle");
    pString.push_back("/controls/switches/master-avionics");
    pString.push_back("/controls/switches/starter");
    pString.push_back("/engines/active-engine/auto-start");
    pString.push_back("/controls/flight/speedbrake");
    pString.push_back("/sim/model/c172p/brake-parking");
    pString.push_back("/controls/engines/engine/primer");
    pString.push_back("/controls/engines/current-engine/mixture");
    pString.push_back("/controls/switches/master-bat");
    pString.push_back("/controls/switches/master-alt");
    pString.push_back("/engines/engine/rpm");
    return pString;

}
