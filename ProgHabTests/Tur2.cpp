#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

int permutations(string a);
int findIndI(vector<char> &v);

int findIndJ(vector<char> &v, int &indI); // нахождение в последовательности элемента который больше элемента i. ОБХОД МАССИВА С КОНЦА. 

int main(){
	
	string s = "Turing";
	int result = permutations(s);
	cout << result << endl;
	
	return 0;
}

int permutations(string a){
	vector<char> v, vTmp;
	for(auto i = a.begin(); i<a.end(); i++){
		if(islower(*i)){ *i = toupper(*i);}
		v.push_back(*i);
		vTmp = v;
	}
	sort(v.begin(), v.end());
	
	int res{-1}, indexI, indexJ;
	do{
		res++;
		indexI = findIndI(v);
		cout << indexI << endl;//11111111111111
	
		indexJ = findIndJ(v, indexI);
		cout << indexJ << endl;//1111111111111
	
		swap(v[indexI], v[indexJ]);
		for (auto i : v) cout << i; //1111111111
		cout << endl; //1111111111
	
		reverse(v.begin()+indexI+1, v.end());
		for (auto i : v) cout << i; //1111111111
		cout << endl; //1111111111
	}while(res != 582);
	return res;
};

int findIndI(vector<char> &v){; // нахождение в последовательности элемента который меньше элемента справа от него. ОБХОД МАССИВА С КОНЦА. 
	for(int i = v.size()-2; i > 0; i--){
		if(v[i]<v[i+1]) return i;
	}
	return  -1;
}

int findIndJ(vector<char> &v, int &indI){
	for(int i = v.size()-1; i > 0; i--){
		if(v[i] > indI) return i;
	}
	return  -1;
}