all:alist

alist: main.o
	g++ main.o -o alist
	
main.o: main.cpp arrayList.hpp linearList.hpp
	g++ -c -o main.o main.cpp

clean:
	rm main.o
