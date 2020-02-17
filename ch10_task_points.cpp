// Задание из главы 10
#include "std_lib_facilities.h"
#include <fstream>

struct Point{
	int x;
	int y;
};

istream& operator>>(istream& is, Point& p)
{
	is >> p.x >> p.y ;
}

void print_point(Point p){
	cout << '\n' << '(' << p.x << ';' << p.y << ')' << '\n';
}

void out_to_file(string oname){
	cout << "Èìÿ ôàéëà äëÿ çàïèñè: " << oname << '\n';
	ofstream ost{oname};
	if(!ost) error("Íåâîçìîæíî îòêðûòü âûõîäíîé ôàéë!");
	
	cout << "Ââåäèòå ñåìü ïàð çíà÷åíèé x, y!" << '\n';
	Point pnt;
	vector<Point> original_points(0);
	for (int i = 0; i<6; ++i){
		cout << "Ïàðà çíà÷åíèé " << i+1 << ':' << '\t';
		cin >> pnt;
		original_points.push_back(pnt);
	}
	
	for(Point p : original_points) 
		print_point(p);	
	
	for(Point p : original_points) 
		ost << '(' << p.x << ';' << p.y << ")\n";
}

void in_from_file(string iname){
	cout << "Èìÿ ôàéëà äëÿ ÷òåíèÿ: " << iname << '\n';
	ifstream ist{iname};
	if(!ist) error("Íåâîçìîæíî îòêðûòü âõîäíîé ôàéë!");
	
	vector<Point>processed_points(0);
	
	Point p;
	char ch1, ch2, ch3;
	while(ist){
		ist >> ch1 >> p.x >> ch2 >> p.y >> ch3;
		processed_points.push_back(p);
	}
	
	for(Point p : processed_points) 
		print_point(p);		
}

int main(){
	out_to_file("mydata.txt");
	in_from_file("mydata.txt");
	
}
