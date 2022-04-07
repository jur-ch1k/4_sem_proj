my_lib.o: my_lib.cpp my_lib.h
	g++ -c my_lib.cpp -o my_lib.o
res: main.cpp my_lib.o
	g++ main.cpp my_lib.o -o res
run: res
	./res
