#include <catch2/catch_test_macros.hpp> 
#include "../include/complexNumber.h"
#include <catch2/catch_approx.hpp>
#include <string>

// Написал unit-тесты на Catch2

// Проверка конструктора на неявное преобразование
TEST_CASE("Checking the class constructor for implicit conversion", "[constructor]"){
    // Преобразование из отрицательных и положительных int
    SECTION("Conversion from negative and positive int") {
        ComplexNumber c1(Real(-1));
        REQUIRE(c1.getReal().toDouble() == Catch::Approx(-1.0));
        ComplexNumber c2(Real(-1011));
        REQUIRE(c2.getReal().toDouble() == Catch::Approx(-1011.0)); 
        ComplexNumber c3(Real(50));
        REQUIRE(c3.getReal().toDouble() == Catch::Approx(50.0));
        ComplexNumber c4(Real(9999999));
        REQUIRE(c4.getReal().toDouble() == Catch::Approx(9999999.0));
    }
    
    // Преобразование из положительных и отрицательных float 
    SECTION("Conversion from negative and positive float") {
        ComplexNumber c1(Real(-1.0));
        REQUIRE(c1.getReal().toDouble() == Catch::Approx(-1.0));
        ComplexNumber c2(Real(-1010.0));
        REQUIRE(c2.getReal().toDouble() == Catch::Approx(-1010.0));
        ComplexNumber c3(Real(5.0));
        REQUIRE(c3.getReal().toDouble() == Catch::Approx(5.0));
        ComplexNumber c4(Real(99999.0));
        REQUIRE(c4.getReal().toDouble() == Catch::Approx(99999.0));
    }
};

// Проверяем методы abs(), arg(), factorization()
TEST_CASE("Testing methods abs(), arg(), factorization()", "[methods]") {
    SECTION("abs() method") {
        ComplexNumber c1(Real(3), Imag(4));
        REQUIRE(c1.abs() == Catch::Approx(5.0));

        ComplexNumber c2(Real(3.0), Imag(4.0));
        REQUIRE(c2.abs() == Catch::Approx(5.0));
    }

    SECTION("arg() method") {
        ComplexNumber c1(Real(1), Imag(1));
        REQUIRE(c1.arg() == Catch::Approx(0.785398).epsilon(0.01)); // pi/4

        ComplexNumber c2(Real(1.0), Imag(1.0));
        REQUIRE(c2.arg() == Catch::Approx(0.785398).epsilon(0.01)); 
    }

    // epsilon(0.1) - задает относительную погрешность в 0.1% от истинного значения
    // Относительная погрешность измеряет разницу между измеренным (или вычисленным) 
    // значением и истинным значением в виде доли или процента от истинного значения. 
    // Она выражается как безразмерное число или в процентах.
    // EX: Если истинное значение равно 100, а измеренное значение равно 98, 
    // то относительная погрешность равна: \frac{|100 - 98|}{100} = \frac{2}{100} = 0.02 \text{ или } 2%
    //
    // margin(0.1) - задает абсолютную погрешность в 0.1 от истинного значения
    // Абсолютная погрешность измеряет разницу между измеренным (или вычисленным) 
    // значением и истинным значением. Она выражается в тех же единицах, 
    // что и сами значения.
    // EX: Если истинное значение равно 100, а измеренное значение равно 98, 
    // то абсолютная погрешность равна: |98 - 100| = 2

    SECTION("factorization() method") {
        ComplexNumber c1(Real(4.0), Imag(4.0));
        c1.factorization(2);
        REQUIRE(c1.getReal().toDouble() == Catch::Approx(0.0));
        REQUIRE(c1.getImaginary().toDouble() == Catch::Approx(32.0).epsilon(0.01));

        ComplexNumber c2(Real(-10.0), Imag(19.0));
        c2.factorization(2);
        REQUIRE(c2.getReal().toDouble() == Catch::Approx(-261));
        REQUIRE(c2.getImaginary().toDouble() == Catch::Approx(-380));
    }
}

