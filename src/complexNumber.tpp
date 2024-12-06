#include <iostream>
#include <cmath>
#include <concepts>
#include "../include/complexNumber.h"
#include <type_traits>
#include <variant>
#include <string>

// Проверяем тип данных. Если int, float, double, то возвращаем double
// Если нет, то вызывается ошибка 
template<typename T>
double ComplexNumber<T>::toDouble(const T& value) {
    return static_cast<double>(value); 
}


template<typename T>
// Конструктор класса со списком инициализации после :
ComplexNumber<T>::ComplexNumber(T r, double i) : real(toDouble(r)), imaginary(i) {}

// Геттер для действительной части
template<typename T>
double ComplexNumber<T>::getReal()
{
    return real;
}

// Сеттер для действительной части
template<typename T>
void ComplexNumber<T>::setReal(T _real)
{
    real = toDouble(_real);
}

// Геттер для мнимой части
template<typename T>
double ComplexNumber<T>::getImaginary()
{
    return imaginary;
}

template<typename T>
void ComplexNumber<T>::setImaginary(T _imaginary)
{
    imaginary = toDouble(_imaginary);
}

// Находим модуль |C| = sqrt(a^2 + b^2)
template<typename T>
double ComplexNumber<T>::abs()
{
    return sqrt(real * real + imaginary * imaginary);
}


// Находим аргумент фи
template<typename T>
double ComplexNumber<T>::arg()
{
    return atan(imaginary / real);
}

// Получаем на вход степень
// r^n(cos(n * arg()) + i * sin(n * arg()))
template<typename T>
void ComplexNumber<T>::factorization(int degree)
{
    // Получаем r^n
    // pow(число, степень)
    double r = pow(abs(), degree);
    // получаем аргумент
    double arg = this->arg();
    // изменяем действительное число
    real = r * cos(degree * arg);
    // изменяем мнимую часть
    imaginary = r * sin(degree * arg);
}

// Перегрузка оператора присваивания (копируем поля другого комп. числа)
template<typename T>
ComplexNumber<T> ComplexNumber<T>::operator=(const ComplexNumber<T> &other)
{
    // Проверяем, чтобы избежать самоприсваивания.
    if (this == &other)
    {
        // *this разымениование указателя *this, чтобы возвращать
        // не ссылку на объект, а сам объект (ссылку на него)
        return *this;
    }
    real = other.real;
    imaginary = other.imaginary;
    return *this;
}

// Перегрузка оператора += для ариф. действий с комплексными числами (др. классом)
template<typename T>
void ComplexNumber<T>::operator+=(ComplexNumber &other)
{
    real += other.real;
    imaginary += other.imaginary;
}

// Перегрузка оператора += для ариф. действий с int, float, double
template<typename T>
void ComplexNumber<T>::operator+=(T number)
{
    real += toDouble(number);
}

// Перегрузка оператора -= для ариф. действий с комплексными числами
template<typename T>
void ComplexNumber<T>::operator-=(ComplexNumber &other)
{
    real -= other.real;
    imaginary -= other.imaginary;
}

// Перегрузка оператора -= для ариф. действий с int, float, double
template<typename T>
void ComplexNumber<T>::operator-=(T number)
{
    real -= toDouble(number);
}

// Перегрузка оператора *= для ариф. действий с комплексными числами
template<typename T>
void ComplexNumber<T>::operator*=(ComplexNumber &other)
{
    // Формула умножения (a1 * a2 - b1 * b2) + (a1 * b2 - b1 * a2)i
    double a1 = real;
    double a2 = other.real;
    double b1 = imaginary;
    double b2 = other.imaginary;
    real = (a1 * a2) - (b1 * b2);
    imaginary = (a1 * b2) - (b1 * a2);
}

// Перегрузка оператора -= для ариф. действий с int, float, double
template<typename T>
void ComplexNumber<T>::operator*=(T number)
{
    // (a*c) + (b*c)i
    double a = real;
    double b = imaginary;
    double c = toDouble(number);
    real = a * c;
    imaginary = b * c;
}

// Перегрузка оператора /= для ариф. действий с комплексными числами
template<typename T>
void ComplexNumber<T>::operator/=(ComplexNumber &other)
{
    // Формула ( (a1 * a2 + b1 * b2) + (b1 * a2 - a1 * b2)i ) / mod
    double a1 = real;
    double a2 = other.real;
    double b1 = imaginary;
    double b2 = other.imaginary;
    double mod = a2 * a2 + b2 * b2;
    real = (a1 * a2 + b1 * b2) / mod;
    imaginary = (b1 * a2 - a1 * b2) / mod;
}

// Перегрузка оператора /= для ариф. действий с int, float, double
template<typename T>
void ComplexNumber<T>::operator/=(T number)
{
    // (a/c) + (b/c)i
    double a = real;
    double b = imaginary;
    double c = toDouble(number);
    real = a / c;
    imaginary = b / c;
}

// Перегрузка унарного оператора - для смены знака
template<typename T>
ComplexNumber<T> ComplexNumber<T>::operator-()
{
    real = -real;
    imaginary = -imaginary;
    return *this;
}

// Перегрузка оператора вывода в поток <<
// Мы объявляем эту функцию, как дружественную (friend), потому что операторы << и >>
// не могут быть объявлены внутри класса, поскольку левые операнды выражения
// например, std::ostream, не являются объектами этого класса
// std::ostream (левый операнд) << c1 << std::endl;
// std::ostream& стоит амперсанд, потому что мы возвращаем ссылку на объект
//
// std::ostream& terminal - ссылка на объект std::cout
template<typename T>
std::ostream &operator<<(std::ostream &terminal, const ComplexNumber<T> &number)
{
    if (number.imaginary >= 0)
    {
        terminal << number.real << " + " << number.imaginary << "i";
    }
    else
    {
        terminal << number.real << " - " << std::abs(number.imaginary) << "i";
    }

    // Возвращает цепочку вывода в основную цепочку
    return terminal;
}

