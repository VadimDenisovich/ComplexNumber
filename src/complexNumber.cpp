#include <iostream>
#include <cmath>
#include <concepts>
#include "../include/complexNumber.h"
#include <type_traits>
#include <variant>
#include <string>
#include "../include/rationalNumber.h"

// Конструктор класса со списком инициализации после :
ComplexNumber::ComplexNumber(Real r, Imag i) : real(Real(r)), imaginary(Imag(i)) {}


// Геттер для действительной части
RationalNumber ComplexNumber::getReal() const   
{
    return real.value;
}

// Сеттер для действительной части
void ComplexNumber::setReal(auto _real)
{
  real.value = RationalNumber::toRationalNumber(_real);
}

// Геттер для мнимой части
RationalNumber ComplexNumber::getImaginary() const 
{
    return imaginary.value;
}

// Сеттер для мнимой части 
void ComplexNumber::setImaginary(auto _imaginary)
{
    imaginary.value = RationalNumber::toRationalNumber(_imaginary);
}

// Находим модуль |C| = sqrt(a^2 + b^2)
double ComplexNumber::abs()
{
		RationalNumber _real = real.value;
		RationalNumber _imaginary = imaginary.value;
		RationalNumber expression = _real * _real + _imaginary * _imaginary; 
    return sqrt(expression.toDouble());
}


// Находим аргумент фи
double ComplexNumber::arg()
{
		RationalNumber _real = real.value;
		RationalNumber _imaginary = imaginary.value;
		RationalNumber expression = _imaginary / _real; 
    return atan(expression.toDouble());
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
    real.value = r * cos(degree * arg);
    // изменяем мнимую часть
    imaginary.value = RationalNumber::toRationalNumber(r * sin(degree * arg));
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
    real.value += other.real.value;
    imaginary.value += other.imaginary.value;
}

// Перегрузка оператора += для ариф. действий с int, float, double
void ComplexNumber::operator+=(auto number)
{
    real.value += RationalNumber::toRationalNumber(number);
}

// Перегрузка оператора -= для ариф. действий с комплексными числами
void ComplexNumber::operator-=(ComplexNumber &other)
{
    real.value -= other.real.value;
    imaginary.value -= other.imaginary.value;
}

// Перегрузка оператора -= для ариф. действий с int, float, double
void ComplexNumber::operator-=(auto number)
{
    real.value -= RationalNumber::toRationalNumber(number);
}

// Перегрузка оператора *= для ариф. действий с комплексными числами
void ComplexNumber::operator*=(ComplexNumber &other)
{
    // Формула умножения (a1 * a2 - b1 * b2) + (a1 * b2 - b1 * a2)i
    RationalNumber a1 = real.value;
   	RationalNumber a2 = other.real.value;
    RationalNumber b1 = imaginary.value;
    RationalNumber b2 = other.imaginary.value;
    real.value = (a1 * a2) - (b1 * b2);
    imaginary.value = (a1 * b2) + (b1 * a2);
}

// Перегрузка оператора -= для ариф. действий с int, float, double
void ComplexNumber::operator*=(auto number)
{
    // (a*c) + (b*c)i
    RationalNumber a = real.value;
    RationalNumber b = imaginary.value;
    RationalNumber c = RationalNumber::toRationalNumber(number);
    real.value = a * c;
    imaginary.value = b * c;
}

// Перегрузка оператора /= для ариф. действий с комплексными числами
void ComplexNumber::operator/=(ComplexNumber &other)
{
    // Формула ( (a1 * a2 + b1 * b2) + (b1 * a2 - a1 * b2)i ) / mod
    RationalNumber a1 = real.value;
    RationalNumber a2 = other.real.value;
    RationalNumber b1 = imaginary.value;
    RationalNumber b2 = other.imaginary.value;
    RationalNumber mod = a2 * a2 + b2 * b2;
    real.value = (a1 * a2 + b1 * b2) / mod;
    imaginary.value = (b1 * a2 - a1 * b2) / mod;
}

// Перегрузка оператора /= для ариф. действий с int, float, double
void ComplexNumber::operator/=(auto number)
{
    // (a/c) + (b/c)i
    RationalNumber a = real.value;
    RationalNumber b = imaginary.value;
    RationalNumber c = RationalNumber::toRationalNumber(number);
    real.value = a / c;
    imaginary.value = b / c;
}

// Перегрузка унарного оператора - для смены знака
ComplexNumber ComplexNumber::operator-()
{
    real.value = -real.value;
    imaginary.value = -imaginary.value;
    return *this;
}

// Вывод тригонометрической формыл 
void ComplexNumber::printTrigonometric() {
	std::cout << abs() << "(cos(" << arg() << ")" << " + " << "isin(" << arg() << ")" << std::endl;
}

// Выводит экспоненциальную форму 
void ComplexNumber::printExponential() {
	std::cout << abs() << "e^" << arg() << std::endl;
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
		// TODO: 
		// 1. Превращение в Double из Rational
    if (number.getImaginary().toDouble() >= 0)
    {
        // Если мнимая часть положительна, то + 
        terminal << number.getReal().toDouble() << " + " << number.getImaginary().toDouble() << "i";
    }
    else
    {
        // Если мнимая часть отрицательна, то - 
        terminal << number.getReal().toDouble() << " - " << std::abs(number.getImaginary().toDouble()) << "i";
    }

    // Возвращает цепочку вывода в основную цепочку
    return terminal;
}

// Перегрузка оператора + для комплексных чисел
ComplexNumber operator+(ComplexNumber &left, ComplexNumber &right)
{
    return ComplexNumber(Real(left.getReal() + right.getReal()), Imag(left.getImaginary() + right.getImaginary()));
}

