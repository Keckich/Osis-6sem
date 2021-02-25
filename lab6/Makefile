UDP = udp
TCP = tcp
SERVER = server
EXE = exe

.PHONY: all clean

all: clean $(EXE) $(UDP) $(TCP) $(SERVER)
	    

clean:
		rm -rf $(EXE)
$(UDP):
		g++ -o $(EXE)/$(UDP) client_udp.cpp
$(TCP):
		g++ -o $(EXE)/$(TCP) client_tcp.cpp
		
main.o: main.cpp
		g++ -c -o $(EXE)/main.o main.cpp
server.o: server.cpp
		g++ -c -o $(EXE)/server.o server.cpp
daemon.o: daemon.cpp
		g++ -c -o $(EXE)/daemon.o daemon.cpp
		
$(SERVER): exe main.o server.o daemon.o
		g++ -o $(EXE)/$(SERVER) $(EXE)/main.o $(EXE)/server.o $(EXE)/daemon.o
$(EXE):
		mkdir $(EXE)
