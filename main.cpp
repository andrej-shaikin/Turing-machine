#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <ctime>
#include <set>
using namespace std;


vector<string>lenta;
vector<string>sostoyaniy;

bool step_ = false;
int start_pos=0;
int step=1;

//возвращает часть от исходной строки что нужно и на что(до -> и после него)
string def_name(string src){
	string side;
	for(int i=0;i<src.find("->");i++) 
		side+=src[i];
	return side;}

string def_val(string src){
	string side;
	for(int i=src.find('->')+1;i<src.size();i++) 
		side+=src[i];
	return side;}

//возвращает состояния слева и справа
string def_name_state(string src){
	string side;
	for(int i=0;src[i]!='|';i++)
		side+=src[i];
	return side;}

string def_val_state(string src){
	string side;
	int p=src.find("->")+2;
	for(int i=p;src[i]!='|';i++) 
		side+=src[i];
	return side;}

//возвращает значение что вместо чего будет записано
string def_name_znac(string src){
	string side;
	int p=0,a=0;
	for(int i=0;i<src.size();i++){
		if(src[i]=='|'){
			p=i+1;break;}
	}
	for(int i=p;i<src.size();i++){
		if(src[i]=='|') {
			a=i;break;}
	}
	for(int i=p;i<a;i++) 
		side+=src[i];
	return side;}

string def_val_znac(string src){
	string side;
	int p=0,a=0;
	for(int i=src.find("->")+3;i<src.size();i++){
		if(src[i]=='|') {
			p=i+1;break;}
	}
	for(int i=p;src[i]!='|';i++) 
		side+=src[i];
	return side;}

//в какую сторону перейти
string turn(string src){
	string side;
	int p=0,a=0;
	for(int i=src.find("->")+3;i<src.size();i++){
		if(src[i]=='|') {
			p=i+1;break;}
	}
	for(int i=p;;i++){
		if(src[i]=='|') {
			a=i+1;break;}
	}
	for(int i=a;src[i]!='|';i++) 
		side+=src[i];
	return side;}

bool check_alph(vector<string>&lent,vector<string>&sost){
	set<char>alph_lenta;
	set<char>alph_sost;
	
	for(int i=0;i<lent.size();i++){
		for(int j=0;j<lent[i].size();j++){
			alph_lenta.insert(lent[i][j]);
		}
	}

	for(int i=0;i<sost.size();i++){
		for(int j=0;j<sost[i].size();j++){
	if(sost[i][j]!='*' && sost[i][j]!='-' && sost[i][j]!='>' && sost[i][j]!='|' && sost[i][j]!='q'){
			if(sost[i][j-1]!='q' && sost[i][j]!='E'&&sost[i][j]!='e'&&sost[i][j]!='R'&&sost[i][j]!='r'&&sost[i][j]!='L'&&sost[i][j]!='l')
			alph_sost.insert(sost[i][j]);}
		}
	}
	set<char>::iterator t;

	t=alph_lenta.begin();
	cout<<"Алфавит ленты: ";
	while(t!=alph_lenta.end()){
		cout<<*t<<"";
		++t;
	}
	cout<<"\nАлфавит состояний: ";
	t=alph_sost.begin();
	while(t!=alph_sost.end()){
		cout<<*t<<"";
		++t;
	}cout<<endl;
	if(alph_lenta==alph_sost) {cout<<"Алфавит ленты и состояний СОВПАДАЮТ !\n\n";return 1;}
	else {cout<<"Алфавит ленты и состояний НЕ совпадает !\n";return 0;}
}

