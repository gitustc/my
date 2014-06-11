#!/bin/bash

g++ -std=c++11 *.cpp ../common/*.cpp ../../common/*.cpp -lpthread -o main -I /usr/local/include/mariadb/ -L /usr/local/lib/mariadb/ -lmysqlclient
cp ./main ../../../bin/server/gate/main
