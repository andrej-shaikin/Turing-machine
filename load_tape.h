cout<<"\n������� ���  �����, ������� ������ �����: ";string tape_namefile;cin>>tape_namefile;
tape_namefile+=".txt";
ifstream fin;
fin.open(tape_namefile);
if(!fin.is_open()){cout<<"�� ������� ����� ���� "<<tape_namefile<<". ��������� ��� ����� � ��������� ������� �����.\n\n\n";system("pause");system("cls");goto menu;}
string side;
while(!fin.eof()){
	getline(fin,side);
lenta.push_back(side);side.erase();}

cout<<"\n����� ������� ���������!\n\n";
	