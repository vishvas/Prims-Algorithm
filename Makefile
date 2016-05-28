all: run

run:  prim.out 
	


prim.out: prim.c		
		gcc -o prim.out prim.c

	
clean: prim.c 
	rm prim.out
