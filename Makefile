compile:
	mkdir -p build && gcc -lcurl main.c easy.c -o build/openai

run:
	tcc -lcurl main.c easy.c -o build/openai && ./build/openai

clean:
	rm -r build

debug:
	mkdir -p build && tcc -lcurl -g main.c easy.c -o build/openai && gdb -ex run build/openai
