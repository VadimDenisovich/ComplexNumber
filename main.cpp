#include <iostream>
#include "include/complexNumber.h"

int main()
{
    ComplexNumber<int> c1(-10, 19);
    c1.factorization(2);
    std::cout << c1.getReal() << " " << c1.getImaginary() << std::endl;
    return 0; 
}