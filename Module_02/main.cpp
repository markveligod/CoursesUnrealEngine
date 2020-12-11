#include <iostream>

void HelloWorld()
{
	std::cout << "Hello World!\n";
}

void Intro()
{
	std::cout << "You are a secret agent breaking into a secure server room\n";
	std::cout << "You need to enter the correct codes to continue...\n";
}

void Varibles()
{
	int a = 4;
	std::cout << "a = " << a << std::endl;
	int b = 14;
	std::cout << "a = " << b << std::endl;
	int c = 114;
	std::cout << "a = " << c << std::endl;
}

int main(void)
{
	//HelloWorld();
	Intro();
	Varibles();
	return (0);
}