all: db
	
db: main.o db.o
	g++ main.o db.o -o db -L/usr/include/mysql -lmysqlclient
main.o: main.cpp
	g++ -c main.cpp
db.o: db.cpp
	g++ -c db.cpp -L/usr/include/mysql -lmysqlclient

	
clean:
	rm -rf *.o server