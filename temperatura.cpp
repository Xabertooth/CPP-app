#include "std_lib_facilities.h"
#include <fstream>
//-----------------------------------------
const double not_a_reading = -7777; //константа для инициализации значений температуры 
const int not_a_month = -1; 
constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

vector<string> month_input_tbl = {
	"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "okt", "nov", "dec"
};

vector<string> month_print_tbl = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};
//-------------------------------------------

//===========================================
struct Day{ //День
	vector<double> hour {vector<double>(24, not_a_reading)};
};

struct Month{ //Месяц
	int month {not_a_month}; //[0,11] (январю соответствует 0)
	vector<Day> day{32}; // [1,31] по одному вектору на день, для упрощения кода 0й элемент не используем
};

struct Year{
	int year; // год состоит из месяцев
	vector<Month> month{12}; //[0,11] нварю соответствует 0
};

struct Reading{
	int day;
	int hour;
	double temperature;
};
//=============================================

//===1=========================================
void end_of_loop(istream& ist, char term, const string& message){ //проверка, находится ли поток в состоянии fail()
	if(ist.fail()){ //используем  term как символ завершения ввода и/или разделитель
		ist.clear();
		char ch;
		if(ist >> ch && ch == term) return; // всё хорошо
		error(message);
	}
}
//===1==========================================

//---2-READING-----------------------------------------
istream& operator>>(istream& is, Reading& r) // считываем показания температуры из потока is в r
{
// проверка корректности формата ( 3 4 5.7 )
	char ch1;
	if(is >> ch1 && ch1 != '('){ // правильно ли начинается формат - ( 
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	
	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')') error("Bad write"); // ;Uncorrect write!
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}
//---2-READING------------------------------------------

bool is_valid(const Reading& r);
int month_to_int(string s);

//---4-MONTH------------------------------------------
istream& operator>>(istream& is, Month& m)
// формат {month feb ...}
// Считываем объект класса Month из потока is в объект m
{ 
	char ch = 0;
	if (is >> ch && ch != '{'){
		is.unget();
		is.clear(ios_base::failbit); // ошибка ввода Month
		return is;
	}
	
	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") error ("Неверное начало Month");
	m.month = month_to_int(mm);
	//cout << mm << '\n';
	
	Reading r;
	int duplicates = 0;
	int invalids =0;
	for(Reading r; is >> r;){
		if (is_valid(r)){	
			if(m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		} 
		else
			++invalids;		
	}
	if(invalids){
		//error("Неверные данные в Month, всего: ", invalids);
		cout << "Неверные данные в Month, всего: " << invalids << endl;
		error("error!");
	}
	if(duplicates){
		//error("Повторяющиеся показания в Month, всего: ", duplicates);
		cout << "Повторяющиеся показания в Month, всего: " << duplicates << endl;
		error("error2!");
	}
	end_of_loop(is, '}', "Неправильный конец Month!");
	return is;
}
//---4-MONTH----------------------------------------------

//===5===============================================
bool is_valid(const Reading& r) //грубая проверка
{
	if (r.day<1 || 31<r.day) return false;
	if (r.hour<0 || 23<r.hour) return false;
	if (r.temperature < implausible_min || implausible_max < r.temperature)
		return false;
	return true;
}
//===5================================================

//---6-YEAR-----------------------------------------------
istream& operator>>(istream& is, Year& y)
	//Считывание объекта класса Year из потока is в объект y
	//Формат: { year 1972 ... }
{
	char ch;
	is >> ch;
	if (ch!='{'){
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	
	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year")
		error("Неправильное начало Year");
	
	y.year = yy;
	while(true){ 	
		Month m; //каждый раз создаётся новый объект m
		if(!(is >> m)) break;      // здесь используется оператор >> для Month
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "Неправильный конец  Year!");
	return is;
}
//---6-YEAR------------------------------------------------

//===7=================================================
int month_to_int(string s){
	//вляется ли s названием месяца, если да то возвращаем индекс в диапазоне [0,11], а в противном случае - -1
	for (int i=0; i<12; ++i) if (month_input_tbl[i]==s) return i;
	return -1;
}
//===7=================================================

//===8=================================================
string int_to_month(int i)
{
	if (i<0 || 12<=i) cout << "Неверный индекс месяца";
	return month_print_tbl[i];
}
//===8==================================================

//===9==================================================
void print_year(Year &y)
{
	cout << '{' << ' ' << y.year << ' '; // раздел ГОД
	
	for (int i = 0;  i < y.month.size(); ++i){
		if (y.month[i].month == not_a_month) continue; // если месяц = -1 пропуск итерации
		string m = int_to_month(y.month[i].month); //преобразуем значение месяца в строковый формат
		cout << ' ' << '{' << ' ' << m << ' ' ; //раздел МЕСЯЦ
		
		for (int j = 1; j < y.month[i].day.size(); ++j){
			for (int k = 0; k < y.month[i].day[j].hour.size(); ++k){
				if(y.month[i].day[j].hour[k] == not_a_reading) continue; // если значение данных = -7777 пропуск итерации
				cout << '(' << j << ' ' << k << ' ' << y.month[i].day[j].hour[k];
				if (k == (y.month[i].day[j].hour.size()-1)) cout << '}';
				cout << ')' << ' ';
			}
		}
		cout << '}' << ' ';
	}
	cout << '}' << '\n' << endl;
}	
//===9===================================================

int main(){	
	//открываем файл ввода
	cout << "Введите имя входного файла: ";
	string iname;
	cin >> iname;
	ifstream ist {iname};
	if (!ist) error("Невозможно открыть входной файл!");
	
	//генерация исключения в случае состояния bad()
	ist.exceptions(ist.exceptions()|ios_base::badbit);
	
	//Открываем файл вывода
	cout << "Введите имя входного файла: ";
	string oname;
	cin >> oname;
	cout << '\n';
	ofstream ost {oname};
	if (!ost) error ("Невозможно открыть выходной файл!");
	
	//Чтение произвольного количества лет:
	vector<Year> ys;
	while (true){
		Year y; // на каждлй итерации получаем вновь инициализированный объект типа Year
		if(!(ist >> y)) break;
		ys.push_back(y);
	}
	cout << "Считано " << ys.size() << " годичных записей\n";
	cout << '\n';
	for (Year& y : ys) print_year(y);
	
}