// Перегрузка оператора + для комплексных чисел
template<typename T>
ComplexNumber<double> operator+(ComplexNumber<T> &left, ComplexNumber<T> &right)
{
    return ComplexNumber<double>(left.real + right.real, left.imaginary + right.imaginary);
}

// Перегрузка оператора + для int, float, double (когда число слева)
template<typename T, typename V>
ComplexNumber<double> operator+(ComplexNumber<T> &left, V number)
{
    // Пишем ComplexNumber::toDouble(number), потому что перегрузка оператора +
    // является дружественной и она не может просто обратиться
    // к методу toDouble, нужно указать, что мы берём этот статический метод
    // у класса ComplexNumber
    double c = ComplexNumber<T>::toDouble(number);
    return ComplexNumber<double>(left.real + c, left.imaginary);
}

// Перегрузка оператора + для int, float, double (когда число справа)
template<typename T, typename V>
ComplexNumber<double> operator+(V number, ComplexNumber<T> &right)
{
    double c = ComplexNumber<T>::toDouble(number);
    return ComplexNumber<double>(right.real + c, right.imaginary);
}

// Перегрузка оператора - для комплексных чисел
template<typename T>
ComplexNumber<double> operator-(ComplexNumber<T> &left, ComplexNumber<T> &right)
{
    return ComplexNumber<double>(left.real - right.real, left.imaginary - right.imaginary);
}

// Перегрузка оператора - для int, float, double (когда число слева)
template<typename T, typename V>
ComplexNumber<double> operator-(ComplexNumber<T> &left, V number)
{
    double c = ComplexNumber<T>::toDouble(number);
    return ComplexNumber<double>(left.real - c, left.imaginary);
}

// Перегрузка оператора - для int, float, double (когда число справа)
template<typename T, typename V>
ComplexNumber<double> operator-(V number, ComplexNumber<T> &right)
{
    double c = ComplexNumber<T>::toDouble(number);
    return ComplexNumber<double>(c - right.real, right.imaginary);
}

// Перегрузка оператора * для комплексных чисел
template<typename T>
ComplexNumber<double> operator*(ComplexNumber<T> &left, ComplexNumber<T> &right)
{
    // Формула умножения (a1 * a2 - b1 * b2) + (a1 * b2 - b1 * a2)i
    double a1 = left.real;
    double a2 = right.real;
    double b1 = left.imaginary;
    double b2 = right.imaginary;
    double real = (a1 * a2) - (b1 * b2);
    double imaginary = (a1 * b2) + (b1 * a2);
    return ComplexNumber<double>(real, imaginary);
}

// Перегрузка оператора * для int, float, double (когда число слева)
template<typename T, typename V>
ComplexNumber<double> operator*(ComplexNumber<T> &left, V number)
{
    double c = ComplexNumber<T>::toDouble(number);
    return ComplexNumber<double>(left.real * c, left.imaginary * c);
}

// Перегрузка оператора * для int, float, double (когда число справа)
template<typename T, typename V>
ComplexNumber<double> operator*(V number, ComplexNumber<T> &right)
{
    double c = ComplexNumber<T>::toDouble(number);
    return ComplexNumber<double>(right.real * c, right.imaginary * c);
}

// Перегрузка оператора / для комплексных чисел
template<typename T>
ComplexNumber<double> operator/(ComplexNumber<T> &left, ComplexNumber<T> &right)
{
    // Формула ( (a1 * a2 + b1 * b2) + (b1 * a2 - a1 * b2)i ) / mod
    double a1 = left.real;
    double b1 = left.imaginary;
    double a2 = right.real;
    double b2 = right.imaginary;
    double mod = (a2 * a2) + (b2 * b2); 
    double real = ((a1 * a2) + (b1 * b2)) / mod;   
    double imaginary = ((b1 * a2) - (a1 * b2)) / mod;
    return ComplexNumber<double>(real, imaginary);
}

// Перегрузка оператора / для int, float, double (когда число слева)
template<typename T, typename V>
ComplexNumber<double> operator/(ComplexNumber<T> &left, V number)
{
    double c = ComplexNumber<T>::toDouble(number);
    return ComplexNumber<double>(left.real / c, left.imaginary / c);
}

// Перегрузка оператора / для int, float, double (когда число справа)
template<typename T, typename V>
ComplexNumber<double> operator/(V number, ComplexNumber<T> &right)
{
    // формула, когда константа делится на комплексное:
    // (c*a / (a^2 + b^2)) - (c*b / (a^2 + b^2))i
    double c = ComplexNumber<T>::toDouble(number);
    double a = right.real;
    double b = right.imaginary;
    double denom = (a * a + b * b); // denominator - знаменатель
    double real = (c * a) / denom;
    double imaginary = (c * b) / denom;
    return ComplexNumber<double>(real, imaginary);
}

template<typename T>
bool operator==(ComplexNumber<T> &left, ComplexNumber<T> &right)
{
    double a1 = left.real;
    double b1 = left.imaginary;
    double a2 = right.real;
    double b2 = right.imaginary;
    return (a1 == a2) && (b1 == b2);
}

template<typename T>
bool operator!=(ComplexNumber<T> &left, ComplexNumber<T> &right)
{
    double a1 = left.real;
    double b1 = left.imaginary;
    double a2 = right.real;
    double b2 = right.imaginary;
    return (a1 != a2) || (b1 != b2);
}