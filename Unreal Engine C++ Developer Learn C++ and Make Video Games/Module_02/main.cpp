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
	const int CodeA = 4;
	std::cout << "CodeA = " << CodeA << std::endl;
	const int CodeB = 14;
	std::cout << "CodeB = " << CodeB << std::endl;
	const int CodeC = 114;
	std::cout << "CodeC = " << CodeC << std::endl;
	std::cout << "CodeA + CodeB + CodeC = " << CodeA + CodeB + CodeC << std::endl;
	std::cout << "CodeA - CodeB - CodeC = " << CodeA - CodeB - CodeC << std::endl;
	std::cout << "CodeA * CodeB * CodeC = " << CodeA * CodeB * CodeC << std::endl;
	std::cout << "CodeA / CodeB / CodeC = " << CodeA / CodeB / CodeC << std::endl;
}

void InputTerminal()
{
	std::cout << "void InputTerminal()\n";
	int GuessA, GuessB, GuessC;

	std::cin >> GuessA >> GuessB >> GuessC;
	std::cout << "Your enter: " << GuessA << " " << GuessB << " " << GuessC << std::endl;
	int GuessSum = GuessA + GuessB + GuessC;
	int GuessMulti = GuessA * GuessB * GuessC;
	std::cout << "GuessSum: " << GuessSum << std::endl;
	std::cout << "GuessMulti: " << GuessMulti << std::endl;
}

void IfState()
{
	std::cout << "void IfState()\n";
	if (true)
	{
		std::cout << "TRUE!\n";
	}

	if (false)
	{
		std::cout << "LOL WHAT!\n";
	}
	else
	{
		std::cout << "FALSE!\n";
	}
	
}

int main(void)
{
	//HelloWorld();
	while (true)
	{
		Intro();
		Varibles();
		ConstVaribles();
		InputTerminal();
		IfState();
		std::cin.clear();
		std::cin.ignore();
	}
	return (0);
}
