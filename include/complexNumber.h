#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

// Добавим, чтобы детектить std::ostream
#include <iostream>
#include <variant>

using IntFloatDoubleType = std::variant<int, float, double>;

class ComplexNumber {
    // Не указывать в .h файле параметры по умолчанию 
    // factorization(int degree = 1) - плохая практика
private: 
    double real;
    double imaginary; 

protected:
    static double toDouble(const IntFloatDoubleType& real); 

public:   
    ComplexNumber(IntFloatDoubleType r = 0.0, double i = 0.0); 
    double getReal();
    void setReal(IntFloatDoubleType _real); 
    double getImaginary(); 
    void setImaginary(IntFloatDoubleType _imaginary);
    double abs();
    double arg();
    void factorization(int degree = 1);
    ComplexNumber operator=(const ComplexNumber &other); 
    void operator+=(ComplexNumber &other);
    void operator+=(IntFloatDoubleType number);
    void operator-=(ComplexNumber &other);
    void operator-=(IntFloatDoubleType number);
    void operator*=(ComplexNumber &other);
    void operator*=(IntFloatDoubleType number);
    void operator/=(ComplexNumber &other);
    void operator/=(IntFloatDoubleType number);
    ComplexNumber operator-();

    // Дружественные функции 
    friend std::ostream &operator<<(std::ostream &terminal, const ComplexNumber &number); 
    friend ComplexNumber operator+(ComplexNumber &left, ComplexNumber &right);
    friend ComplexNumber operator+(ComplexNumber &left, IntFloatDoubleType number);
    friend ComplexNumber operator+(IntFloatDoubleType number, ComplexNumber &right);
    friend ComplexNumber operator-(ComplexNumber &left, ComplexNumber &right);
    friend ComplexNumber operator-(ComplexNumber &left, IntFloatDoubleType number);
    friend ComplexNumber operator-(IntFloatDoubleType number, ComplexNumber &right);
    friend ComplexNumber operator*(ComplexNumber &left, ComplexNumber &right);
    friend ComplexNumber operator*(ComplexNumber &left, IntFloatDoubleType number);
    friend ComplexNumber operator*(IntFloatDoubleType number, ComplexNumber &right);
    friend ComplexNumber operator/(ComplexNumber &left, ComplexNumber &right);
    friend ComplexNumber operator/(ComplexNumber &left, IntFloatDoubleType number);
    friend ComplexNumber operator/(IntFloatDoubleType number, ComplexNumber &right);
    friend bool operator==(ComplexNumber &left, ComplexNumber &right);
    friend bool operator!=(ComplexNumber &left, ComplexNumber &right);
};

#endif