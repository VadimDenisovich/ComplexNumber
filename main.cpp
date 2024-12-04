#include "include/complexNumber.h"
#include <iostream>

// TODO: 
// 1. Реализовать unit-тесты

int main()
{
    ComplexNumber c1(9.0, 12.0);
    ComplexNumber c2(1.0, 2.0);

    ComplexNumber c3 = c1 / 3;
    ComplexNumber c4 = 4 / c2;  
    std::cout << c3 << "\n" << c4 << std::endl; 

    return 0;
}