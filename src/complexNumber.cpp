#include <iostream>
#include <cmath>
#include <concepts>
#include "../include/complexNumber.h"
#include <type_traits>
#include <variant>
#include <string>


// Переводим число из int, float, double в double, потому что класс у нас построен на double 
// Когда мы пишем template вот так раздельно, а не template<typename T, typename V>, то это
// позволяет отказаться от переписывания всей стуктуры когда, где 
// ComlpexNumber<T> меняется везде на ComplexNumber<T, V>
// а так мы вводим частный дженерик 
template<typename V>
double ComplexNumber::toDouble(const V& value) {
    if (std::is_same_v<V, int> || std::is_same_v<V, float> || std::is_same_v<V, double>){
        return static_cast<double>(value);
    } else {
        throw std::invalid_argument("Unsupported type!");
    }
}

// Конструктор класса со списком инициализации после :
ComplexNumber::ComplexNumber(Real r, Imag i) : real(r), imaginary(i) {}

// Геттер для действительной части
double ComplexNumber::getReal() const   
{
    return real.value;
}

// Сеттер для действительной части
void ComplexNumber::setReal(auto _real)
{
  real.value = toDouble(_real);
}

// Геттер для мнимой части
double ComplexNumber::getImaginary() const 
{
    return imaginary.value;
}

// Сеттер для мнимой части 
void ComplexNumber::setImaginary(auto _imaginary)
{
    imaginary.value = toDouble(_imaginary);
}

// Находим модуль |C| = sqrt(a^2 + b^2)
double ComplexNumber::abs()
{
		double _real = real.value;
		double _imaginary = imaginary.value;
    return sqrt(_real * _real + _imaginary * _imaginary);
}


// Находим аргумент фи
double ComplexNumber::arg()
{
		double _real = real.value;
		double _imaginary = imaginary.value;
    return atan(_imaginary / _real);
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
    imaginary.value = r * sin(degree * arg);
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
    real.value += toDouble(number);
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
    real.value -= toDouble(number);
}

// Перегрузка оператора *= для ариф. действий с комплексными числами
void ComplexNumber::operator*=(ComplexNumber &other)
{
    // Формула умножения (a1 * a2 - b1 * b2) + (a1 * b2 - b1 * a2)i
    double a1 = real.value;
    double a2 = other.real.value;
    double b1 = imaginary.value;
    double b2 = other.imaginary.value;
    real.value = (a1 * a2) - (b1 * b2);
    imaginary.value = (a1 * b2) + (b1 * a2);
}

// Перегрузка оператора -= для ариф. действий с int, float, double
void ComplexNumber::operator*=(auto number)
{
    // (a*c) + (b*c)i
    double a = real.value;
    double b = imaginary.value;
    double c = toDouble(number);
    real.value = a * c;
    imaginary.value = b * c;
}

// Перегрузка оператора /= для ариф. действий с комплексными числами
void ComplexNumber::operator/=(ComplexNumber &other)
{
    // Формула ( (a1 * a2 + b1 * b2) + (b1 * a2 - a1 * b2)i ) / mod
    double a1 = real.value;
    double a2 = other.real.value;
    double b1 = imaginary.value;
    double b2 = other.imaginary.value;
    double mod = a2 * a2 + b2 * b2;
    real.value = (a1 * a2 + b1 * b2) / mod;
    imaginary.value = (b1 * a2 - a1 * b2) / mod;
}

