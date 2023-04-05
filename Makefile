all:
	# $(CC) -o a.out main.c $(OBJECTS)
	gcc -g -Wall -Wextra -std=c99 -O3  main.c list.c vertice.c apig23.c

clean:
	rm b.out

.PHONY:
	clean
