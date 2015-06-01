CC=gcc
OBJECTS= face.o file.o tree.o node.o graph.o edge.o tikz.o maintree.o
OBJECTS1= file.o tree.o node.o graph.o edge.o main.o
OBJECTS2=  file.o tree.o node.o graph.o edge.o tikz.o maintikz.o

all : $(OBJECTS)
	$(CC) $(OBJECTS) -o test
	./test
	make latex
	make rand
	evince color.pdf &
	evince schnyderand.pdf &

graf : $(OBJECTS1)
	$(CC) $(OBJECTS1) -o graf

tex :  $(OBJECTS2)
	$(CC) $(OBJECTS2) -o tex

face.o : face.h face.c
	$(CC) -std=c99 -c face.c	

node.o : node.h node.c
	$(CC) -std=c99 -c node.c	

graph.o : graph.c graph.h 
	$(CC) -std=c99 -c graph.c

edge.o : edge.c edge.h 
	$(CC) -std=c99 -c edge.c

file.o : file.c file.h
	$(CC) -std=c99 -c file.c

tree.o : tree.h tree.c
	$(CC) -std=c99 -c tree.c

tikz.o : tikz.h tikz.c
	$(CC) -std=c99 -c tikz.c

main.o : main.c
	$(CC) -std=c99 -c main.c

maintree.o : maintree.c
	$(CC) -std=c99 -c maintree.c

maintikz.o : maintikz.c
	$(CC) -std=c99 -c maintikz.c

latex : graph.tex color.tex
	pdflatex graph.tex
	pdflatex color.tex

rand : rand.tex schnyderand.tex
	pdflatex rand.tex	
	pdflatex schnyderand.tex

clean :
	rm -f *~ *.o *.aux *.log *.out *.nav *.snm *.toc \#*\# test graf *.pdf *.tex
