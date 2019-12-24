//
// Created by yuval on 21/12/2019.
//

#include <cstring>
#include <sstream>
#include "OpenDataServerCommand.h"
#include "globals.h"

double *convertToDoubleArray(char *buffer) {
    string valuesAsString(buffer);
    double valuesInDouble[36];
    // stringstream class check1
    stringstream check1(valuesAsString);
    string value;

    // Tokenizing
    int i = 0;
    while (getline(check1, value, ',')) {
        valuesInDouble[i] = atof(value.c_str());
        i++;
    }

    return valuesInDouble;

}

int OpenDataServerCommand::execute(string str) {
    cout << "opening data server using this string:     " << str << endl;
    int port = atoi(str.substr(1, str.find_first_of(")") - 1).c_str());
    cout << port << endl;
    threads[0] = thread(&OpenDataServerCommand::RunServer, this, port);


}

int OpenDataServerCommand::RunServer(int PORT) {
    PORT = 5404;
    string *XML_Array = makeXmlArray();
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
    }

    close(socketfd); //closing the listening socket

    //reading from client
    char buffer[500] = {0};
    int i = 0;
    double *values;
    while (i < 8) {
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
        i++;
        sleep(0.5);

    }


    return 0;


}


//this is some hard-coded stuff : each address belongs to a certain object - as determined by the XML file
string *OpenDataServerCommand::makeXmlArray() {
    string XML_Array[36];
    XML_Array[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    XML_Array[1] = "/sim/time/warp";
    XML_Array[2] = "/controls/switches/magnetos";
    XML_Array[3] = "/instrumentation/heading-indicator/offset-deg";
    XML_Array[4] = "/instrumentation/altimeter/indicated-altitude-ft";
    XML_Array[5] = "/instrumentation/altimeter/pressure-alt-ft";
    XML_Array[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    XML_Array[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    XML_Array[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    XML_Array[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
    XML_Array[10] = "/instrumentation/encoder/indicated-altitude-ft";
    XML_Array[11] = "/instrumentation/encoder/pressure-alt-ft";
    XML_Array[12] = "/instrumentation/gps/indicated-altitude-ft";
    XML_Array[13] = "/instrumentation/gps/indicated-ground-speed-kt";
    XML_Array[14] = "/instrumentation/gps/indicated-vertical-speed";
    XML_Array[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
    XML_Array[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    XML_Array[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    XML_Array[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
    XML_Array[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    XML_Array[20] = "/controls/flight/aileron";
    XML_Array[21] = "/controls/flight/elevator";
    XML_Array[22] = "/controls/flight/rudder";
    XML_Array[23] = "/controls/flight/flaps";
    XML_Array[24] = "/controls/engines/engine/throttle";
    XML_Array[25] = "/controls/engines/current-engine/throttle";
    XML_Array[26] = "/controls/switches/master-avionics";
    XML_Array[27] = "/controls/switches/starter";
    XML_Array[28] = "/engines/active-engine/auto-start";
    XML_Array[29] = "/controls/flight/speedbrake";
    XML_Array[30] = "/sim/model/c172p/brake-parking";
    XML_Array[31] = "/controls/engines/engine/primer";
    XML_Array[32] = "/controls/engines/current-engine/mixture";
    XML_Array[33] = "/controls/switches/master-bat";
    XML_Array[34] = "/controls/switches/master-alt";
    XML_Array[35] = "/engines/engine/rpm";
    return XML_Array;
}
