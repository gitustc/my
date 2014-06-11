#!/bin/bash

g++ -g -std=c++11 -Wall                             \
    main.cpp                                        \
    client.cpp                                      \
    ./gui/*.cpp                                     \
    ./sdlib/*.cpp                                   \
    ./package/*.cpp                                 \
    ./process/login/*.cpp                           \
    ./process/*.cpp                                 \
    ./net/*.cpp                                     \
    ../common/*.cpp                                 \
    -o main -lSDL2 -lSDL2_ttf

mv ./main ../../bin/client/main

