compile:
	mkdir -p build && gcc -lcurl src/*.c -o build/openai

run:
	mkdir -p build && tcc -lcurl src/*.c -o build/openai && ./build/openai

clean:
	rm -r build

debug:
	mkdir -p build && tcc -lcurl -g src/*.c -o build/openai && gdb -ex run build/openai