// Перегрузка оператора /= для ариф. действий с int, float, double
void ComplexNumber::operator/=(auto number)
{
    // (a/c) + (b/c)i
    double a = real.value;
    double b = imaginary.value;
    double c = toDouble(number);
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
    if (number.getImaginary() >= 0)
    {
        // Если мнимая часть положительна, то + 
        terminal << number.getReal() << " + " << number.getImaginary() << "i";
    }
    else
    {
        // Если мнимая часть отрицательна, то - 
        terminal << number.getReal() << " - " << std::abs(number.getImaginary()) << "i";
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
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(Real(left.getReal() + c), Imag(left.getImaginary()));
}

// Перегрузка оператора + для int, float, double (когда число справа)
template<typename V>
ComplexNumber operator+(V number, ComplexNumber &right)
{
    double c = ComplexNumber::toDouble(number);
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
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(Real(left.getReal - c), Imag(left.getImaginary));
}

// Перегрузка оператора - для int, float, double (когда число справа)
template<typename V>
ComplexNumber operator-(V number, ComplexNumber &right)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(Real(c - right.getReal()), Imag(right.getImaginary()));
}

// Перегрузка оператора * для комплексных чисел
ComplexNumber operator*(ComplexNumber &left, ComplexNumber &right)
{
    // Формула умножения (a1 * a2 - b1 * b2) + (a1 * b2 - b1 * a2)i
    double a1 = left.getReal();
    double a2 = right.getReal();
    double b1 = left.getImaginary();
    double b2 = right.getImaginary();
    Real real = Real((a1 * a2) - (b1 * b2));
    Imag imaginary = Imag((a1 * b2) + (b1 * a2));
    return ComplexNumber(real, imaginary);
}

// Перегрузка оператора * для int, float, double (когда число слева)
template<typename V>
ComplexNumber operator*(ComplexNumber &left, V number)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(Real(left.getReal() * c), Imag(left.getImaginary() * c));
}

// Перегрузка оператора * для int, float, double (когда число справа)
template<typename V>
ComplexNumber operator*(V number, ComplexNumber &right)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(Real(right.getReal() * c), Imag(right.getImaginary() * c));
}

// Перегрузка оператора / для комплексных чисел
ComplexNumber operator/(ComplexNumber &left, ComplexNumber &right)
{
    // Формула ( (a1 * a2 + b1 * b2) + (b1 * a2 - a1 * b2)i ) / mod
    double a1 = left.getReal();
    double b1 = left.getImaginary();
    double a2 = right.getReal();
    double b2 = right.getImaginary();
    double mod = (a2 * a2) + (b2 * b2); 
    Real real = Real(((a1 * a2) + (b1 * b2)) / mod);   
    Imag imaginary = Imag(((b1 * a2) - (a1 * b2)) / mod);
    return ComplexNumber(real, imaginary);
}

// Перегрузка оператора / для int, float, double (когда число слева)
template<typename V>
ComplexNumber operator/(ComplexNumber &left, V number)
{
    double c = ComplexNumber::toDouble(number);
    return ComplexNumber(Real(left.getReal() / c), Imag(left.getImaginary() / c));
}

// Перегрузка оператора / для int, float, double (когда число справа)
template<typename V>
ComplexNumber operator/(V number, ComplexNumber &right)
{
    // формула, когда константа делится на комплексное:
    // (c*a / (a^2 + b^2)) - (c*b / (a^2 + b^2))i
    double c = ComplexNumber::toDouble(number);
    double a = right.getReal();
    double b = right.getImaginary();
    double denom = (a * a + b * b); // denominator - знаменатель
   	Real real = Real((c * a) / denom);
  	Imag imaginary = Imag((c * b) / denom);
    return ComplexNumber(real, imaginary);
}

// Перегрузка оператора сравнения == 
bool operator==(ComplexNumber &left, ComplexNumber &right)
{
    double a1 = left.getReal();
    double b1 = left.getImaginary();
    double a2 = right.getReal();
    double b2 = right.getImaginary();
    return (a1 == a2) && (b1 == b2);
}

// Перегрузка оператора сравнения != 
bool operator!=(ComplexNumber &left, ComplexNumber &right)
{
    double a1 = left.getReal();
    double b1 = left.getImaginary();
    double a2 = right.getReal();
    double b2 = right.getImaginary();
    return (a1 != a2) || (b1 != b2);
}