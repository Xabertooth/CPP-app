#include "std_lib_facilities.h"
#include <fstream>
//-----------------------------------------
const double not_a_reading = -7777; //��������� ��� ������������� �������� ����������� 
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
struct Day{ //����
	vector<double> hour {vector<double>(24, not_a_reading)};
};

struct Month{ //�����
	int month {not_a_month}; //[0,11] (������ ������������� 0)
	vector<Day> day{32}; // [1,31] �� ������ ������� �� ����, ��� ��������� ���� 0� ������� �� ����������
};

struct Year{
	int year; // ��� ������� �� �������
	vector<Month> month{12}; //[0,11] ����� ������������� 0
};

struct Reading{
	int day;
	int hour;
	double temperature;
};
//=============================================

//===1=========================================
void end_of_loop(istream& ist, char term, const string& message){ //��������, ��������� �� ����� � ��������� fail()
	if(ist.fail()){ //����������  term ��� ������ ���������� ����� �/��� �����������
		ist.clear();
		char ch;
		if(ist >> ch && ch == term) return; // �� ������
		error(message);
	}
}
//===1==========================================

//---2-READING-----------------------------------------
istream& operator>>(istream& is, Reading& r) // ��������� ��������� ����������� �� ������ is � r
{
// �������� ������������ ������� ( 3 4 5.7 )
	char ch1;
	if(is >> ch1 && ch1 != '('){ // ��������� �� ���������� ������ - ( 
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
// ������ {month feb ...}
// ��������� ������ ������ Month �� ������ is � ������ m
{ 
	char ch = 0;
	if (is >> ch && ch != '{'){
		is.unget();
		is.clear(ios_base::failbit); // ������ ����� Month
		return is;
	}
	
	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") error ("�������� ������ Month");
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
		//error("�������� ������ � Month, �����: ", invalids);
		cout << "�������� ������ � Month, �����: " << invalids << endl;
		error("error!");
	}
	if(duplicates){
		//error("������������� ��������� � Month, �����: ", duplicates);
		cout << "������������� ��������� � Month, �����: " << duplicates << endl;
		error("error2!");
	}
	end_of_loop(is, '}', "������������ ����� Month!");
	return is;
}
//---4-MONTH----------------------------------------------

//===5===============================================
bool is_valid(const Reading& r) //������ ��������
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
	//���������� ������� ������ Year �� ������ is � ������ y
	//������: { year 1972 ... }
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
		error("������������ ������ Year");
	
	y.year = yy;
	while(true){ 	
		Month m; //������ ��� �������� ����� ������ m
		if(!(is >> m)) break;      // ����� ������������ �������� >> ��� Month
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "������������ �����  Year!");
	return is;
}
//---6-YEAR------------------------------------------------

//===7=================================================
int month_to_int(string s){
	//������� �� s ��������� ������, ���� �� �� ���������� ������ � ��������� [0,11], � � ��������� ������ - -1
	for (int i=0; i<12; ++i) if (month_input_tbl[i]==s) return i;
	return -1;
}
//===7=================================================

//===8=================================================
string int_to_month(int i)
{
	if (i<0 || 12<=i) cout << "�������� ������ ������";
	return month_print_tbl[i];
}
//===8==================================================

//===9==================================================
void print_year(Year &y)
{
	cout << '{' << ' ' << y.year << ' '; // ������ ���
	
	for (int i = 0;  i < y.month.size(); ++i){
		if (y.month[i].month == not_a_month) continue; // ���� ����� = -1 ������� ��������
		string m = int_to_month(y.month[i].month); //����������� �������� ������ � ��������� ������
		cout << ' ' << '{' << ' ' << m << ' ' ; //������ �����
		
		for (int j = 1; j < y.month[i].day.size(); ++j){
			for (int k = 0; k < y.month[i].day[j].hour.size(); ++k){
				if(y.month[i].day[j].hour[k] == not_a_reading) continue; // ���� �������� ������ = -7777 ������� ��������
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
	//��������� ���� �����
	cout << "������� ��� �������� �����: ";
	string iname;
	cin >> iname;
	ifstream ist {iname};
	if (!ist) error("���������� ������� ������� ����!");
	
	//��������� ���������� � ������ ��������� bad()
	ist.exceptions(ist.exceptions()|ios_base::badbit);
	
	//��������� ���� ������
	cout << "������� ��� �������� �����: ";
	string oname;
	cin >> oname;
	cout << '\n';
	ofstream ost {oname};
	if (!ost) error ("���������� ������� �������� ����!");
	
	//������ ������������� ���������� ���:
	vector<Year> ys;
	while (true){
		Year y; // �� ������ �������� �������� ����� ������������������ ������ ���� Year
		if(!(ist >> y)) break;
		ys.push_back(y);
	}
	cout << "������� " << ys.size() << " �������� �������\n";
	cout << '\n';
	for (Year& y : ys) print_year(y);
	
}