all: test

test: runtime/runtime.cpp
	g++ -DUNIT runtime/runtime.cpp -o test

clean:
	rm -f test

# You can use `./test /usr/bin/bc` to test this project