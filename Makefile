all:
	# $(CC) -o a.out main.c $(OBJECTS)
	gcc -g -o a.out main.c list/list.c vertice/vertice.c apig23.c

clean:
	rm b.out

.PHONY:
	clean
