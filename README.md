# RedFlix
RedFlix es un sistema básico de streaming de video implementado como parte de un proyecto de Sistemas Operativos. Este programa simula un servicio de transmisión de video con ajuste adaptativo de calidad, soportando comandos básicos como reproducción, pausa, detener y cambio de bitrate.

## Estructura
El sistema está compuesto por tres módulos principales:

| **Módulo**        | **Descripción**        | 
|--------------------|--------------------|
| **Servidor (ProgramaServer.c)**        | Gestiona las conexiones de clientes y recibe comandos. Se comunica con el streamer para manejar los datos del video       | 
| **Streamer (ProgStreamer.c)**        | Responsable de la transmisión de frames de video. Gestiona un buffer de frames para enviar datos a los clientes de manera eficiente        | 
| **Encoder (ProgEncoder.c)**        | Carga y prepara los frames del video en diferentes calidades (bitrate). Admite tres niveles: baja, media y alta calidad       | 

El sistema permite conectar múltiples clientes a un servidor central. Cada cliente puede enviar comandos para controlar la reproducción del video o cambiar el bitrate.

## Compilación

1. Clona este repositorio:
   
   ```
   git clone <URL_DEL_REPOSITORIO>
   cd RedFlix_SO
   ```
3. Usa el archivo Makefile para compilar ambos programas:
   ```
   make
   ```

## Ejecución
1. Iniciar el Servidor
   Ejecuta el servidor antes de iniciar los clientes en una terminal:
   ```
   ./servidor
   ```

2. Iniciar un Cliente
   Ejecuta un cliente en una terminal diferente para conectarte al servidor:
   ```
   ./cliente
   ```

3. Comandos del Cliente
   Desde el cliente, puedes enviar los siguientes comandos al servidor:

   - play: Inicia la reproducción del video.
   - pause: Pausa la reproducción del video.
   - stop: Detiene la reproducción del video y cierra la conexión.
   - bitrate [low|medium|high]: Cambia la calidad del video.

   Por ejemplo, para cambiar el bitrate a alta calidad, escribe:
   ```
   bitrate high
   ```

