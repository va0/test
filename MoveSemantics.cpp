#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "MoveSemantics.h"

using std::cout;
using std::endl;

//Name::Name() : name(""), size(0) {};
Name::Name(const char* c)
{
	cout << "Converting Constructor!" << endl;
	this->size = strlen(c) + 1;
	this->name = new char[this->size];
	this->name[size - 1] = '\0';
	//memcpy(name, c, size);
	strcpy_s(this->name, this->size,c);
};
Name::Name(const Name& obj)
{
	cout << "Name Copying Constructor!" << endl;
	this->size = obj.size;
	this->name = new char[this->size];
	this->name[size - 1] = '\0';;
	strcpy_s(this->name, this->size, obj.name);
};
Name::Name(Name&& obj) noexcept
{
	cout << "Name Moving Constructor!" << endl;
	this->name = obj.name;

	obj.name = nullptr;
	obj.size = 0;

};
Name::~Name() { cout << "Destroying name!" << endl; delete[] this->name; };
void Name::PrintName() { if (this->name != NULL) cout << this->name << endl; }


Person::Person(const Person& person) : name(person.name)
{
	cout << "Person Copying Constructor!" << endl;

}

Person::Person(Person&& person) noexcept : name(std::move(person.name))
{
	cout << "Person Moving Constructor!" << endl;

}

Person::Person(const Name& name) : name(name)
{
	cout << "Person (Name) Copying Constructor!" << endl;

}

Person::Person(Name&& name) noexcept : name(std::move(name))    //albo name((Name&&)name)
{
	cout << "Person (Name) Moving Constructor!" << endl;

}

Person::~Person() {}
void Person::Print() {  this->name.PrintName(); }

void main()
{
	//Name n = "Jarek";
	//n.PrintName();


	//-------------------------------------------------


	//Person p("Filip");
	//Person p(Name("Filip"));
	
	//Name nFilip = Name("Filip");
	//Name nFilip = "Filip";
	//Person p(nFilip);
	//p.Print();
	

	//make std::move and move semantics to avoid copying the object
	Name nFilip = "Filip";
	Person p(std::move(nFilip));  //czyli trzeba dac tutaj std move zeby miec Name&& reference to rvalue apotem w kontruktorze Person moving dac jeszcze raz std::move zeby odpalil konstruktor moving dla Name
	p.Print();



	system("cls");



	Person p1 = ((Name&)Name("Daniel")); //ciekawe bo bez jawnej konwersji odpala mi moving constructor w 2 klasach - jakas auto optymalizacja?
	//Person p1 = (Name("Daniel"));
	//p1.Print();

	//Person p2 = p1; //oba dzialaja wywoluje sie copying constructor we 2 klasach
	//Person p2(p1);  //oba dzialaja wywoluje sie copying constructor we 2 klasach
	Person p2(std::move(p1));  //a tutaj robie moving constructor i pozniej p1 name jest juz null
	p2.Print(); //all ok wyswietla Daniel
	//p1.~Person(); //nawet moglbym samemu wywolac destruktor na obiekcie Person bo stary juz mi nie potrzebny
	p1.Print(); //nic nie wysietli bo p1.name.name jest null


	//system("pause");
	system("cls");




	int liczba = 50;
	std::string test = "Test";

	//MessageBox(NULL, L"Body", (LPCWSTR)(test.c_str()), MB_OK);
	MessageBoxA(NULL, test.c_str(), "Header", MB_OK);
	MessageBoxA(NULL, std::to_string(liczba).c_str(), "Header", MB_OK);


	time_t time = std::time(0);
	char buffer[100];
	ctime_s(buffer, 100, &time);
	MessageBoxA(NULL, buffer, "Header", MB_OK);


	char buffer2[100];
	//tm* pTm = std::localtime(&time);
	tm tm;
	localtime_s(&tm, &time);
	strftime(buffer2, 100, "%Y/%m/%d %H:%M:%S %A", &tm);
	MessageBoxA(NULL, buffer2, "Header", MB_OK);

	
	float fl = 17.043;
	std::string strFl = std::to_string(fl);
	MessageBoxA(NULL, strFl.c_str(), "Header", MB_OK);

	const char* siema = "siema";
	std::string strSiema(siema);

	strSiema = "jednak elo elo";
	strSiema += " KOCHAM";
	std::string tester = "ZAL PL" + strSiema + " SEX";
	MessageBoxA(NULL, strSiema.c_str(), "Header", MB_OK);
	MessageBoxA(NULL, tester.c_str(), "Header", MB_OK);

	float zmiana = atof(strFl.c_str());
	zmiana += 0.031;
	cout << zmiana << endl;

	cout << "Nowa zmiana for git\n";
}