int selectStartPos(string word){
	int pos=0;
	men:
	string mes="Выберите ячейку слова,с которой нужно начать выполнение программы.\nПо умолчанию берется крайняя правая ячейка справа.\n";
	mes+="В данном слове ( "+word+" ), по умолчанию будет взята "+to_string(word.size()-1)+"-я ячейка "+word[word.size()-1]+".\n\n";
	cout<<mes;
	cout<<"Symbol\tNumber"<<endl;
	
	for(int i=0;i<word.size();i++) 
		cout<<word[i]<<"\t[ "<<i<<" ]\n";
	
	cout<<endl<<"\n\nВыберите действие:\n";
	cout<<"1 ) Выбрать ячейку ; \n";
	cout<<"2 ) Выбрать ячейку по умолчанию ; \n";
	cout<<"\nВыбор: ";
	string vote;cin>>vote;
	int vot=atoi(vote.c_str());
	if(vot==2){
		return word.size()-1;}
	else if(vot==1){
r:
	cout<<endl<<"Введите номер ячейки: ";string h;cin>>h;pos=atoi(h.c_str());
	if(pos<word.size()) return pos;
	else{cout<<"\nВы ввели номер ячейки, который не входит в данное слово.\nПопробуйте снова.\n\n";system("pause");system("cls");goto r;}}
	else{cout<<"\nВы ввели номер операции, которой нет.\nПопробуйте снова.\n\n";system("pause");system("cls");goto men;}	

}


void show_sost(){
	cout<<endl;
	for(int i=0;i<sostoyaniy.size();i++){
		string k=sostoyaniy[i];
		if(sostoyaniy[i].find('/')!=-1) {
			k.erase(k.find('/'),1);
			sostoyaniy[i]=k;
			cout<<sostoyaniy[i]<<endl;
			cout<<endl;
		}
		else cout<<sostoyaniy[i]<<endl;
	}
}

void run_algor(string &word,ofstream &log){
	string side=word;
	string star="****";
	side.insert(0,star);
	side+=star;
	start_pos=selectStartPos(word)+4;
	int beg = start_pos;
	log<<"Исходное слово: "<<word<<"\n\n";
	log<<"\tАлгоритм запущен\n\n";
	vector<string>::iterator iter=sostoyaniy.begin();
run:
	while(iter!=sostoyaniy.end()){
		string algor=*iter;
		string name=def_name(algor);
		string val=def_val(algor);

		string name_znac=def_name_znac(name);
		string val_znac=def_val_znac(val);

		string name_state=def_name_state(name);
		string val_state=def_val_state(val);

		string turw=turn(val);

		char a=name_znac[0];
		char b=side[start_pos];
		if(a==b){
			string sk="[";
			string ks="]";
			string SIDE=side;
		int qqw=start_pos;

			SIDE.insert(qqw,sk);
			SIDE.insert(qqw+1+val_znac.size(),ks);
			if(step_){
				log<<"Текущее состояние: "<<name_state<<" ; \n";
				log<<"Cледующее состояние: "<<val_state<<" ;\n";
				log<<"Направление: "<<turw<<" ; \n\n";}
			if(step_) {
			for(int i=0;i<SIDE.size();i++){
				if(i==qqw) {log<<name_state<<endl;break;}
				if(i+1==qqw){
					if(turw=="L" || turw=="l") log<<"<-";
					if(turw=="R" || turw=="r") log<<"->";
					if(turw=="E" || turw=="e") log<<"^";}
				else log<<" ";}
			log<<step<<" ) "<<SIDE<<"  -> ";
			cout<<step<<" ) "<<SIDE<<"  -> "; 	}
			side.replace(start_pos,name_znac.size(),val_znac);
			
			SIDE=side;
			qqw=start_pos;
			SIDE.insert(qqw,sk);
			SIDE.insert(qqw+1+name_znac.size(),ks);
			if(step_) {cout<<SIDE<<endl;
			log<<SIDE<<endl<<endl;}

			if(turw=="L" || turw=="l") start_pos--;
			if(turw=="E" || turw=="e") start_pos=start_pos;
			if(turw=="R" || turw=="r") start_pos++;
			
			vector<string>::iterator it=sostoyaniy.begin();
			while(it!=sostoyaniy.end()){
				string r=*it;

				string nam=def_name(r);
				string nam_state=def_name_state(nam);
				string nam_znac=def_name_znac(r);

				string vale=def_val(r);
				string vale_state=def_val_state(vale);
				char a=side[start_pos];
				char b=nam_znac[0];
				if( (val_state==nam_state) && (b==a)) {
					iter=sostoyaniy.begin();
					advance(iter,distance(sostoyaniy.begin(),it));step++;goto run;}
				++it;
			}
		}
			if(step>120) {cout<<"Машина зациклилась. Алгоритм неверный!\nError!\n........\n";break;}
			if(val_state=="q0") break;
		++iter;}
	word=side;
}


