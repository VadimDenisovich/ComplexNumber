#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

// Добавим, чтобы детектить std::ostream
#include <iostream>
#include <variant>
#include <type_traits>
#include <stdexcept>

template<typename T>
class ComplexNumber {
    // Вызывает ошибку, если тип T не соответствует int, float, double 
    // EX: СomplexNumber<char> вызовет ошибку
    static_assert(std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, double>,
                  "Unsupported type for ComplexNumber");

    // Указывать в .h файле параметры по умолчанию 
    // factorization(int degree = 1)
private: 
    double real;
    double imaginary; 

protected:
    template<typename V>
    static double toDouble(const V& value);

public:   
    ComplexNumber(T r = 0.0, double i = 0.0); 
    double getReal();

    // Чтобы работало auto нужно в tasks.json 
    // в разделе args прописать `-std=c++20`
    void setReal(auto _real); 
    double getImaginary(); 
    void setImaginary(auto _imaginary);
    double abs();
    double arg();
    void factorization(int degree = 1);
    ComplexNumber operator=(const ComplexNumber &other); 
    void operator+=(ComplexNumber &other);

    void operator+=(auto number);
    void operator-=(ComplexNumber &other);
    void operator-=(auto number);
    void operator*=(ComplexNumber &other);
    void operator*=(auto number);
    void operator/=(ComplexNumber &other);
    void operator/=(auto number);
    ComplexNumber operator-();

    // Дружественные функции 
    template<typename U>
    friend std::ostream &operator<<(std::ostream &terminal, const ComplexNumber<U> &number); 
    
    template<typename U>
    friend ComplexNumber<double> operator+(ComplexNumber<U> &left, ComplexNumber<U> &right);
    
    // Указываем два шаблона 
    // typename U - для типа, с которым был инициализирован экземпляр класса 
    // typename V - для типа, с каким 
    template<typename U, typename V>
    friend ComplexNumber<double> operator+(ComplexNumber<U> &left, V number);
    
    template<typename U, typename V>
    friend ComplexNumber<double> operator+(V number, ComplexNumber<U> &right);
    
    template<typename U>
    friend ComplexNumber<double> operator-(ComplexNumber<U> &left, ComplexNumber<U> &right);
    
    template<typename U, typename V>
    friend ComplexNumber<double> operator-(ComplexNumber<U> &left, V number);
    
    template<typename U, typename V>
    friend ComplexNumber<double> operator-(V number, ComplexNumber<U> &right);
    
    template<typename U>
    friend ComplexNumber<double> operator*(ComplexNumber<U> &left, ComplexNumber<U> &right);
    
    template<typename U, typename V>
    friend ComplexNumber<double> operator*(ComplexNumber<U> &left, V number);
    
    template<typename U, typename V>
    friend ComplexNumber<double> operator*(V number, ComplexNumber<U> &right);
    
    template<typename U>
    friend ComplexNumber<double> operator/(ComplexNumber<U> &left, ComplexNumber<U> &right);
    
    template<typename U, typename V>
    friend ComplexNumber<double> operator/(ComplexNumber<U> &left, V number);

    template<typename U, typename V>
    friend ComplexNumber<double> operator/(V number, ComplexNumber<U> &right);

    template<typename U>
    friend bool operator==(ComplexNumber<U> &left, ComplexNumber<U> &right);

    template<typename U>
    friend bool operator!=(ComplexNumber<U> &left, ComplexNumber<U> &right);
};

// в конце нужно экспортировать файл с реализацией
// шаблонных методов и конструкторов, и дружественных функций 
#include "../src/complexNumber.tpp"

#endif