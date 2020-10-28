all: test

test: runtime/runtime.cpp
	g++ runtime/runtime.cpp -o test

clean:
	rm -f test