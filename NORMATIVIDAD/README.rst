TITULOO GRANDE
##################

subtitulo
********

COMENTARIOS
This sample demonstrates how to use the UART serial driver with a simple
echo bot. It reads data from the console and echoes the characters back after
an end of line (return key) is received.

The polling API is used for sending data and the interrupt-driven API
for receiving, so that in theory the thread could do something else
while waiting for incoming data.

By default, the UART peripheral that is normally used for the Zephyr shell
is used, so that almost every board should be supported.
