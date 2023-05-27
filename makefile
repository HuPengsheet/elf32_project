target := run

target :main.o
	-gcc -g main.o -o  run
	
main.o :main.c
	-gcc -c -g  main.c

clean:
	-rm *.o run