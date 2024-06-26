#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <algorithm>

int login();

void gotoxy(int x, int y) {
    y--;
    static HANDLE h = NULL;
    if (!h) {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

#define CLS() system("cls")

void delay(unsigned int secs) {
    time_t goal = secs + clock();
    while (goal > clock());
}

#define FLBSTUD "student.txt"
#define FLBCLAS "class.txt"
#define RULE(x) cout << '\n';
#define CL(cl, x) cl == 0 ? 1 : cl == x

using namespace std;

int strcmpi(const char* s1, const char* s2) {
    return strcasecmp(s1, s2);
}

bool strcmpis(pair<string, int> s1, pair<string, int> s2) {
    return (strcasecmp(s1.first.c_str(), s2.first.c_str())) < 0;
}

void load() {
    CLS();
    cout << "\n\n\n\n\t\t\t\t  Loading\n\n";
    for (int i = 0; i < 80; i++) {
        cout << "!";
        gotoxy(i, 3);
        cout << "!";
        cout.flush();
        gotoxy(i + 1, 7);
        delay((rand() % 80) + 20);
    }
    cout.flush();
    delay(200);
}

int scan() {
    string ch;
    int i, v;
    do {
        v = 1;
        cin >> ch;
        for (i = 0; i < ch.size(); i++) {
            if (!isdigit(ch[i])) {
                v = 0;
                break;
            }
        }
    } while (!v);
    return atoi(ch.c_str());
}

char bGs[8][4] = {"A+", "B+", "AB+", "O+", "A-", "B-", "AB-", "O-"};
int fee[12] = {
    1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000
};
char* strTitle(int x) {
    static char title[8] = " ";
    if (x == 1)
        strcpy(title, "Master");
    else if (x == 2)
        strcpy(title, "Mr");
    else
        strcpy(title, "Miss");
    return title;
}

class Student {
    int title;
    char studentName[30];
    int rollNo;
    char fatherName[30];
    char motherName[30];
    char address[80];
    char bloodGroup[4];
public:
    void getDetails(void);
    void printDetails(void) {
        cout << "Student Name  : " << strTitle(title) << ' ' << studentName << endl;
        cout << "Roll No.      : " << rollNo << endl;
        cout << "Father's Name : " << fatherName << endl;
        cout << "Mother's Name : " << motherName << endl;
        cout << "Address       : " << address << endl;
        cout << "Blood Group   : " << bloodGroup << endl;
    }
    int retRollNo() {
        return rollNo;
    }
    char* retString(char x) {
        if (x == 'T')
            return strTitle(title);
        if (x == 'N')
            return studentName;
        if (x == 'F')
            return fatherName;
        if (x == 'M')
            return motherName;
        if (x == 'A')
            return address;
        if (x == 'B')
            return bloodGroup;
    }
    char* retStudentName() {
        return retString('N');
    }
    void modDetail(char ch);
};

void Student::getDetails() {
    CLS();
    cout << "Enter Title \n(Master = 1, Mr = 2, Miss = 3)  : ";
    do {
        title = scan();
    } while (title != 1 && title != 2 && title != 3);
    cout << "Enter Student Name: ";
    do {
        cin.ignore();
        cin.getline(studentName, 30);
    } while (strlen(studentName) == 0);
    cout << "Enter Roll No.: ";
    do {
        rollNo = scan();
    } while (rollNo < 1);
    cout << "Enter Father Name: ";
    do {
        cin.ignore();
        cin.getline(fatherName, 30);
    } while (strlen(fatherName) == 0);
    cout << "Enter Mother Name: ";
    do {
        cin.ignore();
        cin.getline(motherName, 30);
    } while (strlen(motherName) == 0);
    cout << "Enter Address: ";
    do {
        cin.ignore();
        cin.getline(address, 80);
    } while (strlen(address) == 0);
    cout << "Enter Blood Group: ";
    int v = 0, i;
    do {
        cin >> bloodGroup;
        for (i = 0; i < strlen(bloodGroup); i++)
            bloodGroup[i] = toupper(bloodGroup[i]);
        for (i = 0; i < 8; i++) {
            if (!strcmp(bloodGroup, bGs[i])) {
                v = 1;
                break;
            }
        }
    } while (!v);
}

void Student::modDetail(char ch) {
    CLS();
    if (ch == 'T') {
        cout << "Enter Title \n(Master = 1, Mr = 2, Miss = 3)  : ";
        do {
            title = scan();
        } while (title != 1 && title != 2 && title != 3);
    }
    else if (ch == 'N') {
        cout << "Enter Student Name: ";
        do {
            cin.ignore();
            cin.getline(studentName, 30);
        } while (strlen(studentName) == 0);
    }
    else if (ch == 'R') {
        int r = rollNo;
        cout << "Enter Roll No.: ";
        fstream fl(FLBSTUD, ios::in | ios::binary);
        Student obj;
        do {
            rollNo = scan();
            fl.close();
            fl.open(FLBSTUD, ios::in | ios::binary);
            while (!fl.eof()) {
                fl.read((char*)&obj, sizeof(obj));
                if (fl.eof())
                    break;
                if (obj.retRollNo() == rollNo && r != rollNo) {
                    cout << "\nSame Roll No. Already Exists !\n";
                    cout << "Enter Roll No.: ";
                    rollNo = -1;
                }
            }
        } while (rollNo < 1);
        fl.close();
    }
    else if (ch == 'F') {
        cout << "Enter Father Name : ";
        do {
            cin.ignore();
            cin.getline(fatherName, 30);
        } while (strlen(fatherName) == 0);
    }
    else if (ch == 'M') {
        cout << "Enter Mother Name: ";
        do {
            cin.ignore();
            cin.getline(motherName, 30);
        } while (strlen(motherName) == 0);
    }
    else if (ch == 'A') {
        cout << "Enter Address : ";
        do {
            cin.ignore();
            cin.getline(address, 80);
        } while (strlen(address) == 0);
    }
    else {
        cout << "Enter Blood Group: ";
        int v = 0, i;
        do {
            cin >> bloodGroup;
            for (i = 0; i < strlen(bloodGroup); i++)
                bloodGroup[i] = toupper(bloodGroup[i]);
            for (i = 0; i < 8; i++) {
                if (!strcmp(bloodGroup, bGs[i])) {
                    v = 1;
                    break;
                }
            }
        } while (!v);
    }
}

class Class {	
	int class_standard;
	char studentName[30];
	int rollNo;
	char Subject[30];
	public:
	void getDetails();			
	void printDetails(int i=1){	
	
		cout<<"Student Name: "<<studentName<<endl;
		if(i)
			cout<<"Class Standard : "<<class_standard<<endl;
		cout<<"Roll No. : "<<rollNo<<endl;
		cout<<"Subject : "<<Subject<<endl;
	}
	int retClass(){			
		return class_standard;
	}
	int retRollNo(){	
		return rollNo;
	}
	char * retString(char x){	
		if(x=='N')
			return studentName;
		if(x=='S')
			return Subject;
	}
	char * retStudentName(){
		return retString('N');
	}
	void modDetail(char ch);
};
void Class::getDetails(){		
system("CLS");
	cout<<"Enter Class Standard : ";
	do{
		class_standard = scan();
	}while(class_standard>12 || class_standard<1);
	cout<<"Enter Student Name: ";
	do{
		gets(studentName);
	}while(strlen(studentName)==0);
	cout<<"Enter Roll No.: ";
	do{
		rollNo = scan();
	}while(rollNo<1);
	cout<<"Enter Subject: ";
	do{
		gets(Subject);
	}while(strlen(Subject)==0);
}
void Class::modDetail(char ch){	
system("CLS");
	if(ch=='C'){
		cout<<"Enter Class Standard: ";
		do{
			class_standard = scan();
		}while(class_standard>12 || class_standard<1);
	}
	else if(ch=='N'){
		cout<<"Enter Student Name: ";
		do{
			gets(studentName);
		}while(strlen(studentName)==0);	
	}
	else if(ch=='R'){
		fstream fl(FLBCLAS,ios::in|ios::binary);
		Class obj;
		int r = rollNo;	
		cout<<"Enter Roll No: ";
		do{
			rollNo = scan();
			fl.close();
			fl.open(FLBCLAS,ios::in|ios::binary);
			while(!fl.eof()){
				fl.read((char*)&obj, sizeof(obj));
				if(fl.eof())
					break;			
				if(obj.retRollNo()==rollNo && r!=rollNo){
					cout<<"\nSame Roll No. Already Exists !\n";
					cout<<"Enter Roll No: ";
					rollNo=-1;
				}
			}
		}while(rollNo<1);
		fl.close();
	}
	else {
		cout<<"Subject : ";
		int v = 0,i;
		do{
			gets(Subject);
		}while(strlen(Subject)==0);
	}
}
void insertStudent(){			
system("CLS");
	Student obj,obj2;
	char ch;
	int v=0;
	cout<<"Enter Details for new Student :\n";
	obj.getDetails();
	fstream fl1(FLBSTUD, ios::in|ios::binary);
	ofstream fl2;
	if(!fl1){			
		fl2.open(FLBSTUD,ios::out|ios::binary);
		fl2.write((char*)&obj, sizeof(obj));
		fl2.close();
		cout<<"Record successfully inserted !\n";
		return;
	}
	while(!fl1.eof()){
		fl1.read((char*)&obj2,sizeof(obj));
		if(fl1.eof()){
			break;
		}
		if(obj.retRollNo()==obj2.retRollNo()){	
			cout<<"Record with same Roll No. with following details already exists : \n";
			obj2.printDetails();
			cout<<"Insertion Aborted !\n";
			return;
		}
		else if(strcmpi(obj.retStudentName(),obj2.retStudentName())==0){
			if (!v)			
				cout<<"Warning : Record with same name exists with follwing details : \n";
			obj2.printDetails();
			cout<<'\n';
			v=1;
		}
	}
	if(v){
		cout<<"Do you still wish to insert record (Y/N) ? ";
		do{			
			cin>>ch;
			ch = toupper(ch);
		}while(ch!= 'Y' && ch!='N');
		if(ch=='N'){
			cout<<"Insertion Aborted !\n";
			return;
		}
	}
	fl2.open(FLBSTUD,ios::out|ios::app|ios::binary);
	fl2.seekp(0,ios::end);
	fl2.write((char*)&obj, sizeof(obj));
	fl2.close();
	cout<<"Record Inserted successfully !\n";
}
void insertClass(){					
system("CLS");
	Class obj,obj2;
	char ch;
	int v=0;
	cout<<"Enter Class Details :\n";
	obj.getDetails();
	fstream fl1(FLBCLAS, ios::in|ios::binary);
	ofstream fl2;
	if(!fl1){						
		fl2.open(FLBCLAS,ios::out|ios::binary);
		fl2.write((char*)&obj, sizeof(obj));
		fl2.close();
		cout<<"Record Inserted successfully !\n";
		return;
	}
	while(!fl1.eof()){
		fl1.read((char*)&obj2,sizeof(obj));
		if(fl1.eof()){
			break;
		}
		if(obj.retRollNo()==obj2.retRollNo()){		
			cout<<"Record with same Roll No. with following details already exists : \n";
			obj2.printDetails();
			cout<<"Insertion Aborted !\n";
			return;
		}
		else if(strcmpi(obj.retStudentName(),obj2.retStudentName())==0){
			if (!v)							
				cout<<"Warning : Record with same name exists with follwing details : \n";
			obj2.printDetails();
			cout<<'\n';
			v=1;
		}
	}
	if(v){				
		cout<<"Do you still wish to insert record (Y/N) ? ";
		do{
			cin>>ch;
			ch = toupper(ch);
		}while(ch!= 'Y' && ch!='N');
		if(ch=='N'){
			cout<<"Insertion Aborted !\n";
			return;
		}
	}
	fl2.open(FLBCLAS,ios::out|ios::app|ios::binary);
	fl2.seekp(0,ios::end);
	fl2.write((char*)&obj, sizeof(obj));
	fl2.close();
	cout<<"Record Inserted successfully !\n";
}
int dispClassRecord(){		

	Class obj;
	int v=0;
	fstream fl(FLBCLAS, ios::in|ios::binary);
	if(!fl){		
		cout<<"Empty Records !\n";
		return 0;
	}
	while(!fl.eof()){
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		v=1;
		obj.printDetails();
		RULE('-');
	}
	fl.close();
	if(!v)
		cout<<"Empty Records !\n";
	return v;
}
int dispStudentRecord(){
system("CLS");
	Student obj;
	int v=0;
	fstream fl(FLBSTUD, ios::in|ios::binary);
	if(!fl){		
		cout<<"Empty Records !\n";
		return 0;
	}
	while(!fl.eof()){
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		v=1;
		obj.printDetails();
		RULE('-');
	}
	fl.close();
	if(!v)
		cout<<"Empty Records !\n";
	return v;
}
int searchClassID(const string str = "search"){	
	fstream fl(FLBCLAS,ios::in|ios::ate|ios::binary);
	if((!fl)||fl.tellg()==0){	
		cout<<"No Records Found !\n";
		return 0;
	}
	fl.close();
	fl.open(FLBCLAS,ios::in|ios::binary);
	cout<<"Enter class to "<<str<<" (0 to disable) : "; 
	int cl;
	char ch;
	char query[30];
	Class obj;
	int found = 0;
	do{
		cin>>cl;
	}while(cl>12 || cl<0);
	cout<<"Enter Attribute to search :\n";
	cout<<"  (N)ame of Student.\n";
	cout<<"  (S)ubject.\n";
	cout<<"Enter your choice : ";
	do{
		cin>>ch;
		ch = toupper(ch);
	}while(ch!='N' && ch!='S');
	cout<<"Enter Query : ";
	do{
		gets(query);
	}while(strlen(query)==0);

	
	while(!fl.eof()){
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof()){
			break;
		}
		if(CL(cl,obj.retClass())){
			if((strcmpi(query,obj.retString(ch))==0)){
				if(!found)
					cout<<"\nSearch Results : \n\n";
				obj.printDetails();
				RULE('-');
				found = 1;
			}
		}
	}
	if(!found)
		cout<<"No Records Found !\n";
	fl.close();
	return found;
}
int searchStudentID(const string str = "search"){
system("CLS");
	fstream fl(FLBSTUD,ios::in|ios::ate|ios::binary);
	if((!fl)||fl.tellg()==0){
		cout<<" No Records Found !\n";
		return 0;
	} 
	fl.close();
	fl.open(FLBSTUD,ios::in|ios::binary);
	char ch;
	char query[30];
	Student obj;
	int found = 0;
	cout<<"Enter Attribute to "<<str<<" :\n";
	cout<<"  (T)itle.\n";
	cout<<"  (N)ame of Student.\n";
	cout<<"  (F)ather's Name.\n";
	cout<<"  (M)other's Name.\n";
	cout<<"  (A)ddress.\n";
	cout<<"  (B)lood Group.\n";
	cout<<"Enter your choice : ";
	do{
		cin>>ch;
		ch = toupper(ch);
	}while(ch!='T' && ch!='N' && ch!='F' && ch!='M' && ch!='A' && ch!='B');
	cout<<"\nEnter Query : ";
	do{
		gets(query);
	}while(strlen(query)==0);
	while(!fl.eof()){
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof()){
			break;
		}
		if((strcmpi(query,obj.retString(ch))==0)){
			if(!found)
				cout<<"\nSearch Results : \n\n";
			obj.printDetails();
			RULE('-');
			found = 1;
		}
	}
	if(!found)
		cout<<"No Records Found !\n";
	fl.close();
	return found;
}
int searchByRollNo(int i){		
system("CLS");
	int r;
	if(i==1){
		Class obj;
		int found = 0;
		int cl;
		cout<<"Enter class to search in (0 to disable) : ";	
		do{
			cin>>cl;
		}while(cl>12 || cl<0);
		cout<<"Enter Roll No. to search for : ";
		cin>>r;
		fstream fl(FLBCLAS,ios::in|ios::binary);
		if(!fl){					
			cout<<"No Records Found !\n";
			return 0;
		}
		while(!fl.eof()){
			fl.read((char*)&obj,sizeof(obj));
			if(fl.eof()){
				break;
			}
			if(CL(cl,obj.retClass())){
				if(r==obj.retRollNo()){			
					if(!found)
						cout<<"\nSearch Results : \n\n";
					obj.printDetails();
					RULE('-');
					found = 1;
				}
			}
		}
		if(!found)
			cout<<"No Records Found !\n";
		fl.close();
		return found;
	}
	else{
		int found=0;
		Student obj;
		cout<<"Enter Roll No. to search for : ";
		cin>>r;
		fstream fl(FLBSTUD,ios::in|ios::binary);
		if(!fl){		
			cout<<"No Records Found !\n";
			return 0;
		}
		while(!fl.eof()){
			fl.read((char*)&obj,sizeof(obj));
			if(fl.eof()){
				break;
			}
			if(r==obj.retRollNo()){
				if(!found)
					cout<<"\nSearch Results : \n\n";
				obj.printDetails();
				RULE('-');
				found = 1;
			}
		}
		if(!found)
			cout<<"No Records Found !\n";
		fl.close();
		return found;
	}
}
void sortByStudents(char ch){		
	vector <pair<string,int> > lst;		
	int i;
	if(ch=='C'){				
		Class obj;
		int v=0;
		fstream fl(FLBCLAS, ios::in|ios::binary);
		if(!fl){
			cout<<"Empty Records !\n";
			return;
		}
		while(!fl.eof()){
			fl.read((char*)&obj, sizeof(obj));
			if(fl.eof())
				break;
			v=1;
			lst.push_back(make_pair(obj.retString('N'),obj.retRollNo())); 
		}
		fl.close();
		if(v==0){
			cout<<"Empty Records !\n";
			return;
		}
		sort(lst.begin(),lst.end(),strcmpis);	//Sort using <algorithm> sort and Custom Comparison 
		fstream tmp("temp.txt",ios::out|ios::binary);
		fl.open(FLBCLAS,ios::in|ios::binary);
		fl.seekg(0,ios::beg);
		for(i=0;i<lst.size();i++){
			fl.close();
			fl.open(FLBCLAS,ios::in|ios::binary);
			while(!fl.eof()){
				fl.read((char*)&obj, sizeof(obj));
				if(fl.eof())
					break;
				if(obj.retRollNo()==lst[i].second){		//Check each Roll No. from each pair and write record to new file
					tmp.write((char*)&obj,sizeof(obj));
				}
			}
		}
		fl.close();
		tmp.close();
		remove(FLBCLAS);
		rename("temp.txt",FLBCLAS);
		cout<<"\nThe Records have been successfully sorted !\n\n";
		dispClassRecord();
	}
	else{					//Sort Student Records
		Student obj;
		int v=0;
		char c;
		fstream fl(FLBSTUD, ios::in|ios::binary);
		system("CLS");
		cout<<"Enter criteria to sort :\n";
		cout<<"  (N)ame of Student.\n";
		cout<<"  (T)itle.\n";
		cout<<"Enter your choice : \n";		
		do{
			cin>>c;
			c=toupper(c);
		}while(c!='N' && c!='T');
		if(!fl){
			cout<<"Empty Records !\n";
			return;
		}
		while(!fl.eof()){
			fl.read((char*)&obj, sizeof(obj));
			if(fl.eof())
				break;
			v=1;
			lst.push_back(make_pair(obj.retString(c),obj.retRollNo()));	//Push each pair in the vector
		}
		fl.close();
		if(v==0){
			cout<<"Empty Records !\n";
			return;
		}
		sort(lst.begin(),lst.end(),strcmpis);	//Sort using <algorithm> sort and Custom Comparison 
		fstream tmp("temp.txt",ios::out|ios::binary);
		fl.open(FLBSTUD,ios::in|ios::binary);
		fl.seekg(0,ios::beg);
		for(i=0;i<lst.size();i++){
			fl.close();
			fl.open(FLBSTUD,ios::in|ios::binary);
			while(!fl.eof()){
				fl.read((char*)&obj, sizeof(obj));
				if(fl.eof())
					break;
				if(obj.retRollNo()==lst[i].second){		//Check each Roll No. from each pair and write record to new file
					tmp.write((char*)&obj,sizeof(obj));
				}
			}
		}
		fl.close();
		tmp.close();
		remove(FLBSTUD);
		rename("temp.txt",FLBSTUD);
		cout<<"\nThe Records have been successfully sorted !\n\n";
		dispStudentRecord();
	}
}
void delClassRecord(){			//Delete Class Records
system("CLS");
	Class obj;					//Writes to new file except record to be deleted
	int f=0;
	if(!searchClassID("delete from"))
		return;
	cout<<"\nEnter Roll No. to delete : ";
	int r;
	char ch;
	cin>>r;
	fstream fl(FLBCLAS, ios::in|ios::binary);
	fstream fo("temp.dat", ios::out|ios::binary);
	while(!fl.eof()){
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		if (r==obj.retRollNo()){
			cout<<"Record with following info will be deleted :\n\n";
			obj.printDetails();
			cout<<"Do you wish to continue ? (Y/N) : ";
			do{
				cin>>ch;
				ch = toupper(ch);
			}while(ch!='N' && ch!='Y');
			if(ch=='N'){
				cout<<"Deletion Aborted !\n";
				fl.close();
				fo.close();
				remove("temp.dat");
				return;
			}
			f=1;
			continue;
		}
		fo.write((char*)&obj,sizeof(obj));
	}
	fl.close();
	fo.close();
	remove(FLBCLAS);
	rename("temp.dat",FLBCLAS);
	if(f)
		cout<<"Record Successfully Deleted !\n";
	else
		cout<<"No Such Record Exists !\n";
}
void delStudentRecord(){			//Delete Student Records
system("CLS");
	Student obj;					//Writes to new file except record to be deleted
	int f=0;
	if(!searchStudentID("delete using"))
		return;
	cout<<"\nEnter Roll No. to delete : ";
	int r;
	char ch;
	cin>>r;
	fstream fl(FLBSTUD, ios::in|ios::binary);
	fstream fo("temp.dat", ios::out|ios::binary);
	while(!fl.eof()){
		fl.read((char*)&obj, sizeof(obj));
		if(fl.eof())
			break;
		if (r==obj.retRollNo()){
			cout<<"Record with following info will be deleted :\n\n";
			obj.printDetails();
			cout<<"Do you wish to continue ? (Y/N) : ";
			do{
				cin>>ch;
				ch = toupper(ch);
			}while(ch!='N' && ch!='Y');
			if(ch=='N'){
				cout<<"Deletion Aborted !\n";
				
				fl.close();
				fo.close();
				remove("temp.dat");
				return;
			}
			f=1;
			continue;
		}
		fo.write((char*)&obj,sizeof(obj));
	}
	fl.close();
	fo.close();
	remove(FLBSTUD);
	rename("temp.dat",FLBSTUD);
	if(f)
		cout<<"Record Successfully Deleted !\n";
	else
		cout<<"No Such Record Exists !\n";
}
int checkNoInClass(){				//Prints total number of students in each class
system("CLS");
	int cl[12]={0,0,0,0,0,0,0,0,0,0,0,0},i,found =0;
	Class obj;
	int cnt=0;
	fstream fl(FLBCLAS,ios::in|ios::binary);
	if(!fl){
		cout<<"No Records Found !\n";
		return 0;
	}
	while(!fl.eof()){
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof()){
			break;
		}
		found=1;
		cl[obj.retClass()-1]++;			//Gets each record from file and stores count of each class [c-p cp]
	}
	if(!found)
		cout<<"No Records Found !\n";
	fl.close();
	cout<<"\tNumber of Students in :\n";
	for(i=0;i<12;i++){
		cout<<"\t\tClass "<<i+1<<((i>8)?" ":"  ")<<"    :\t";
		printf("%3d",cl[i]);
		cout<<'\n';
		cnt+=cl[i];
	}
	cout<<"\t\t-------------------\n";
	cout<<"\t\tTotal Number :\t";
	printf("%3d", cnt);
	cout<<"\n\t\t-------------------\n";
	return found;
}
int dispByStandard(){					//Display each Class record by Standard
	Class obj;
	int v=0,cl=1,cnt;
	fstream fl(FLBCLAS, ios::in|ios::binary);
	if(!fl){
		cout<<"No Records Found !\n";
		return 0;
	}
	for(cl=1;cl<=12;cl++){
		cnt=0;
		fl.close();
		fl.open(FLBCLAS, ios::in|ios::binary);		//Starts with Class 1 to 12 and checks each class 
		while(!fl.eof()){
			fl.read((char*)&obj, sizeof(obj));
			if(fl.eof())
				break;
			v=1;
			if(obj.retClass()==cl){
				if(cnt==0){
					RULE('*');
					cout<<"\t\t\t\t  Class "<<cl;
					RULE('*'); 
					cnt=1;
				}
				obj.printDetails(0);
				RULE('-');
			}
		}
	}
	fl.close();
	if(!v)
		cout<<"No Records Found !\n";
	return v;
}
int totalRevenueGenerated(){			//Calculates total fee based on Total=Sum(Fee for Each class  * Total students in that class)
system("CLS");
	int i,found =0;
	Class obj;
	int total = 0;
	fstream fl(FLBCLAS,ios::in|ios::binary);
	if(!fl){
	cout<<" \n\n   Total Fee Revenue Generated  : \t"<<total<<".00"<<'\n';
		return 0;
	}
	while(!fl.eof()){
		fl.read((char*)&obj,sizeof(obj));
		if(fl.eof()){
			break;
		}
		total += ::fee[obj.retClass()-1];
	}
	fl.close();
	cout<<" \n\n   Total Fee Revenue Generated  : \t"<<total<<".00"<<'\n';
	return found;
}
void modEntry(char c){				//Modify Record Entry
system("CLS");
	if(c=='C'){
		Class obj;
		if(!searchClassID("search for"))
			return;					//Searches for Records and Modifies using Roll No. based on attribute
		fstream fl(FLBCLAS,ios::in|ios::binary);
		int r,pos;
		char ch;
		int found = 0;
		cout<<"Enter Roll No. of Record to modify : ";
		do{
			cin>>r;
		}while(r<1);
		while(!fl.eof()){
			pos=fl.tellg();
			fl.read((char*)&obj,sizeof(obj));
			if(fl.eof())
				break;
			if(r==obj.retRollNo()){
				cout<<'\n';
				fl.close();
				fl.open(FLBCLAS,ios::out|ios::in|ios::binary);
				while(pos--) fl.get();
				cout<<"Enter Attribute to modify :\n";
				cout<<"  (N)ame of Student.\n";
				cout<<"  (C)lass Standard.\n";
				cout<<"  (R)oll No.\n";
				cout<<"  (S)ubject.\n";
				cout<<"Enter your choice : ";
				do{
					cin>>ch;
					ch = toupper(ch);
				}while(ch!='N' && ch!='C' && ch!='R' && ch!='S');
				obj.modDetail(ch);
				obj.printDetails();
				fl.write((char*)&obj,sizeof(obj));
				RULE('-');
				break;
			}
		}
		return;
	}
		Student obj;
		if(!searchStudentID("search for"))
			return;				//Searches for Records and Modifies using Roll No. based on attribute
		fstream fl(FLBSTUD,ios::in|ios::binary);
		int r,pos;
		char ch;
		int found = 0;
		cout<<"Enter Roll No. of Record to modify : ";
		do{
			cin>>r;
		}while(r<1);
		while(!fl.eof()){
			pos=fl.tellg();
			fl.read((char*)&obj,sizeof(obj));
			if(fl.eof())
				break;
			if(r==obj.retRollNo()){
				cout<<'\n';
				fl.close();
				fl.open(FLBSTUD,ios::out|ios::in|ios::binary);
				while(pos--) fl.get();
				cout<<"Enter Attribute to modify :\n";
				cout<<"  (T)itle.\n";
				cout<<"  (N)ame of Student.\n";
				cout<<"  (R)oll No.\n";
				cout<<"  (F)ather's Name.\n";
				cout<<"  (M)other's Name.\n";
				cout<<"  (A)ddress.\n";
				cout<<"  (B)lood Group.\n";
				cout<<"Enter your choice : ";
				do{
					cin>>ch;
					ch = toupper(ch);
				}while(ch!='T' && ch!='N' &&ch!='R' && ch!='F' && ch!='M' && ch!='A' && ch!='B');
				obj.modDetail(ch);
				obj.printDetails();
				fl.write((char*)&obj, sizeof(obj));
				RULE('-');
				break;
			}
		}
}

