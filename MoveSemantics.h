#pragma once

class Name
{
public:
	//Name();
	~Name();

	/*explicit*/ Name(const char*);  //mozna dac ze explicit i wtedy nie da sie Name n = "Jarek";
	Name(const Name&);
	Name(Name&&) noexcept;

	void PrintName();

private:
	char* name;
	int size;
};

class Person
{
public:
	//Person();
	~Person();

	Person(const Person&);
	Person(Person&&) noexcept;
	Person(const Name&);
	Person(Name&&) noexcept;

	void Print();

private:
	Name name;
};

extern int u6064525;