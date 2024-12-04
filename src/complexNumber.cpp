#include <iostream>
#include <cmath>
#include <concepts>
#include "../include/complexNumber.h"
#include <type_traits>
#include <variant>

// Переводим из IntFloatDoubleType в double
// (Разобраться детальнее, как работает функция!)
double ComplexNumber::toDouble(const IntFloatDoubleType &real)
{
    return std::visit([](auto &&number) -> double
                      { return (double)number; }, real);
}

// Специальный тип данных, позволяющий передавать на выбор <int, float, double>
// на случай, если наше число задаётся
using IntFloatDoubleType = std::variant<int, float, double>;

// Конструктор класса со списком инициализации после :
ComplexNumber::ComplexNumber(IntFloatDoubleType r, double i) : real(toDouble(r)), imaginary(i) {};

// Геттер для действительной части
double ComplexNumber::getReal()
{
    return real;
}

// Сеттер для действительной части
void ComplexNumber::setReal(IntFloatDoubleType _real)
{
    real = toDouble(_real);
}

// Геттер для мнимой части
double ComplexNumber::getImaginary()
{
    return imaginary;
}

// Сеттер для мнимой части
void ComplexNumber::setImaginary(IntFloatDoubleType _imaginary)
{
    imaginary = toDouble(_imaginary);
}

// Находим модуль |C| = sqrt(a^2 + b^2)
double ComplexNumber::abs()
{
    return sqrt(real * real + imaginary * imaginary);
}

// Находим аргумент фи
double ComplexNumber::arg()
{
    return atan(imaginary / real);
}

// Получаем на вход степень
// r^n(cos(n * arg()) + i * sin(n * arg()))
void ComplexNumber::factorization(int degree)
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
ComplexNumber ComplexNumber::operator=(const ComplexNumber &other)
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
void ComplexNumber::operator+=(ComplexNumber &other)
{
    real += other.real;
    imaginary += other.imaginary;
}

// Перегрузка оператора += для ариф. действий с int, float, double
void ComplexNumber::operator+=(IntFloatDoubleType number)
{
    real += toDouble(number);
}

// Перегрузка оператора -= для ариф. действий с комплексными числами
void ComplexNumber::operator-=(ComplexNumber &other)
{
    real -= other.real;
    imaginary -= other.imaginary;
}

// Перегрузка оператора -= для ариф. действий с int, float, double
void ComplexNumber::operator-=(IntFloatDoubleType number)
{
    real -= toDouble(number);
}

// Перегрузка оператора *= для ариф. действий с комплексными числами
void ComplexNumber::operator*=(ComplexNumber &other)
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
void ComplexNumber::operator*=(IntFloatDoubleType number)
{
    // (a*c) + (b*c)i
    double a = real;
    double b = imaginary;
    double c = toDouble(number);
    real = a * c;
    imaginary = b * c;
}

// Перегрузка оператора /= для ариф. действий с комплексными числами
void ComplexNumber::operator/=(ComplexNumber &other)
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
void ComplexNumber::operator/=(IntFloatDoubleType number)
{
    // (a/c) + (b/c)i
    double a = real;
    double b = imaginary;
    double c = toDouble(number);
    real = a / c;
    imaginary = b / c;
}

// Перегрузка унарного оператора - для смены знака
ComplexNumber ComplexNumber::operator-()
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
std::ostream &operator<<(std::ostream &terminal, const ComplexNumber &number)
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
ComplexNumber operator+(ComplexNumber &left, ComplexNumber &right)
{
    return ComplexNumber(left.real + right.real, left.imaginary + right.imaginary);
}

// Перегрузка оператора + для int, float, double (когда число слева)
ComplexNumber operator+(ComplexNumber &left, IntFloatDoubleType number)
{
    // Пишем ComplexNumber::toDouble(number), потому что перегрузка оператора +
    // является дружественной и она не может просто обратиться
    // к методу toDouble, нужно указать, что мы берём этот статический метод
    // у класса ComplexNumber
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(left.real + c, left.imaginary);
}

// Перегрузка оператора + для int, float, double (когда число справа)
ComplexNumber operator+(IntFloatDoubleType number, ComplexNumber &right)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(right.real + c, right.imaginary);
}

// Перегрузка оператора - для комплексных чисел
ComplexNumber operator-(ComplexNumber &left, ComplexNumber &right)
{
    return ComplexNumber(left.real - right.real, left.imaginary - right.imaginary);
}

// Перегрузка оператора - для int, float, double (когда число слева)
ComplexNumber operator-(ComplexNumber &left, IntFloatDoubleType number)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(left.real - c, left.imaginary);
}

// Перегрузка оператора - для int, float, double (когда число справа)
ComplexNumber operator-(IntFloatDoubleType number, ComplexNumber &right)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(c - right.real, right.imaginary);
}

// Перегрузка оператора * для комплексных чисел
ComplexNumber operator*(ComplexNumber &left, ComplexNumber &right)
{
    // Формула умножения (a1 * a2 - b1 * b2) + (a1 * b2 - b1 * a2)i
    double a1 = left.real;
    double a2 = right.real;
    double b1 = left.imaginary;
    double b2 = right.imaginary;
    double real = (a1 * a2) - (b1 * b2);
    double imaginary = (a1 * b2) - (b1 * a2);
    return ComplexNumber(real, imaginary);
}

// Перегрузка оператора * для int, float, double (когда число слева)
ComplexNumber operator*(ComplexNumber &left, IntFloatDoubleType number)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(left.real * c, left.imaginary * c);
}

// Перегрузка оператора * для int, float, double (когда число справа)
ComplexNumber operator*(IntFloatDoubleType number, ComplexNumber &right)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(right.real * c, right.imaginary * c);
}

ComplexNumber operator/(ComplexNumber &left, ComplexNumber &right)
{
    // Формула ( (a1 * a2 + b1 * b2) + (b1 * a2 - a1 * b2)i ) / mod
    double a1 = left.real;
    double b1 = left.imaginary;
    double a2 = right.real;
    double b2 = right.imaginary;
    double mod = a2 * a2 + b2 * b2;
    double real = (a1 * a2 + b1 * b2) / mod;
    double imaginary = (b1 * a2 - a1 * b2) / mod;
    return ComplexNumber(real, imaginary);
}

// Перегрузка оператора / для int, float, double (когда число слева)
ComplexNumber operator/(ComplexNumber &left, IntFloatDoubleType number)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(left.real / c, left.imaginary / c);
}

// Перегрузка оператора / для int, float, double (когда число справа)
ComplexNumber operator/(IntFloatDoubleType number, ComplexNumber &right)
{
    // формула, когда константа делится на комплексное: 
    // (c*a / (a^2 + b^2)) - (c*b / (a^2 + b^2))i 
    double c = ComplexNumber::toDouble(number);
    double a = right.real; 
    double b = right.imaginary;
    double denom = (a*a + b*b); // denominator - знаменатель
    double real = (c * a) / denom; 
    double imaginary = (c * b) / denom; 
    return ComplexNumber(real, imaginary);
}

bool operator==(ComplexNumber &left, ComplexNumber &right)
{
    double a1 = left.real;
    double b1 = left.imaginary;
    double a2 = right.real;
    double b2 = right.imaginary;
    return (a1 == a2) && (b1 == b2);
}

bool operator!=(ComplexNumber &left, ComplexNumber &right)
{
    double a1 = left.real;
    double b1 = left.imaginary;
    double a2 = right.real;
    double b2 = right.imaginary;
    return (a1 != a2) || (b1 != b2);
}