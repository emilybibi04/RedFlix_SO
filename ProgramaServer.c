// Proyecto de Sistemas Operativos: RedFlix
// Emily Valarezo Plaza

#include "ProgStreamer.h"
#include "ProgEncoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


// Parámetros
// Número de clientes con el que se puede manejar simultáneamente
#define clienteMax 5

// Este método básicamente gestiona la comunicación que hay con el cliente
void control(int stock) {
    char buffer[1024];
    while (1) {
        // Variable que recibe los datos del cliente e indica si esta conectado o no
        int statusConexion = recv(stock, buffer, 1024, 0);
        if (statusConexion <= 0) {
            printf("El cliente se encuentra desconectado\n");
            break;
        }

        buffer[statusConexion] = '\0';

        // Dependiendo del comando, el servidor enviara el mensaje
        if (strcmp(buffer, "play") == 0) {
            send(stock, "El video se está reproduciendo", strlen("El video se está reproduciendo"), 0);
        } else if (strcmp(buffer, "pause") == 0) {
            send(stock, "El video está pausado", strlen("El video está pausado"), 0);
        } else if (strcmp(buffer, "stop") == 0) {
            send(stock, "El video se ha detenido", strlen("El video se ha detenido"), 0);
        } else if (strncmp(buffer, "bitrate", 7) == 0) {
            // El bitrate es fundamental en la transmisión de video para equilibrar entre calidad de imagen y ancho de banda
            send(stock, "La cantidad de datos (bitrate) ha cambiado", strlen("La cantidad de datos (bitrate) ha cambiado"), 0);
        } else {
            send(stock, "El comando no es válido", strlen("El comando no es válido"), 0);
        }
    }
    close(stock);
}

// Con la función main, se puede hacer las operaciones suficientes para establecer la conexión
int main() {
    int socketPrincipal = socket(AF_INET, SOCK_STREAM, 0);
    if (socketPrincipal < 0) {
        perror("Ocurrió un error al crear el socket principal");
        exit(EXIT_FAILURE);
    }

    // Se configura la dirección del servidor
    struct sockaddr_in serverDirec;
    serverDirec.sin_family = AF_INET;
    serverDirec.sin_addr.s_addr = INADDR_ANY;
    serverDirec.sin_port = htons(8080);

    if (bind(socketPrincipal, (struct sockaddr *)&serverDirec, sizeof(serverDirec)) < 0) {
        perror("Error en bind");
        close(socketPrincipal);
        exit(EXIT_FAILURE);
    }

    listen(socketPrincipal, clienteMax);
    printf("El servidor está escuchando en el puerto 8080\n");

    while (1) {
        // Aceptar conexiones de clientes
        struct sockaddr_in clienteDirec;
        socklen_t clienteDirecTam = sizeof(clienteDirec);
        int socketCliente = accept(socketPrincipal, (struct sockaddr *)&clienteDirec, &clienteDirecTam);

        if (socketCliente < 0) {
            perror("Error en accept");
            continue;
        }

        printf("El cliente se encuentra conectado\n");
        control(socketCliente);
    }

    close(socketPrincipal);
    return 0;
}

