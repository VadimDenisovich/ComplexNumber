#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

// Добавим, чтобы детектить std::ostream
#include <iostream>
#include <variant>
#include <type_traits>
#include <stdexcept>
#include "rationalNumber.h"

// Класс действительного числа
class Real {
private:
	RationalNumber value; 

public: 
	// Конструктор для действительного числа
	template<typename T>
	Real(T _real) {
		static_assert(std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, double> || std::is_same_v<T,RationalNumber>,
							"Unsupported type for imaginary part");
		value = RationalNumber::toRationalNumber(_real);
	};

	friend class ComplexNumber; 
};

// Класс мнимой части
class Imag {
private: 
	RationalNumber value; 

public: 
	// Конструктор мнимой части 
	template<typename T>
	Imag(T _imag) {
		static_assert(std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, double> || std::is_same_v<T,RationalNumber>,
							"Unsupported type for imaginary part");
		value = RationalNumber::toRationalNumber(_imag);
	};

	friend class ComplexNumber; 
};

class ComplexNumber {
    // Указывать в .h файле параметры по умолчанию 
    // factorization(int degree = 1)
private: 
    Real real;
    Imag imaginary;

public:   
    ComplexNumber(Real r, Imag i = Imag(0));
    RationalNumber getReal() const;
    // Чтобы работало auto нужно в tasks.json 
    // в разделе args прописать `-std=c++20`
    void setReal(auto _real); 
    RationalNumber getImaginary() const; 
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

		// Выводит тригонометрическую форму
		void printTrigonometric();
		// Выводит экспоненциальную форму 
		void printExponential();

    // Дружественные функции 
    friend std::ostream &operator<<(std::ostream &terminal, const ComplexNumber &number); 
    friend ComplexNumber operator+(ComplexNumber &left, ComplexNumber &right);
    
    // Указываем два шаблона 
    // typename U - для типа, с которым был инициализирован экземпляр класса 
    // typename V - для типа, с каким подаётся число
    template<typename V>
    friend ComplexNumber operator+(ComplexNumber &left, V number);
    
    template<typename V>
    friend ComplexNumber operator+(V number, ComplexNumber &right);
    
    friend ComplexNumber operator-(ComplexNumber &left, ComplexNumber &right);
    
    template<typename V>
    friend ComplexNumber operator-(ComplexNumber &left, V number);
    
    template<typename V>
    friend ComplexNumber operator-(V number, ComplexNumber &right);
  
    friend ComplexNumber operator*(ComplexNumber &left, ComplexNumber &right);
    
    template<typename V>
    friend ComplexNumber operator*(ComplexNumber &left, V number);
    
    template<typename V>
    friend ComplexNumber operator*(V number, ComplexNumber &right);
    
    friend ComplexNumber operator/(ComplexNumber &left, ComplexNumber &right);
    
    template<typename V>
    friend ComplexNumber operator/(ComplexNumber &left, V number);

    template<typename V>
    friend ComplexNumber operator/(V number, ComplexNumber &right);

    friend bool operator==(ComplexNumber &left, ComplexNumber &right);

    friend bool operator!=(ComplexNumber &left, ComplexNumber &right);
};

#endif