#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main(int argc, char const *argv[])
{
    int bytes_recv, bytes_env, destino;

    if (argc != 2)
    {
        cout << "Debe ingresar: ./servidor <archivo destino>" << endl;
        return -1;
    }


    cout << "Soy servidor" << endl;

    string respuesta ("Recibí mensaje, gracias.");
    string ipAddress ("127.0.0.1");
    int tam = respuesta.length() + 1;
    const char * crespuesta = respuesta.c_str();
    const char * cIpAddress = ipAddress.c_str();


	/**
     * 
     * Si es servidor inicializar con:
     * SocketDatagrama(int puerto), pidiendo el puerto al usuario.
     * Inicializar paquetes datagrama para envío y recibimiento
     */
    SocketDatagrama socket  = SocketDatagrama(PUERTO_SERVIDOR);
    PaqueteDatagrama paquete_recv = PaqueteDatagrama(VOTE_TAM_DATA);

    if((destino = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT,0666)) == -1){
        perror(argv[1]);
        exit(-1);
    }

    while(1)
    {
        bytes_recv = socket.recibe(paquete_recv);

        if (bytes_recv >= 0)
        {
            char * ipRemota = paquete_recv.obtieneDireccion();
            int puertoRemoto = paquete_recv.obtienePuerto();
            cout << "Bytes recibidos: " << bytes_recv << endl;
            cout << "Cliente dijo: " << paquete_recv.obtieneDatos() << endl;
            cout << "Recibido desde ip: " <<  ipRemota << endl;
            cout << "Con puerto: " << puertoRemoto << endl;
            //PaqueteDatagrama paquete_env = PaqueteDatagrama(crespuesta, tam, ipRemota, puertoRemoto);
            //bytes_env = socket.envia(paquete_env);
            write(destino, paquete_recv.obtieneDatos(), sizeof(paquete_recv.obtieneDatos()));
            close(destino);
        }

    }
    
	return 0;
}
