#include "TGeneralClass.h"
//======================================================
void IPRating(){
	
}
//======================================================
void fireAreas(){
	
}
//главное меню======================================================
int invite(){ //Функция приглашения выбрать пункт
	int choice{0};
	cout << '\n' << "Введите y!" << '\n' << endl // тут буква ‚ - это английскаЯ Bb
		<< "1 - взрывозащита" << endl
		<< "2 - пыле-влагостойкость" << endl
		<< "3 - УХЛ" << endl
		<< "4 - классификаци пож.опасных зон" << endl
		<< "5 - классы и группы взрывоопасных смесей" << endl
		<< "0 - выход" << '\n' << endl;
	cin >> choice;
	if (choice < 0 || choice > 3) error("отсутствует пункт" + ' ' + choice + '!');
	return choice;
}	
//======================================================
int main(){
	system("chcp 1251");
	
	static const regex Ex_pntr {R"([0-2]Ex[deimnopqs][abcxyzACLR]?\[?i?[abc]?\]?(I|II)[ABC]?T[1-6](X|U)?)"}; //Шаблон ввода для Ex
	static const regex Ip_pntr{ R"(IP[0-6][0-8]:)" }; //Шаблон ввода для IP
	static const regex UHL_pntr{ R"([УХТОМВ][ЛХ]?[Л]?[1-5])"}; //Шаблон для УХЛ
	static const regex fireAreas_pntr{ R"([УХТОМВ][ЛХ]?[Л]?[1-5])" }; //Шаблон для УХЛ
	static const regex UHL_pntr{ R"([УХТОМВ][ЛХ]?[Л]?[1-5])" }; //Шаблон для УХЛ

	TGeneral* genVar;

	while(1){
		int cho = invite();
		switch (cho){
			case 1:
				cout << '\n' << '\t' << "Explosion protection" << endl;
				genVar = new TGeneral(Ex_pntr, "Ex_file.txt");
				genVar->printMap();
				delete genVar;
				break;
			case 2:
				cout << '\n' << '\t' << "Ingress Protection Rating (сокращенно IP)" << '\n'
					<< "Примечание: после ввода второй цифры введите двоеточие (пример IP 6 8: >)" << endl;
				genVar = new TGeneral(Ip_pntr, "Ip_file.txt");
				genVar->printMap();
				delete genVar;
				break;
			case 3:
				cout << '\n' << '\t' << "UHL" << endl;
				genVar = new TGeneral(UHL_pntr, "UHL_file.txt");
				genVar->printMap();
				delete genVar;
				break;
			case 4:
				cout << '\n' << '\t' << "UHL" << endl;
				genVar = new TGeneral(fireAreas_pntr, "UHL_file.txt");
				genVar->printMap();
				delete genVar; 
				break;
			case 5:
				cout << '\n' << '\t' << "UHL" << endl;
				genVar = new TGeneral(UHL_pntr, "UHL_file.txt");
				genVar->printMap();
				delete genVar;
				break;
			default:
				cout << '\n' << '\t' << "Goodbye!" << std::endl;
				Sleep(1300);
				return 0;
				break;
		}
	}
	return 0;
}