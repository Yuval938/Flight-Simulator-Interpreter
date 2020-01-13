cmake_minimum_required(VERSION 3.15)
project(untitled13)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(untitled13 main.cpp globals.cpp globals.h DefineVarCommand.cpp DefineVarCommand.h OpenDataServerCommand.cpp OpenDataServerCommand.h ConnectControlClientCommand.cpp ConnectControlClientCommand.h WhileCommand.cpp WhileCommand.h SleepCommand.cpp SleepCommand.h PrintCommand.cpp PrintCommand.h IfCommand.cpp IfCommand.h ex1.cpp ex1.h Command.h Command.cpp ConditionParser.cpp ConditionParser.h)