all: cliente servidor
cliente: cliente.cpp SocketDatagrama.o PaqueteDatagrama.o
	g++ cliente.cpp SocketDatagrama.o PaqueteDatagrama.o -o cliente
servidor: servidor.cpp SocketDatagrama.o PaqueteDatagrama.o
	g++ servidor.cpp SocketDatagrama.o PaqueteDatagrama.o -o servidor
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h mensaje.h PaqueteDatagrama.o
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
	