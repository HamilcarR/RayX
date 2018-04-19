


RayX : RayX.o BMPexporter.o 
	gcc -o RayX RayX.o BMPexporter.o




BMPexporter.o : BMPexporter.c
	gcc -o BMPexporter.o -c BMPexporter.c -Wall -ansi -pedantic -W




RayX.o : RayX.c BMPexporter.h
	gcc -o RayX.o -c RayX.c -W -Wall -ansi -pedantic