// Перегрузка оператора + для int, float, double (когда число слева)
template<typename V>
ComplexNumber operator+(ComplexNumber &left, V number)
{
    // Пишем ComplexNumber::toDouble(number), потому что перегрузка оператора +
    // является дружественной и она не может просто обратиться
    // к методу toDouble, нужно указать, что мы берём этот статический метод
    // у класса ComplexNumber

		// Создаем из чилса рациональное число 
    RationalNumber c = RationalNumber::toRationalNumber(number);
    return ComplexNumber(Real(left.getReal() + c), Imag(left.getImaginary()));
}

// Перегрузка оператора + для int, float, double (когда число справа)
template<typename V>
ComplexNumber operator+(V number, ComplexNumber &right)
{
    RationalNumber c = RationalNumber::toRationalNumber(number);
    return ComplexNumber(Real(right.getReal() + c), Imag(right.getImaginary()));
}

// Перегрузка оператора - для комплексных чисел
ComplexNumber operator-(ComplexNumber &left, ComplexNumber &right)
{
    return ComplexNumber(Real(left.getReal() - right.getReal()), Imag(left.getImaginary() - right.getImaginary()));
}

// Перегрузка оператора - для int, float, double (когда число слева)
template<typename V>
ComplexNumber operator-(ComplexNumber &left, V number)
{
    RationalNumber c = RationalNumber::toRationalNumber(number);
    return ComplexNumber(Real(left.getReal() - c), Imag(left.getImaginary()));
}

// Перегрузка оператора - для int, float, double (когда число справа)
template<typename V>
ComplexNumber operator-(V number, ComplexNumber &right)
{
    RationalNumber c = RationalNumber::toRationalNumber(number);
    return ComplexNumber(Real(c - right.getReal()), Imag(right.getImaginary()));
}

// Перегрузка оператора * для комплексных чисел
ComplexNumber operator*(ComplexNumber &left, ComplexNumber &right)
{
    // Формула умножения (a1 * a2 - b1 * b2) + (a1 * b2 - b1 * a2)i
    RationalNumber a1 = left.getReal();
    RationalNumber a2 = right.getReal();
    RationalNumber b1 = left.getImaginary();
    RationalNumber b2 = right.getImaginary();
    Real real = Real((a1 * a2) - (b1 * b2));
    Imag imaginary = Imag((a1 * b2) + (b1 * a2));
    return ComplexNumber(real, imaginary);
}

// Перегрузка оператора * для int, float, double (когда число слева)
template<typename V>
ComplexNumber operator*(ComplexNumber &left, V number)
{
    RationalNumber c = RationalNumber::toRationalNumber(number);
    return ComplexNumber(Real(left.getReal() * c), Imag(left.getImaginary() * c));
}

// Перегрузка оператора * для int, float, double (когда число справа)
template<typename V>
ComplexNumber operator*(V number, ComplexNumber &right)
{	
		RationalNumber c = RationalNumber::toRationalNumber(number);
    return ComplexNumber(Real(right.getReal() * c), Imag(right.getImaginary() * c));
}

// Перегрузка оператора / для комплексных чисел
ComplexNumber operator/(ComplexNumber &left, ComplexNumber &right)
{
    // Формула ( (a1 * a2 + b1 * b2) + (b1 * a2 - a1 * b2)i ) / mod
    RationalNumber a1 = left.getReal();
   	RationalNumber b1 = left.getImaginary();
    RationalNumber a2 = right.getReal();
    RationalNumber b2 = right.getImaginary();
    RationalNumber mod = (a2 * a2) + (b2 * b2); 
    Real real = Real(((a1 * a2) + (b1 * b2)) / mod);   
    Imag imaginary = Imag(((b1 * a2) - (a1 * b2)) / mod);
    return ComplexNumber(real, imaginary);
}

// Перегрузка оператора / для int, float, double (когда число слева)
template<typename V>
ComplexNumber operator/(ComplexNumber &left, V number)
{
    RationalNumber c = RationalNumber::toRationalNumber(number);
    return ComplexNumber(Real(left.getReal() / c), Imag(left.getImaginary() / c));
}

// Перегрузка оператора / для int, float, double (когда число справа)
template<typename V>
ComplexNumber operator/(V number, ComplexNumber &right)
{
    // формула, когда константа делится на комплексное:
    // (c*a / (a^2 + b^2)) - (c*b / (a^2 + b^2))i
    RationalNumber c = RationalNumber::toRationalNumber(number);
    RationalNumber a = right.getReal();
    RationalNumber b = right.getImaginary();
    RationalNumber denom = (a * a + b * b); // denominator - знаменатель
   	Real real = Real((c * a) / denom);
  	Imag imaginary = Imag((c * b) / denom);
    return ComplexNumber(real, imaginary);
}

// Перегрузка оператора сравнения == 
bool operator==(ComplexNumber &left, ComplexNumber &right)
{
    RationalNumber a1 = left.getReal();
    RationalNumber b1 = left.getImaginary();
    RationalNumber a2 = right.getReal();
    RationalNumber b2 = right.getImaginary();
    return (a1 == a2) && (b1 == b2);
}

// Перегрузка оператора сравнения != 
bool operator!=(ComplexNumber &left, ComplexNumber &right)
{
    RationalNumber a1 = left.getReal();
    RationalNumber b1 = left.getImaginary();
    RationalNumber a2 = right.getReal();
    RationalNumber b2 = right.getImaginary();
    return (a1 != a2) || (b1 != b2);
}
