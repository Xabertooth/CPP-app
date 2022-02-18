#include <iostream>
#include <algorithm>
using namespace std;

void arrOut(int *s, int &n); // вывод последовательности в консоль
void inputSeq(int *s, int &n); // ввод значений последовательности
void convertSeq(int *s, int i, int j, int &n); // 
int findIndI(int *s, int &n); // нахождение в последовательности элемента который меньше элемента справа от него. ОБХОД МАССИВА С КОНЦА. 
int findIndJ(int *s, int &n, int &ii); // нахождение в последовательности элемента который больше элемента i. ОБХОД МАССИВА С КОНЦА. 
int fac(int x){return x > 1 ? x*fac(x-1) : 1;}
 
int main(){
	int n;
	cout << "Insert elements quantity" << endl;
	cin >> n;
	int seq[n];
	inputSeq(seq, n);
	arrOut(seq, n);
	for(int i = 1; i < fac(n); i++){
		int indI = findIndI(seq, n);
		int indJ = findIndJ(seq, n, indI);
		convertSeq(seq, indI, indJ, n);
		arrOut(seq, n);
	}	
	return 0;
}

void inputSeq(int *s, int &n){
	for(int i = 0; i < n; i++){
		cin >> s[i];
	}
}

void arrOut(int *s, int &n){
	for(int i = 0; i<n; i++) cout << s[i];
	cout << endl;
}

int findIndI(int *s, int &n){
	for(int i = n - 2; i>=0; i--){
		if(s[i]<s[i+1]) return i;
	}
	return -1;
}

int findIndJ(int *s, int &n, int &ii){
	for(int i = n - 1; i>=0; i--){
	if(s[i]>s[ii]) return i;
	}
	return -1;
}

void convertSeq(int *s, int i, int j, int &n){
	swap(s[i], s[j]);
	reverse(&s[i+1], &s[n]);
}