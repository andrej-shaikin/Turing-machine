cout<<"\nВведите имя  файла, который хранит состояния: ";string tape_namefile;cin>>tape_namefile;
tape_namefile+=".txt";
ifstream fin;
fin.open(tape_namefile);
if(!fin.is_open()){cout<<"Не удалось найти файл "<<tape_namefile<<". Проверьте имя файла и повторите попытку позже.\n\n\n";system("pause");system("cls");goto menu;}
string side;
while(!fin.eof()){
	getline(fin,side);
	if(side.size()!=0) sostoyaniy.push_back(side);side.erase();}

cout<<"\nСостояния успешно загружены!\n\n";
	