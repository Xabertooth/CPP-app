#include <iostream>

int main(){
	int i = 13, j = 60;
	i^=j;
	j^=i;
	i^=j;
	
	std::cout << i << " " << j << std::endl;
	
	return 0;
}