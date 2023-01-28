compile:
	gcc -lcurl main.c

run:
	tcc -lcurl -run main.c

clean:
	find -name "*.o" -o -name "*.out" | xargs -r rm
