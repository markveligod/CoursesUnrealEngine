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

int main(void)
{
	//HelloWorld();
	Intro();
	return (0);
}