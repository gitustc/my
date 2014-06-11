CC		=	g++ -g -std=c++11 -Wall
LIBS	=	-lSDL2 -lSDL2_ttf
OBJS    =	main.o client.o button.o inputbox.o manager.o pwdbox.o widget.o net.o imagehandler.o imagepackage.o package.o login.o process.o bitmap.o event.o font.o graphics.o sdlib.o surface.o texture.o message.o

all:$(OBJS)
	$(CC) $(OBJS) $(LIBS)
	mv ./a.out ../../bin/client/main
clean:
	rm *.o -f
main.o: main.cpp
	$(CC) main.cpp -c
client.o: client.cpp client.hpp
	$(CC) client.cpp -c
button.o: gui/button.cpp gui/button.hpp gui/gui.hpp
	$(CC) gui/button.cpp -c
inputbox.o: gui/inputbox.cpp gui/inputbox.hpp gui/gui.hpp
	$(CC) gui/inputbox.cpp -c
manager.o: gui/manager.cpp gui/manager.hpp gui/gui.hpp
	$(CC) gui/manager.cpp -c
pwdbox.o: gui/pwdbox.cpp gui/pwdbox.hpp gui/gui.hpp
	$(CC) gui/pwdbox.cpp -c
widget.o: gui/widget.cpp gui/widget.hpp gui/gui.hpp
	$(CC) gui/widget.cpp -c
net.o: net/net.cpp net/net.hpp
	$(CC) net/net.cpp -c
imagehandler.o: package/imagehandler.cpp package/imagehandler.hpp
	$(CC) package/imagehandler.cpp -c
imagepackage.o: package/imagepackage.cpp package/imagepackage.hpp
	$(CC) package/imagepackage.cpp -c
package.o: package/package.cpp package/package.hpp
	$(CC) package/package.cpp -c
login.o: process/login/login.cpp process/login/login.hpp
	$(CC) process/login/login.cpp -c
process.o: process/process.cpp process/process.hpp
	$(CC) process/process.cpp -c
bitmap.o: sdlib/bitmap.cpp sdlib/bitmap.hpp
	$(CC) sdlib/bitmap.cpp -c
event.o:sdlib/event.cpp sdlib/event.hpp
	$(CC) sdlib/event.cpp -c
font.o: sdlib/font.cpp sdlib/font.hpp
	$(CC) sdlib/font.cpp -c
graphics.o: sdlib/graphics.cpp sdlib/graphics.hpp
	$(CC) sdlib/graphics.cpp -c
sdlib.o: sdlib/sdlib.cpp sdlib/sdlib.hpp
	$(CC) sdlib/sdlib.cpp -c
surface.o: sdlib/surface.cpp sdlib/surface.hpp
	$(CC) sdlib/surface.cpp -c
texture.o: sdlib/texture.cpp sdlib/texture.hpp
	$(CC) sdlib/texture.cpp -c
message.o: ../common/message.cpp ../common/message.hpp
	$(CC) ../common/message.cpp -c
