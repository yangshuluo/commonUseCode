all: Ltest
Ltest: Ltest.o system.o
	g++ Ltest.o system.o -o Ltest -std=c++11 -lpthread -lX11 -levent
Ltest.o:test.cpp
	g++ test.cpp -c -Wall -g -o Ltest.o -std=c++11 -lpthread -lX11 -levent
system.o:system.cpp
	g++ system.cpp -c -Wall -g -o system.o -std=c++11 -lpthread -lX11 -levent

clean:
	rm -rf Ltest *.o
