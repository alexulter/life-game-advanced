run: index.o partZhenya.o graphics.o
	gcc index.o partZhenya.o -o run `pkg-config --cflags --libs libglade-2.0` 
index.o: index.c
	gcc index.c -c -o index.o
partZhenya.o: partZhenya.c
	gcc partZhenya.c -c -o partZhenya.o
graphics.o: graphics.c
	gcc graphics.c -c -o graphics.o 



