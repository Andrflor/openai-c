compile:
	mkdir -p build && gcc -lcurl main.c -o build/openai

run:
	tcc -lcurl -run main.c

clean:
	rm -r build

debug:
	mkdir -p build && tcc -lcurl -g main.c -o build/openai && gdb -ex run build/openai
