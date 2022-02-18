/*
Функция, которая принимает число n и выводит таблицу размером n * n, 
заполненную числами от 1 до n^2 по спирали, выходящей из левого верхнего угла
и закрученной по часовой стрелке.

Пример входных парамертров:
n = 5

Пример выходных параметров:
1  2  3  4  5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
*/

#include <vector>
#include <iostream>

using namespace std;
/*
vector<vector<int>> Snake (int n){
   vector<vector<int>> vv; //вектор векторов
   vector<int> vInt(n,0); //заполнитель
	for (int i = 0; i < n; ++i){
		cout << '\n';
		for(auto itB = vInt.begin(); itB < vInt.end(); ++itB){
			++*itB;
			cout << &itB << endl;
		}
		vv.push_back(vInt);
	}
	
	return vv;
}
*/
void snake(int n){
int var{0}, i{0}, j{-1};
int k = n/2+1;
int max = n;
int min = 0;
int arr[n][n] = {0};
	if (n%2==0){
		arr[n/2][(n/2)-1] = n*n;
	} 
	else{	
			arr[n/2][(n/2)] = n*n;
		}
	while(k>0){
		for (; j < max-1; ++j) arr [i][j] = var++; // >
		//cout << i << ' ' << j << endl;
	
		for (; i < max-1; ++i) arr[i][j] = var++; // v
		//cout << i << ' ' << j << endl;
	
		for (; j > min; --j) arr[i][j] = var++; // <
		//cout << i << ' ' << j << endl;
	
		for (; i > min+1; --i) arr[i][j] = var++; // ^
		//cout << i << ' ' << j << endl;
		++min;
		--max;
		--k;
	}
	//-------------------------------------------------------------
	for (int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cout << '|' << arr[i][j] << '|';
		}
		cout << endl;
	}
}

int main (int argc, char* argv[])
{
	//snake(9);
	
	if (argc > 1){
		int arg = atoi(argv[1]);
		snake(arg);
	}
	else{
			cout << "Not arguments" << endl;
		}
	system("pause");
	
	return 0;
}