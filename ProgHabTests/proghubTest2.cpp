#include <iostream>

int main(){
	int arr[] = {1,2,3};
	for(int &i:arr) i = 99;
	for(int i = 0; i<3; i++) std::cout << arr[i] << '\t';
}