/* 
	Напишите функцию, которая принимает строку "a", содержащую фамилию,
и возвращает позицию, которую займет данная фамилия в сгенерированном
списке всех "слов" в лексикографическом порядке, составленных из букв
этой самой фамилии. Например, в случае с фамилией Turing первым в списке
будет слово GINRTU, а последним UTRNIG.
Для поиска перестановок используется "Алгоритм Нараяны".
Сортировка массива реализована методом "пузырьковая сортировка".	
	Пример входных параметров
a = "Turing"
	
	Ожидается на выходе
598*/

#include <iostream>
#include <algorithm>
#include <ctype.h>

using namespace std;

template<typename T> // вывод последовательности в консоль
void arrOut(T *s, int &n){
	for(int i = 0; i<n; i++) cout << static_cast<char>(s[i]) << ' ';
	cout << endl;
}; 

bool compare(int *a, int *b, int &n){
	for(int i = 0; i<n-1; i++){
		if(a[i] != b[i]) return false;
	}
	return true;
}

void bubbleSort(int data[], int lenD);
void convertSeq(int *s, int i, int j, int &n); // 
int findIndI(int *s, int &n); // нахождение в последовательности элемента который меньше элемента справа от него. ОБХОД МАССИВА С КОНЦА. 
int findIndJ(int *s, int &n, int &ii); // нахождение в последовательности элемента который больше элемента i. ОБХОД МАССИВА С КОНЦА. 
int fac(int x){return x > 1 ? x*fac(x-1) : 1;}
 
int main(){
	std::string s = "Turing";
	int n = s.length();
	
	cout << n << endl;
	cout << fac(n) << endl;
	
	int seq[n], res[n];

	for(int i = 0; s[i]; ++i){
		islower(s[i]) ? s[i] = toupper(s[i]) : s[i];
		seq[i] = static_cast<int>(s[i]);
		res[i] = seq[i];
	}
	
	bubbleSort(seq, n);
	
	arrOut(seq, n);
	
	int result{0};
	for(int i = 1; i < fac(n)-1; i++){
		if(compare(res, seq, n)) result = i;
		arrOut(seq, n);
		int indI = findIndI(seq, n);
		int indJ = findIndJ(seq, n, indI);
		convertSeq(seq, indI, indJ, n);
		cout << i << ' ';
	}	
	cout << endl << result << endl;
	return 0;
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

//Пузырьковая сортировка
void bubbleSort(int data[], int lenD)
{
  int tmp = 0;
  for(int i = 0;i<lenD;i++){
    for(int j = (lenD-1);j>=(i+1);j--){
      if(data[j]<data[j-1]){
        tmp = data[j];
        data[j]=data[j-1];
        data[j-1]=tmp;
      }
    }
  }
}