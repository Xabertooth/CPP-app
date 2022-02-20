#include "std_lib_facilities.h"
using namespace std;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TGeneral{
	public:
		ifstream ifs;
		TGeneral(const regex& pat, string file); //0 конструкотор
		void printMap(); // 1
	private:
		void incert(); // 2 Ввод маркировки
		void check_input(); // 3 Проверка корректности ввода
		void mapFiller(); //4 Заполнение карты
		string file; // имя файла
		map<string, string> m; // Карта для хранения данных из файла
		vector<string> v; //вектор для хранения введённых польз. данных
		regex pat;
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//0 Конструктор======================================================
TGeneral::TGeneral(const regex& r, string s)
	:file{s}, pat{r}
{
	ifs.open(file, std::ios::in); 
	if(!ifs.is_open()) error("Fail opened file!");
	TGeneral::mapFiller(); //
	ifs.close();
}

//1 Вывод значений карты в соответствии ключам в векторе=============
void TGeneral::printMap() {
	TGeneral::incert();
	for (string str : v) {
		auto search = m.find(str);
		if (search != m.end()) cout << search->first << ":  " << search->second << std::endl;
	}
}

//2 Ввод маркировки==================================================
void TGeneral::incert(){ // заполнение вектора
	cout << '\n' << '\t'
		<<  "Введите знаки маркировки через пробел, после ввода введите символ '>'" << endl;
	v.clear();
	string s;
	while (1){
		cin >> s;
		if (s[0] == '>' || (v.size() == 7)) break;
		v.push_back(s);
	}
	cout << '\n';
	TGeneral::check_input();
}

//3 Проверка корректности ввода=====================================
void TGeneral::check_input(){
	string sv;
	smatch matches;
	
	for (string s : v) sv += s; //вывод элементов из вектора
	cout << '\n' << sv << '\n' << endl;
	
	if(!regex_match(sv, matches, pat)){//проверка корректности ввода
		cout << "некорректноый ввод!" << endl;
		for (string str : v) {
			auto search = m.find(str);
			if (search == m.end()) cout << "Некорректный элемент " << str << endl;
		}
	}
}

//4 Заполнение карты================================================
void TGeneral::mapFiller(){
	bool flag {true}; //флаг для определения свойства "key"
	string sKey, sValue; //память для хранения ключа и значения
	m.clear(); //очистка карты
	for (string s; getline(ifs, s);) { //получаем строку из файла, кладём её в s
		if (flag) { //если флаг==1, значит строка это ключ 
			sKey = s; //сохраняем её в sKey  
			flag = !flag; //инверсия флага т.к. последующие строки войдут в значение
		}
		else if (s == "---") { //
			flag = !flag;
			sValue += '\n';
			m.insert(make_pair(sKey, sValue)); //если строка равна "---", то заносятся значения sKey и sValue в map
			sValue.clear();
		} 
		else {
			(sValue += s)+= '\n';
		}
	}
}