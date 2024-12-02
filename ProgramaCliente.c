// Proyecto de Sistemas Operativos: RedFlix
// Emily Valarezo Plaza

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Parámetros
// El puerto al que el cliente se va a conectar
#define puertoServer 8080
// Tamaño que usara el buffer para recibir y enviar datos
#define bufferTam 1024

// Con este método puedo gestionar la interacción entre el cliente y el servidor
void cliente(int s) {
    char buffer[bufferTam];
    int n;
    while (1) {
        //
        printf("¡Bienvenido a RedFlix!\n");
        printf("Escribe un comando (play | stop | pause | bitrate): ");
        fgets(buffer, bufferTam, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        send(s, buffer, strlen(buffer), 0);
        if (strcmp(buffer, "stop") == 0) break;

        n = recv(s, buffer, bufferTam, 0);
        buffer[n] = '\0';
        printf("Servidor: %s\n", buffer);
    }
}

int main() {
    int s1 = socket(AF_INET, SOCK_STREAM, 0);
    if (s1 < 0) {
        perror("Socket error");
        exit(EXIT_FAILURE);
    }

    // Configuración de la dirección del servidor
    struct sockaddr_in serverDirec;
    serverDirec.sin_family = AF_INET;
    serverDirec.sin_port = htons(puertoServer);
    serverDirec.sin_addr.s_addr = INADDR_ANY;

    // Aquí se verifica si se conecto al servidor, en caso contrario, aparecerá un error
    if (connect(s1, (struct sockaddr *)&serverDirec, sizeof(serverDirec)) < 0) {
        perror("Error al conectar");
        exit(EXIT_FAILURE);
    }

    cliente(s1);
    close(s1);
    return 0;
}
