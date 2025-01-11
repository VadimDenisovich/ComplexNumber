#include <iostream>
#include "include/complexNumber.h"
#include "include/rationalNumber.h"

// Просто файл для проверки разных отдельных функций
int main()
{  
		double max_double = std::numeric_limits<double>::max();
		std::cout << max_double << std::endl;
    double big_number1 = max_double / 2;
		std::cout << big_number1 << std::endl;
    double big_number2 = max_double / 3;
		RationalNumber r1(big_number1);
		std::cout << r1 << std::endl;
    return 0; 
}