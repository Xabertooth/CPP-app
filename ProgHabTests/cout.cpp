#include <iostream>

static int a = 0;

template<typename T>
void f(T t){
	static int b = ++a;
	std::cout << a;
	std::cout << b++;
}

int main(int argc, char* argv[]){
	f(27);
	f(634);
	f(.8);
	return 0;
}