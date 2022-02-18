#include <stdio.h>
#include <iostream>

int main(){
	static unsigned int var{1};
	
	//сдвиги влево
	printf("var = %d\n\n", var);
	for (unsigned int i=0; i<4; i++){
		var = var << 1; //сдвиг влево на 1 бит означает умножение на 2	
		printf("left shift %d: %d\n", i, var);
	}
	std::cout << std::endl;
	
	//сдвиги вправо
	printf("var = %d\n\n", var);
	for (unsigned int i=0; i<4; i++){
		var = var >> 1; //сдвиг вправо на 1 бит означает деление на 2	
		printf("right shift %d: %d\n", i, var);
	}
	std::cout << std::endl;
	return 0;
}