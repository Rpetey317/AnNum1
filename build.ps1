# Requiere gcc.exe instalado y que el directorio donde se encuentra esté en PATH
# Disponible en https://winlibs.com/ (Yo usé gcc win64 v12.2.0)

$CFLAGS = echo -g -std=c17
$OUTPUTNAME = echo main.exe
$CFILES = echo src/*.c main.c

gcc.exe $CFLAGS $CFILES -o $OUTPUTNAME -lm