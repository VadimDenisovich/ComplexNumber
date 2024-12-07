#include <iostream>
#include "include/complexNumber.h"

// Просто файл для проверки разных отдельных функций
int main()
{  
    ComplexNumber<int> c1(-10, 19);
    ComplexNumber c2 = c1 + 'a';
    std::cout << c2 << std::endl;
    return 0; 
}