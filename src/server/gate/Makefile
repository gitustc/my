CC		=	g++ -g -std=c++11 -Wall -I /usr/local/include/mariadb -L /usr/local/lib/mariadb
OBJS    =   db.o main.o server.o session.o message.o
LIBS    =   -lmysqlclient

all: $(OBJS)
	$(CC) $(OBJS) $(LIBS)
	mv ./a.out ../../../bin/server/gate/main
db.o: ../common/db.cpp ../common/db.hpp
	$(CC) ../common/db.cpp -c
main.o: main.cpp
	$(CC) main.cpp -c
server.o: server.cpp server.hpp
	$(CC) server.cpp -c
session.o: session.cpp session.hpp
	$(CC) session.cpp -c
message.o: ../../common/message.cpp ../../common/message.hpp
	$(CC) ../../common/message.cpp -c