// Проверяем перегруженные операторы +, -, *, / и унарного минуса
TEST_CASE("Testing overloaded operators +, -, *, / and unary minus", "[operators]") {
    SECTION("Addition operator") {
        ComplexNumber c1(Real(1), Imag(2));
        ComplexNumber c2(Real(3), Imag(4));
        ComplexNumber result = c1 + c2;
        REQUIRE(result.getReal().toDouble() == Catch::Approx(4.0));
        REQUIRE(result.getImaginary().toDouble() == Catch::Approx(6.0));

        ComplexNumber c3(Real(1.5), Imag(2.5));
        ComplexNumber c4(Real(3.5), Imag(4.5));
        ComplexNumber result2 = c3 + c4;
        REQUIRE(result2.getReal().toDouble() == Catch::Approx(5.0));
        REQUIRE(result2.getImaginary().toDouble() == Catch::Approx(7.0));
    }

    SECTION("Subtraction operator") {
        ComplexNumber c1(Real(5), Imag(6));
        ComplexNumber c2(Real(3), Imag(4));
        ComplexNumber result = c1 - c2;
        REQUIRE(result.getReal().toDouble() == Catch::Approx(2.0));
        REQUIRE(result.getImaginary().toDouble() == Catch::Approx(2.0));

        ComplexNumber c3(Real(5.5), Imag(6.5));
        ComplexNumber c4(Real(3.5), Imag(4.5));
        ComplexNumber result2 = c3 - c4;
        REQUIRE(result2.getReal().toDouble() == Catch::Approx(2.0));
        REQUIRE(result2.getImaginary().toDouble() == Catch::Approx(2.0));
    }

    SECTION("Multiplication operator") {
        ComplexNumber c1(Real(1), Imag(2));
        ComplexNumber c2(Real(3), Imag(4));
        ComplexNumber result = c1 * c2;
        REQUIRE(result.getReal().toDouble() == Catch::Approx(-5.0));
        REQUIRE(result.getImaginary().toDouble() == Catch::Approx(10.0));

        ComplexNumber c3(Real(1.5), Imag(2.5));
        ComplexNumber c4(Real(3.5), Imag(4.5));
        ComplexNumber result2 = c3 * c4;
        REQUIRE(result2.getReal().toDouble() == Catch::Approx(-6));
        REQUIRE(result2.getImaginary().toDouble() == Catch::Approx(15.5));
    }

    SECTION("Division operator") {
        ComplexNumber c1(Real(1), Imag(2));
        ComplexNumber c2(Real(3), Imag(4));
        ComplexNumber result = c1 / c2;
        REQUIRE(result.getReal().toDouble() == Catch::Approx(0.44).epsilon(0.01));
        REQUIRE(result.getImaginary().toDouble() == Catch::Approx(0.08).epsilon(0.01));

        ComplexNumber c3(Real(1.5), Imag(2.5));
        ComplexNumber c4(Real(3.5), Imag(4.5));
        ComplexNumber result2 = c3 / c4;
        REQUIRE(result2.getReal().toDouble() == Catch::Approx(0.507).margin(0.0007));
        REQUIRE(result2.getImaginary().toDouble() == Catch::Approx(0.06).margin(0.002));
    }

    SECTION("Unary minus operator") {
        ComplexNumber c1(Real(1), Imag(-2));
        ComplexNumber result = -c1;
        REQUIRE(result.getReal().toDouble() == Catch::Approx(-1.0));
        REQUIRE(result.getImaginary().toDouble() == Catch::Approx(2.0));

        ComplexNumber c2(Real(1.5), Imag(-2.5));
        ComplexNumber result2 = -c2;
        REQUIRE(result2.getReal().toDouble() == Catch::Approx(-1.5));
        REQUIRE(result2.getImaginary().toDouble() == Catch::Approx(2.5));
    }
}