int main(){

	char ch;
	char ch1;
	int ch2;
	load();
	do{
		CLS();
		cout << "\t%%      %%      ";
   cout << "\n\t%%      %% %%%%%%% %%      %%%%%%  %%%%%% %%%%  %%%% %%%%%%%";
   cout << "\n\t%%      %% %%      %%      %%      %%  %% %%  %%% %% %%       ";
   cout << "\n\t%%  %%  %% %%%%%   %%      %%      %%  %% %%  %%% %% %%%%%      ";
   cout << "\n\t%%  %%  %% %%      %%      %%      %%  %% %%      %% %%           ";
   cout << "\n\t%%%%%%%%%% %%%%%%% %%%%%%% %%%%%%% %%%%%% %%      %% %%%%%%%     ";
   cout << "\n\n\t\t\t        $$$$$$$$  $$$$$        ";
   cout << "\n\t\t\t           $$     $   $      ";
   cout << "\n\t\t\t           $$     $$$$$    ";

   cout << "\n\n\n\t\t\tOBJECT ORIENTED PROGRAMMING   PROJECT \n\n\n\n\n";

		RULE("*******************");
		cout <<"**************************************\n";
		cout<<"\t\t\t    School Management System\n";
		cout <<"**************************************\n";
		RULE("*******************");
		cout<<"\t1. Student Database Management.\n";
		cout<<"\t2. Class Database Management.\n";
		cout<<"\t0. Exit.\n\n";
		cout<<"Enter your choice : ";
		fflush(stdin);
		cin>>ch1;
		if(ch1=='1'){
			fflush(stdin);
			
			load();
			do{
				CLS();
				RULE("*");
				cout<<"\t\t\t    School Management System";
				RULE("*");
				cout<<"\t\t\tStudent Database Management System";
				RULE('-');
				cout<<"\t1.  Insert Records.\n";
				cout<<"\t2.  Display all Records.\n";
				cout<<"\t3.  Search for a Record using Roll No.\n";
				cout<<"\t4.  Search for a Record using other Attributes.\n";
				cout<<"\t5.  Sort all Records.\n";
				cout<<"\t6.  Modify a Record.\n";
				cout<<"\t7.  Delete a Record.\n";
				cout<<"\t0.  Exit.\n";
				cout<<"\nEnter your choice : ";
				ch2 = scan();
				switch(ch2){
					case 1:
						insertStudent();
						break;
					case 2:
						dispStudentRecord();
						break;
					case 3:
						searchByRollNo(2);
						break;
					case 4:
						searchStudentID();
						break;
					case 5:
						sortByStudents('S');
						break;
					case 6:
						modEntry('S');
						break;
					case 7:
						delStudentRecord();
						break;
				}
				fflush(stdin);
				if(ch2)
					cin>>ch;
				else
					load();
			}while(ch2!=0);
		}
		if(ch1=='2'){
			fflush(stdin);
			load();
			do{
				CLS();
				RULE("*");
				cout<<"\t\t\t     Class Management System";
				RULE("*");
				cout<<"\t\t\tClass Database Management System";
				RULE('-');
				cout<<"\t1.  Insert Records.\n";
				cout<<"\t2.  Display all Records.\n";
				cout<<"\t3.  Search for a Record using Roll No.\n";
				cout<<"\t4.  Search for a Record using other Attributes.\n";
				cout<<"\t5.  Sort all Records.\n";
				cout<<"\t6.  Modify a Record.\n";
				cout<<"\t7.  Delete a Record.\n";
				cout<<"\t8.  Display Total Number of Students in Each Class.\n";
				cout<<"\t9.  Display Students by Standard.\n";
				cout<<"\t10. Display Total Fee Revenue Generated.\n";
				cout<<"\t0.  Exit.\n";
				cout<<"\nEnter your choice : ";
				ch2 = scan();
				switch(ch2){
					case 1:
						insertClass();
						break;
					case 2:
						dispClassRecord();
						break;
					case 3:
						searchByRollNo(1);
						break;
					case 4:
						searchClassID();
						break;
					case 5:
						sortByStudents('C');
						break;
					case 6:
						modEntry('C');
						break;
					case 7:
						delClassRecord();
						break;
					case 8:
						checkNoInClass();
						break;
					case 9:
						dispByStandard();
						break;
					case 10:
						totalRevenueGenerated();
						break;
				}
				fflush(stdin);
				if(ch2)
					cin>>ch;
				else{
					load();
				}
			}while(ch2!=0);
		}
	}while(ch1!='0');
	CLS();
	return 0;
}
