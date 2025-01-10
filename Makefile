prog : main.c fonction.c fonction.h
	gcc -o prog main.c fonction.c  
run:
	./prog
clean:
	rm prog 