// Тестируем операторы +=, -=, *=, /=
TEST_CASE("Testing operators +=, -=, *=, /=", "[operators]") {
    SECTION("Operator +=") {
        ComplexNumber c1(Real(1.0), Imag(2.0));
        ComplexNumber c2(Real(3.0), Imag(4.0));
        c1 += c2;
        REQUIRE(c1.getReal().toDouble() == Catch::Approx(4.0));
        REQUIRE(c1.getImaginary().toDouble() == Catch::Approx(6.0));
    }

    SECTION("Operator -=") {
        ComplexNumber c1(Real(5.0), Imag(6.0));
        ComplexNumber c2(Real(1.0), Imag(2.0));
        c1 -= c2;
        REQUIRE(c1.getReal().toDouble() == Catch::Approx(4.0));
        REQUIRE(c1.getImaginary().toDouble() == Catch::Approx(4.0));
    }

    SECTION("Operator *=") {
        ComplexNumber c1(Real(1.0), Imag(2.0));
        ComplexNumber c2(Real(3.0), Imag(4.0));
        c1 *= c2;
        REQUIRE(c1.getReal().toDouble() == Catch::Approx(-5.0));
        REQUIRE(c1.getImaginary().toDouble() == Catch::Approx(10.0));
    }

    SECTION("Operator /=") {
        ComplexNumber c1(Real(1.0), Imag(2.0));
        ComplexNumber c2(Real(3.0), Imag(4.0));
        c1 /= c2;
        REQUIRE(c1.getReal().toDouble() == Catch::Approx(0.44).epsilon(0.01));
        REQUIRE(c1.getImaginary().toDouble() == Catch::Approx(0.08).epsilon(0.01));
    }
}

// Тестируем операторы == и !=
TEST_CASE("Testing comparison operators == and !=", "[operators]") {
    SECTION("Operator ==") {
        ComplexNumber c1(Real(1.0), Imag(2.0));
        ComplexNumber c2(Real(1.0), Imag(2.0));
        REQUIRE(c1 == c2);

				ComplexNumber c3(100000.3423, 1234435.435);
        ComplexNumber c4(Real(100000.3423), Imag(1234435.435));
        REQUIRE(c3 == c4);
    }

    SECTION("Operator !=") {
        ComplexNumber c1(Real(1.0), Imag(2.0));
        ComplexNumber c2(Real(2.0), Imag(3.0));
        REQUIRE(c1 != c2);
    }
}

// Проверяем, как работает оператор присваивания
TEST_CASE("Testing assignment operator", "[assignment]") {
    ComplexNumber c1(Real(1.0), Imag(2.0));
    ComplexNumber c2(Real(0), Imag(1));
    c2 = c1;
    REQUIRE(c2.getReal().toDouble() == Catch::Approx(1.0));
    REQUIRE(c2.getImaginary().toDouble() == Catch::Approx(2.0));
}

TEST_CASE("Testing very big number", "[operators]") {
		// Берём очень большое значение double
    double max_double = 9223372036854775400.3485238;
    double big_number1 = max_double / 2;
    double big_number2 = max_double / 3;

    // Создаем комплексные числа с большими значениями
    ComplexNumber c1(big_number1, big_number2);
    ComplexNumber c2(big_number2, big_number1);

    // Проверяем, что числа не изменились после создания
    REQUIRE(c1.getReal().toDouble() == Catch::Approx(big_number1));
    REQUIRE(c1.getImaginary().toDouble() == Catch::Approx(big_number2));
    REQUIRE(c2.getReal().toDouble() == Catch::Approx(big_number2));
    REQUIRE(c2.getImaginary().toDouble() == Catch::Approx(big_number1));

    // Выполняем цепочку вычислений для проверки сохранится ли значение
    ComplexNumber c3 = c1 + c2;
    ComplexNumber c4 = c3 - c1;
    ComplexNumber c5 = c4 * c2;
    ComplexNumber c6 = c5 / c2;

    // Проверяем, что числа не изменились после вычислений
    REQUIRE(c6.getReal().toDouble() == Catch::Approx(1.08333333333394344));
    REQUIRE(c6.getImaginary().toDouble() == Catch::Approx(-0.0));	
}

TEST_CASE("Dividing big number by zero", "[big_numbers_zero_div]") {
    // Создаем комплексное число с очень большими значениями
    ComplexNumber c1(Real(9223372036854775400.3482338), Imag(1));
    // Создаем комплексное число, равное нулю
    ComplexNumber c2(Real(0.0), Imag(0.0));

    // Проверяем, что при делении на ноль выбрасывается исключение
    REQUIRE_THROWS_AS(c1 / c2, std::invalid_argument);
}