//
// Created by yuval on 21/12/2019.
//

#include "ConnectControlClientCommand.h"

int ConnectControlClientCommand::execute(string str) {
    cout << "Connecting to Control Client using this string:     " << str << endl;
    //example --> ("127.0.0.1",5402)
    string ip = str.substr(str.find_first_of('"'), str.find_last_of('"'));
    string port; // need to find port

    //for some reason i cant break the string to a port and an ip -FIX I
    threads[1] = thread(&ConnectControlClientCommand::RunClient, this, "127.0.0.1", 5402);

    while (ClientisConnected == false) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }


}

int ConnectControlClientCommand::RunClient(const char *ip, int PORT) {
//create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    address.sin_port = htons(PORT);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std::cout << "Client is now connected to server" << std::endl;
        ClientisConnected =true;
    }

    //if here we made a connection
    //the server will see if there's a set command for him in queue and if so - he will use it
// string sim = "set "+rudder+" 1\r\n";
    while (true) {  //will replace with a better condition..

        if (!SetCommands.empty()) {
            string command = SetCommands.front();
            int is_sent = send(client_socket, command.c_str(), command.size(), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            } else {

                SetCommands.pop();
                char buffer[1024] = {0};
                int valread = read(client_socket, buffer, 1024);
                std::cout << buffer << std::endl;

            }

        }
        sleep(0.1);
    }
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    close(client_socket);

    return 0;
}