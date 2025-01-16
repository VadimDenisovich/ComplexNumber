#include <iostream>
#include "include/complexNumber.h"
#include "include/rationalNumber.h"

// Просто файл для проверки разных отдельных функций
int main()
{  
		RationalNumber a2(0.0);
		RationalNumber b2(0.0);
		RationalNumber a1(9223372036854775400.3482338);
		RationalNumber b1(1);
		RationalNumber mod = (a2 * a2) + (b2 * b2); 
		std::cout << mod << std::endl;
    RationalNumber real = (((a1 * a2) + (b1 * b2)) / mod);   
		std::cout << real << std::endl;
   	RationalNumber imaginary = (((b1 * a2) - (a1 * b2)) / mod);
		std::cout << imaginary << std::endl;
    return 0; 
}