/*
Напишите функцию, которая принимает одно целое число n, а возвращает “ступенчатую” матрицу, состоящую из n этажей.
Этажи нумеруются с первого, ширина каждой ступеньки равна одной строке или столбцу.

Пример входных парамертров:
n = 4

Пример выходных параметров:
1 1 1 1 1 1 1
1 2 2 2 2 2 1
1 2 3 3 3 2 1
1 2 3 4 3 2 1
1 2 3 3 3 2 1
1 2 2 2 2 2 1
1 1 1 1 1 1 1
*/

#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> Ziggurat (int n){
   vector<vector<int>> vv; //вектор векторов
   vector<int> vInt(n*2-1, 0); //заполнитель

	for(int i = 0; i < n; ++i){
		for(auto it = vInt.begin()+i; it < vInt.end()-i; ++it){
			++*it;
		}
		vv.push_back(vInt);
	}
	
	auto vv2 = vv;
	for (auto j = vv.end()-2; j >= vv.begin(); j--){
		vv2.push_back(*j);
	}
	
	for (auto vMain : vv2){
		for (auto v : vMain) cout << v;
		cout << '\n';
	}
	cout << vv2.max_size() << endl
		<< vv2.size();
	
	return vv2;
}

int main ()
{
	Ziggurat (4);
   return 0;
}