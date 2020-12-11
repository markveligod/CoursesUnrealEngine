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
	std::cout << "void Varibles()\n";
	int a = 4;
	std::cout << "a = " << a << std::endl;
	int b = 14;
	std::cout << "b = " << b << std::endl;
	int c = 114;
	std::cout << "c = " << c << std::endl;
	std::cout << "a + b + c = " << a + b + c << std::endl;
	std::cout << "a - b - c = " << a - b - c << std::endl;
	std::cout << "a * b * c = " << a * b * c << std::endl;
	std::cout << "a / b / c = " << a / b / c << std::endl;
}

void ConstVaribles()
{
	std::cout << "void ConstVaribles()\n";
	const int a = 4;
	std::cout << "a = " << a << std::endl;
	const int b = 14;
	std::cout << "b = " << b << std::endl;
	const int c = 114;
	std::cout << "c = " << c << std::endl;
	std::cout << "a + b + c = " << a + b + c << std::endl;
	std::cout << "a - b - c = " << a - b - c << std::endl;
	std::cout << "a * b * c = " << a * b * c << std::endl;
	std::cout << "a / b / c = " << a / b / c << std::endl;
}

int main(void)
{
	//HelloWorld();
	Intro();
	Varibles();
	ConstVaribles();
	return (0);
}