int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitleA("Машина Тьюринга");
	ofstream log("log.ini");
	bool load_tape = false, load_sostoayn = false;

menu:
	cout<<"Выберите действие\n";
	cout<<"1 ) Загрузить ленту ; \n";
	cout<<"2 ) Загрузить состояния ; \n";
	cout<<"3 ) Запустить машину ;\n\n";
	cout<<"Выбор: ";int vote;string kin;cin>>kin;
	vote=atoi(kin.c_str());
	//загрузка ленты
	if(vote==1){
#include "load_tape.h"
		load_tape =true;cout<<endl;system("pause");system("cls");goto menu;
	}
	//загрузка состояний
	if(vote==2){
#include "load_sost.h"
		load_sostoayn=true;cout<<endl;system("pause");system("cls");goto menu;
	}

	if((!load_sostoayn || !load_tape) && vote == 3){
		if(!load_sostoayn) {cout<<"\nСостояние не загружены.\nПожалуйста загрузите состояния и попробуйте заново.\n\n";}
		if(!load_tape) {cout<<"\nЛента не загружена.\nПожалуйста загрузите ленту и попробуйте заново.\n\n";}
		system("pause");system("cls");goto menu;}

	if(load_sostoayn && load_tape && vote==3){
		cout<<endl;system("pause");system("cls");
		if(check_alph(lenta,sostoyaniy)==0){cout<<"\nМашина будет остановлена !\n";system("pause");exit(0);}
		cout<<"Показать шаги выполнения: (1/0) ? ";string g;cin>>g;vote=atoi(g.c_str());
		if(vote==1) step_=true;
		else step_=false;
		system("cls");int pol=0;
		for(int i=0;i<lenta.size();i++){
			string in_time=lenta[i];
			if(step_) cout<<"\tШаги выполнения\n\n";
			cout<<"\n\tCостояния\n";
			show_sost();
			cout<<endl;

			double beg_time=clock();
			cout<<endl;
			run_algor(lenta[i],log);

			double end_time=clock();

			cout<<"\nИсходное слово: "<<in_time<<endl;
			cout<<"Переработонное слово: ";//lenta[i]<<endl;}
			for(int g=0;g<lenta[i].size();g++){
				if(lenta[i][g]=='*') continue;
				else cout<<lenta[i][g];}
			string l="Затраченное время: ";
			cout<<"\nЗатраченное время: \n\t\t   "<<(end_time-beg_time)/1000<<" секунд\n";
			for(int i=0;i<l.size();i++) cout<<" ";
			cout<<(end_time-beg_time)<<" миллисекунд\n";
				;//из миллисекунд делаем секунду
			cout<<"Алгоритм выполнен за: "<<step;
			if(step==1) cout<<" шаг ";
			else if(2<=step && step<5) cout<<" шага ";
			else cout<<" шагов ";
			cout<<"\n\n";
			step=0;pol=0;
		system("pause");system("cls");}
		cout<<"\n\nЗапустить программу заново ? (1/0) ";
		string kin;cin>>kin;vote=atoi(kin.c_str());
		if(vote==1){
			cout<<endl<<endl;system("pause");system("cls");
			sostoyaniy.clear();
			lenta.clear();
			goto menu;
		}
	}
cout<<"\n\n";system("pause");}