#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char const *argv[])
{
    int origen, nbytes, bytes_env;
    char buffer[VOTE_TAM_DATA];

    if (argc != 3)
    {
    	cout << "Debe ingresar: ./cliente <IP servidor> <archivo leído>" << endl;
    	return -1;
    }

    char ipRemota[50], nombreArchivo[50];
    strcpy(ipRemota, argv[1]);
    strcpy(nombreArchivo, argv[2]);
    
    SocketDatagrama socket  = SocketDatagrama(0);

    if((origen = open(argv[2], O_RDONLY,0666)) == -1){
        perror(argv[2]);
        exit(-1);
    }

    nbytes = read(origen, buffer, sizeof buffer);

    if (nbytes > 0)
    {
        PaqueteDatagrama paquete_env = PaqueteDatagrama(buffer, sizeof(buffer), ipRemota, PUERTO_SERVIDOR);
        bytes_env = socket.envia(paquete_env);

        if (bytes_env < 0)
        {
            perror("Fallo en envio");
            exit(1);
        } else {
            cout << "Éxito en envío, " << bytes_env << " bytes enviados." << endl;
        }
    }

    close(origen);

	return 0;
}
