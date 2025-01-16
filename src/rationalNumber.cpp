#include "../include/rationalNumber.h"
#include <stdexcept>
#include <sstream>
#include <cassert>
#include <iomanip>
#include <limits>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <charconv> 

// Десериализация из RationalNumber 
double RationalNumber::toDouble() {
	// double _num = static_cast<double>(numerator);
	// double _denom = static_cast<double>(denominator);
  // return _num / _denom; 
	return static_cast<double>(numerator) / denominator;
}

// Алгоритм Евклида для вычисления НОД
long long RationalNumber::_findGCD(long long a, long long b)
{
	// Базовый случай: Если число b равно нулю, ф-ия возвращает абсолютное значение
	// первого числа.
	// Основано на св-ве: НОД любого числа или нуля равен самому числу.
	if (b == 0)
	{
		return abs(a);
	}
	// Рекурсия: Если число b не равно нулю, ф-ия вызывает саму себя,
	// передавая b в качестве первого аргумента, а остаток от деления a % b в качестве
	// второго аргумента
	// Это последовательно уменьшает пары чисел для достижения Базового случая
	return _findGCD(b, a % b);
}


// Функция для подсчёта цифр после запятой (работает только с double)
int RationalNumber::_countDecimalPlaces(double number) {
	std::array<char, 32> buffer;
	auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), number, std::chars_format::fixed, 10);

	if (result.ec == std::errc()) {
		std::string s(buffer.data(), result.ptr);
		std::reverse(s.begin(), s.end());

		// Находим позицию десятичной точки
		size_t dot_pos = s.find('.');
		// std::string::npos - спец. значение, используемое для недопустимого
		// или отсутствующего положения символа в строке. 
		if (dot_pos != std::string::npos) {
				// Находим позицию последнего не-нуля
				size_t first_non_zero = s.find_first_not_of('0');
				if (first_non_zero != std::string::npos) {
						return static_cast<int>(dot_pos - first_non_zero); 
				}
		}
	}
	return 0; 
}

RationalNumber::RationalNumber() : numerator(0), denominator(0) {};

RationalNumber::RationalNumber(long long _numerator, long long _denominator)
{
	if (_denominator == 0 && _numerator != 0)
	{
		throw std::invalid_argument("Denominator cannot be zero");
	}
	else if (_denominator == 0 && _numerator == 0)
	{
		throw std::invalid_argument("0/0 = inf! That's not rational number.");
	}
	else
	{
		numerator = _numerator;
		denominator = _denominator;
	}
}

long long RationalNumber::getNumerator() const
{
	return numerator;
}

long long RationalNumber::getDenominator() const
{
	return denominator;
}

void RationalNumber::setNumerator(long long _numerator)
{  
	numerator = _numerator;
}

void RationalNumber::setDenominator(long long _denominator)
{
	if (_denominator == 0)
	{
		throw std::invalid_argument("Denominator cannot be zero");
	}
	else
	{
		denominator = _denominator;
	}
}

RationalNumber RationalNumber::operator=(const RationalNumber &other)
{
	// Проверяем, чтобы избежать самоприсваивания.
	if (this == &other)
	{
		// *this разымениование указателя *this, чтобы возвращать
		// не ссылку на объект, а сам объект (ссылку на него)
		return *this;
	}
	numerator = other.numerator;
	denominator = other.denominator;
	return *this;
}

RationalNumber RationalNumber::operator-()
{
	numerator = -numerator; 
	return *this; 
}

std::ostream &operator<<(std::ostream &terminal, const RationalNumber &number)
{
	terminal << number.getNumerator() << "/" << number.getDenominator();
	return terminal;
}

bool operator==(RationalNumber &left, RationalNumber &right)
{
	return (left.getNumerator() == right.getNumerator()) && (left.getDenominator() == right.getDenominator());
}

bool operator!=(RationalNumber &left, RationalNumber &right)
{
	return !(left == right);
}
