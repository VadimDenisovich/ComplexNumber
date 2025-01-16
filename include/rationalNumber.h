#ifndef RATIONALNUMBER_H
#define RATIONALNUMBER_H

#include <iostream>
#include <limits>
#include <charconv>
#include <stdexcept>
#include <sstream>
#include <cassert>
#include <iomanip>
#include <boost/lexical_cast.hpp>

// Все шаблонные функции и конструкторы нужно объявлять в заголовочном файле

class RationalNumber
{
private:
	long long numerator;
	long long denominator;

public:
	RationalNumber();
	RationalNumber(long long _numerator, long long _denominator);

	template <typename T>
	RationalNumber(const T &value)
	{
		*this = toRationalNumber(value);
	}

	static long long _findGCD(long long a, long long b);
	static int _countDecimalPlaces(double number);
	double toDouble();
	template <typename V>
	static RationalNumber toRationalNumber(const V &value)
	{
		if constexpr (std::is_same_v<V, RationalNumber>)
		{
			return value;
		}
		else if constexpr (std::is_same_v<V, int>)
		{
			if (value == 0) 
			{
				return RationalNumber(0, 0);
			}
			return RationalNumber(value, 1);
		}
		else if constexpr (std::is_same_v<V, double>)
		{
			int factor = pow(10, _countDecimalPlaces(value));
			std::cout << "tutochki" << factor << std::endl;
			long long _denominator = factor;
			long long _numerator = value * factor;
			return RationalNumber(_numerator, _denominator);
		}
		else
		{
			throw std::invalid_argument("Unsupported type!");
		}
	}

	// temp → delete
	static void test(double number)
	{
		std::cout << _countDecimalPlaces(number) << std::endl;
	}

	long long getNumerator() const;
	long long getDenominator() const;
	void setNumerator(long long _numerator);
	void setDenominator(long long _denominator);

	RationalNumber operator=(const RationalNumber &other);

	template <typename T>
	void operator+=(const T &number)
	{
		RationalNumber other = toRationalNumber(number);
		// Числитель представляет из себя сумму двух числителей, умноженных на чужие знаменатели
		numerator = numerator * other.denominator + denominator * other.numerator;
		denominator = denominator * other.denominator;
		long long gcd = _findGCD(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;
	}
	template <typename T>
	void operator-=(const T &number)
	{
		RationalNumber other = toRationalNumber(number);
		numerator = numerator * other.denominator - denominator * other.numerator;
		denominator = denominator * other.denominator;
		long long gcd = _findGCD(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;
	}
	template <typename T>
	void operator*=(const T &number)
	{
		RationalNumber other = toRationalNumber(number);
		numerator *= other.numerator;
		denominator *= other.denominator;
		long long gcd = _findGCD(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;
	}
	template <typename T>
	void operator/=(const T &number)
	{
		RationalNumber other = toRationalNumber(number);
		numerator *= other.denominator;
		denominator *= other.numerator;
		long long gcd = _findGCD(numerator, denominator);
		numerator /= gcd;
		denominator /= gcd;
	}
	RationalNumber operator-();

	friend std::ostream &operator<<(std::ostream &terminal, const RationalNumber &number);

	template<typename V, typename T>
	friend RationalNumber operator+(T l, V r);

	template<typename V, typename T>
	friend RationalNumber operator-(T l, V r);

	template<typename V, typename T>
	friend RationalNumber operator*(T l, V r);

	template<typename V, typename T>
	friend RationalNumber operator*(T l, V r);

	friend bool operator==(RationalNumber &left, RationalNumber &right);

	friend bool operator!=(RationalNumber &left, RationalNumber &right);
};

template<typename V, typename T>
RationalNumber operator+(T l, V r)
{
	RationalNumber left = RationalNumber::toRationalNumber(l);
	RationalNumber right = RationalNumber::toRationalNumber(r);
	long long numerator = left.getNumerator() * right.getDenominator() + left.getDenominator() * right.getNumerator();
	long long denominator = left.getDenominator() * right.getDenominator();
	long long gcd = RationalNumber::_findGCD(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
	return RationalNumber(numerator, denominator);
}

template<typename V, typename T>
RationalNumber operator-(T l, V r)
{
	RationalNumber left = RationalNumber::toRationalNumber(l);
	RationalNumber right = RationalNumber::toRationalNumber(r);
	long long numerator = left.getNumerator() * right.getDenominator() - left.getDenominator() * right.getNumerator();
	long long denominator = left.getDenominator() * right.getDenominator();
	long long gcd = RationalNumber::_findGCD(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
	return RationalNumber(numerator, denominator);
}


template<typename V, typename T>
RationalNumber operator*(T l, V r)
{
	RationalNumber left = RationalNumber::toRationalNumber(l);
	RationalNumber right = RationalNumber::toRationalNumber(r);
	long long numerator = left.getNumerator() * right.getNumerator();
	long long denominator = left.getDenominator() * right.getDenominator();
	long long gcd = RationalNumber::_findGCD(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
	return RationalNumber(numerator, denominator);
}

template<typename V, typename T>
RationalNumber operator/(T l, V r)
{
	RationalNumber left = RationalNumber::toRationalNumber(l);
	RationalNumber right = RationalNumber::toRationalNumber(r);
	long long numerator = left.getNumerator() * right.getDenominator();
	long long denominator = left.getDenominator() * right.getNumerator();
	long long gcd = RationalNumber::_findGCD(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
	return RationalNumber(numerator, denominator);
}

#endif // RATIONALNUMBER_H