all: client
	
client: main.o tcp_client.o
	g++ main.o tcp_client.o -o client
main.o: main.cpp
	g++ -c main.cpp
tcp_client.o: tcp_client.cpp
	g++ -c tcp_client.cpp
clean:
	rm -rf *.o client	