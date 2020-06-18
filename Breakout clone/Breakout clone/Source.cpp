#include <iostream>

int x = 1;

int main()
{
	// "Write a program that prints the numbers from 1 to 100.   
	// But for multiples of three print “Fizz” instead of the number and for the multiples of five print “Buzz”.
	// For numbers which are multiples of both three and five print “FizzBuzz”.


	//Doesn't replace the number still!

	std:: cout << "Hello World!" << std::endl;

	//goes through to 100
	while (x < 101)
	{
		std::cout << x++ << std::endl;

		// using the modular for finding whats equal to the number
		if (x % 3 == 0)
		{
			std::cout << "Fizz" << std::endl;
		}

		if (x % 5 == 0)
		{
			std::cout << "Buzz" << std::endl;
		}

		if (x % 3 == 0 && x % 5 == 0)
		{
			std::cout << "FizzBuzz" << std::endl;
		}
		
	}

	return 0;
}