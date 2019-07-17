#Brendon Henrique de Paula da Silva
#Grr 20170203

CFLAGS = -Wall 

objs: wavinfo wavrev wavwide wavvol wavautovol wavcat wavmix wavecho
all: $(objs)

wavinfo:	opensound.o	linhasdecomando.o	wavinfo.o
	gcc opensound.o linhasdecomando.o wavinfo.o -o wavinfo $(CFLAGS)

opensound.o:	opensound.c opensound.h
	gcc -c opensound.c $(CFLAGS)
linhasdecomando.o:	linhasdecomando.c	linhasdecomando.h	
	gcc -c linhasdecomando.c opensound.c $(CFLAGS)

wavinfo.o:	wavinfo.c
	gcc -c wavinfo.c $(CFLAGS)

wavrev:	opensound.o	linhasdecomando.o	wavrev.o
	gcc opensound.o linhasdecomando.o wavrev.o -o wavrev $(CFLAGS)

wavrev.o:	wavrev.c
	gcc -c wavrev.c $(CFLAGS)

wavvol:	opensound.o	linhasdecomando.o	wavvol.o
	gcc opensound.o linhasdecomando.o wavvol.o -o wavvol $(CFLAGS)

wavvol.o:	wavvol.c
	gcc -c wavvol.c $(CFLAGS)

wavautovol:	opensound.o	linhasdecomando.o	wavautovol.o
	gcc opensound.o linhasdecomando.o wavautovol.o -o wavautovol $(CFLAGS)

wavautovol.o:	wavautovol.c
	gcc -c wavautovol.c $(CFLAGS)

wavwide:	opensound.o	linhasdecomando.o	wavwide.o
	gcc opensound.o linhasdecomando.o wavwide.o -o wavwide $(CFLAGS)

wavwide.o:	wavwide.c
	gcc -c wavwide.c $(CFLAGS)

wavcat:	opensound.o	linhasdecomando.o	wavcat.o
	gcc opensound.o linhasdecomando.o wavcat.o -o wavcat $(CFLAGS)

wavcat.o:	wavcat.c
	gcc -c wavcat.c $(CFLAGS)

wavmix:	opensound.o	linhasdecomando.o	wavmix.o
	gcc opensound.o linhasdecomando.o wavmix.o -o wavmix $(CFLAGS)
wavmix.o:	wavmix.c
	gcc -c wavmix.c $(CFLAGS)

wavecho:	opensound.o	linhasdecomando.o	wavecho.o
	gcc opensound.o linhasdecomando.o wavecho.o -o wavecho $(CFLAGS)

wavecho.o:	wavecho.c
	gcc -c wavecho.c $(CFLAGS)




clean:	
	-rm -rf *.o

purge: clean
	-rm wavinfo wavrev wavwide wavvol wavautovol wavcat wavmix wavecho
	
