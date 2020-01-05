# Flight Simulator Interpreter
This Project interprets a text file into a code that run's FlightGear simulator.
this program will run in multithreaded application:
- main theard reads the text file and interprets it
- second thread connect's to the simulator as a server and receives data from the air craft in real time (the data is pre-determined by a generic xml file)
- third thread will connect to the simulator as a client and will send commands to the aircraft as desired


### Prerequisites

[FlightGear](https://www.flightgear.org/download/) (Flight Simulator): Version 2019.1.1

Versions c++14 and below are allowed for the project

### Installing
1.Clone the project:

```bash
git clone https://github.com/Yuval938/flight-ex3.git
```

2.Install FlightGear:
after the installation make sure you have a generic file so the simulator will know
what information to send to our server.
(the xml file should be placed in "./FlightGear/protocol/")


3.Compiling:

```bash
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o FGinterpreter.out -pthread
```

### Running the application:
1.You should first run the application with the desired text file (we used fly.txt):

```bash
./a.out text_file.txt
```

2.Run FlightGear:

insert the following commands in FlightGear settings:

```bash
--telnet=socket,in,10,127.0.0.1,5402,tcp=8080
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
```


## Authors

* **Roy Waldman**
* **Yuval Cohen**



