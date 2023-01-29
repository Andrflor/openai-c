compile:
	mkdir -p build && gcc -lcurl src/main.c src/easy.c -o build/openai

run:
	tcc -lcurl src/main.c src/easy.c -o build/openai && ./build/openai

clean:
	rm -r build

debug:
	mkdir -p build && tcc -lcurl -g src/main.c src/easy.c -o build/openai && gdb -ex run build/openai
