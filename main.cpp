#include "arrayList.hpp"

int main()
{
	arrayList<char> a(10);
	for(char i = 'a'; i < a.capacity() + 'a'; ++i) {
		a.push_back(i);
	}
	a.output(std::cout);
	std::cout << '\n' << a.size() << " " << a.capacity() << std::endl;
	a.setSize(5);
	a.output(std::cout);
	std::cout << '\n' << a.size() << " " << a.capacity() << std::endl;
	a.setSize(15);
	a.output(std::cout);
	std::cout << '\n' << a.size() << " " << a.capacity() << std::endl;
	a.push_back('z');
	a.output(std::cout);
	std::cout << '\n' << a.size() << " " << a.capacity() << std::endl;
	a.trimToSize();
	a.output(std::cout);
	std::cout << '\n' << a.size() << " " << a.capacity() << std::endl;
	a.reserve(20);
	a.output(std::cout);
	std::cout << '\n' << a.size() << " " << a.capacity() << std::endl;
}
