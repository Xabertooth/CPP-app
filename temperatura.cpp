/*
Упражнение 5 из главы 10 книги Страуструпа
в основном заключается в разработке функции print_year()
Извиняюсь за крокозябры!
*/

#include "std_lib_facilities.h"
#include <fstream>
//-----------------------------------------
const double not_a_reading = -7777; //êîíñòàíòà äëÿ èíèöèàëèçàöèè çíà÷åíèé òåìïåðàòóðû 
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
struct Day{ //Äåíü
	vector<double> hour {vector<double>(24, not_a_reading)};
};

struct Month{ //Ìåñÿö
	int month {not_a_month}; //[0,11] (ÿíâàðþ ñîîòâåòñòâóåò 0)
	vector<Day> day{32}; // [1,31] ïî îäíîìó âåêòîðó íà äåíü, äëÿ óïðîùåíèÿ êîäà 0é ýëåìåíò íå èñïîëüçóåì
};

struct Year{
	int year; // ãîä ñîñòîèò èç ìåñÿöåâ
	vector<Month> month{12}; //[0,11] íâàðþ ñîîòâåòñòâóåò 0
};

struct Reading{
	int day;
	int hour;
	double temperature;
};
//=============================================

//===1=========================================
void end_of_loop(istream& ist, char term, const string& message){ //ïðîâåðêà, íàõîäèòñÿ ëè ïîòîê â ñîñòîÿíèè fail()
	if(ist.fail()){ //èñïîëüçóåì  term êàê ñèìâîë çàâåðøåíèÿ ââîäà è/èëè ðàçäåëèòåëü
		ist.clear();
		char ch;
		if(ist >> ch && ch == term) return; // âñ¸ õîðîøî
		error(message);
	}
}
//===1==========================================

//---2-READING-----------------------------------------
istream& operator>>(istream& is, Reading& r) // ñ÷èòûâàåì ïîêàçàíèÿ òåìïåðàòóðû èç ïîòîêà is â r
{
// ïðîâåðêà êîððåêòíîñòè ôîðìàòà ( 3 4 5.7 )
	char ch1;
	if(is >> ch1 && ch1 != '('){ // ïðàâèëüíî ëè íà÷èíàåòñÿ ôîðìàò - ( 
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
// ôîðìàò {month feb ...}
// Ñ÷èòûâàåì îáúåêò êëàññà Month èç ïîòîêà is â îáúåêò m
{ 
	char ch = 0;
	if (is >> ch && ch != '{'){
		is.unget();
		is.clear(ios_base::failbit); // îøèáêà ââîäà Month
		return is;
	}
	
	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") error ("Íåâåðíîå íà÷àëî Month");
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
		//error("Íåâåðíûå äàííûå â Month, âñåãî: ", invalids);
		cout << "Íåâåðíûå äàííûå â Month, âñåãî: " << invalids << endl;
		error("error!");
	}
	if(duplicates){
		//error("Ïîâòîðÿþùèåñÿ ïîêàçàíèÿ â Month, âñåãî: ", duplicates);
		cout << "Ïîâòîðÿþùèåñÿ ïîêàçàíèÿ â Month, âñåãî: " << duplicates << endl;
		error("error2!");
	}
	end_of_loop(is, '}', "Íåïðàâèëüíûé êîíåö Month!");
	return is;
}
//---4-MONTH----------------------------------------------

//===5===============================================
bool is_valid(const Reading& r) //ãðóáàÿ ïðîâåðêà
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
	//Ñ÷èòûâàíèå îáúåêòà êëàññà Year èç ïîòîêà is â îáúåêò y
	//Ôîðìàò: { year 1972 ... }
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
		error("Íåïðàâèëüíîå íà÷àëî Year");
	
	y.year = yy;
	while(true){ 	
		Month m; //êàæäûé ðàç ñîçäà¸òñÿ íîâûé îáúåêò m
		if(!(is >> m)) break;      // çäåñü èñïîëüçóåòñÿ îïåðàòîð >> äëÿ Month
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "Íåïðàâèëüíûé êîíåö  Year!");
	return is;
}
//---6-YEAR------------------------------------------------

//===7=================================================
int month_to_int(string s){
	//âëÿåòñÿ ëè s íàçâàíèåì ìåñÿöà, åñëè äà òî âîçâðàùàåì èíäåêñ â äèàïàçîíå [0,11], à â ïðîòèâíîì ñëó÷àå - -1
	for (int i=0; i<12; ++i) if (month_input_tbl[i]==s) return i;
	return -1;
}
//===7=================================================

//===8=================================================
string int_to_month(int i)
{
	if (i<0 || 12<=i) cout << "Íåâåðíûé èíäåêñ ìåñÿöà";
	return month_print_tbl[i];
}
//===8==================================================

//===9==================================================
void print_year(Year &y)
{
	cout << '{' << ' ' << y.year << ' '; // ðàçäåë ÃÎÄ
	
	for (int i = 0;  i < y.month.size(); ++i){
		if (y.month[i].month == not_a_month) continue; // åñëè ìåñÿö = -1 ïðîïóñê èòåðàöèè
		string m = int_to_month(y.month[i].month); //ïðåîáðàçóåì çíà÷åíèå ìåñÿöà â ñòðîêîâûé ôîðìàò
		cout << ' ' << '{' << ' ' << m << ' ' ; //ðàçäåë ÌÅÑßÖ
		
		for (int j = 1; j < y.month[i].day.size(); ++j){
			for (int k = 0; k < y.month[i].day[j].hour.size(); ++k){
				if(y.month[i].day[j].hour[k] == not_a_reading) continue; // åñëè çíà÷åíèå äàííûõ = -7777 ïðîïóñê èòåðàöèè
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
	//îòêðûâàåì ôàéë ââîäà
	cout << "Ââåäèòå èìÿ âõîäíîãî ôàéëà: ";
	string iname;
	cin >> iname;
	ifstream ist {iname};
	if (!ist) error("Íåâîçìîæíî îòêðûòü âõîäíîé ôàéë!");
	
	//ãåíåðàöèÿ èñêëþ÷åíèÿ â ñëó÷àå ñîñòîÿíèÿ bad()
	ist.exceptions(ist.exceptions()|ios_base::badbit);
	
	//Îòêðûâàåì ôàéë âûâîäà
	cout << "Ââåäèòå èìÿ âõîäíîãî ôàéëà: ";
	string oname;
	cin >> oname;
	cout << '\n';
	ofstream ost {oname};
	if (!ost) error ("Íåâîçìîæíî îòêðûòü âûõîäíîé ôàéë!");
	
	//×òåíèå ïðîèçâîëüíîãî êîëè÷åñòâà ëåò:
	vector<Year> ys;
	while (true){
		Year y; // íà êàæäëé èòåðàöèè ïîëó÷àåì âíîâü èíèöèàëèçèðîâàííûé îáúåêò òèïà Year
		if(!(ist >> y)) break;
		ys.push_back(y);
	}
	cout << "Ñ÷èòàíî " << ys.size() << " ãîäè÷íûõ çàïèñåé\n";
	cout << '\n';
	for (Year& y : ys) print_year(y);
	
}
