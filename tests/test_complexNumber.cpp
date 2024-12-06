#include <catch2/catch_test_macros.hpp> 
#include "../include/complexNumber.h"
#include <catch2/catch_approx.hpp>
#include <string>

// Написал unit-тесты на Catch2

// Проверка конструктора на неявное преобразование
TEST_CASE("Checking the class constructor for implicit conversion", "[constructor]"){
    // Преобразование из отрицательных и положительных int
    SECTION("Conversion from negative and positive int") {
        ComplexNumber<int> c1(-1);
        REQUIRE(c1.getReal() == Catch::Approx(-1.0));
        ComplexNumber<int> c2(-1011);
        REQUIRE(c2.getReal() == Catch::Approx(-1011.0)); 
        ComplexNumber<int> c3(50);
        REQUIRE(c3.getReal() == Catch::Approx(50.0));
        ComplexNumber<int> c4(9999999);
        REQUIRE(c4.getReal() == Catch::Approx(9999999.0));
    }
    
    // Преобразование из положительных и отрицательных float 
    SECTION("Conversion from negative and positive float") {
        ComplexNumber<float> c1(-1.0);
        REQUIRE(c1.getReal() == Catch::Approx(-1.0));
        ComplexNumber<float> c2(-1010.0);
        REQUIRE(c2.getReal() == Catch::Approx(-1010.0));
        ComplexNumber<float> c3(5.0);
        REQUIRE(c3.getReal() == Catch::Approx(5.0));
        ComplexNumber<float> c4(99999.0);
        REQUIRE(c4.getReal() == Catch::Approx(99999.0));
    }
};

TEST_CASE("Testing methods", "[methods]") {
    SECTION("abs() method") {
        ComplexNumber<int> c1(3, 4);
        REQUIRE(c1.abs() == Catch::Approx(5.0));

        ComplexNumber<float> c2(3.0, 4.0);
        REQUIRE(c2.abs() == Catch::Approx(5.0));
    }

    SECTION("arg() method") {
        ComplexNumber<int> c1(1, 1);
        REQUIRE(c1.arg() == Catch::Approx(0.785398).epsilon(0.01)); // pi/4

        ComplexNumber<float> c2(1.0, 1.0);
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
        ComplexNumber<double> c1(4.0, 4.0);
        c1.factorization(2);
        REQUIRE(c1.getReal() == Catch::Approx(0.00000000000000196).epsilon(0.01));
        REQUIRE(c1.getImaginary() == Catch::Approx(32.0).epsilon(0.01));

        ComplexNumber<double> c2(-10.0, 19.0);
        c2.factorization(2);
        REQUIRE(c2.getReal() == Catch::Approx(-261));
        REQUIRE(c2.getImaginary() == Catch::Approx(-380));
    }
}

TEST_CASE("Testing overloaded operators", "[operators]") {
    SECTION("Addition operator") {
        ComplexNumber<int> c1(1, 2);
        ComplexNumber<int> c2(3, 4);
        ComplexNumber<double> result = c1 + c2;
        REQUIRE(result.getReal() == Catch::Approx(4.0));
        REQUIRE(result.getImaginary() == Catch::Approx(6.0));

        ComplexNumber<float> c3(1.5, 2.5);
        ComplexNumber<float> c4(3.5, 4.5);
        ComplexNumber<double> result2 = c3 + c4;
        REQUIRE(result2.getReal() == Catch::Approx(5.0));
        REQUIRE(result2.getImaginary() == Catch::Approx(7.0));
    }

    SECTION("Subtraction operator") {
        ComplexNumber<int> c1(5, 6);
        ComplexNumber<int> c2(3, 4);
        ComplexNumber<double> result = c1 - c2;
        REQUIRE(result.getReal() == Catch::Approx(2.0));
        REQUIRE(result.getImaginary() == Catch::Approx(2.0));

        ComplexNumber<float> c3(5.5, 6.5);
        ComplexNumber<float> c4(3.5, 4.5);
        ComplexNumber<double> result2 = c3 - c4;
        REQUIRE(result2.getReal() == Catch::Approx(2.0));
        REQUIRE(result2.getImaginary() == Catch::Approx(2.0));
    }

    SECTION("Multiplication operator") {
        ComplexNumber<int> c1(1, 2);
        ComplexNumber<int> c2(3, 4);
        ComplexNumber<double> result = c1 * c2;
        REQUIRE(result.getReal() == Catch::Approx(-5.0));
        REQUIRE(result.getImaginary() == Catch::Approx(10.0));

        ComplexNumber<float> c3(1.5, 2.5);
        ComplexNumber<float> c4(3.5, 4.5);
        ComplexNumber<double> result2 = c3 * c4;
        REQUIRE(result2.getReal() == Catch::Approx(-6));
        REQUIRE(result2.getImaginary() == Catch::Approx(15.5));
    }

    SECTION("Division operator") {
        ComplexNumber<int> c1(1, 2);
        ComplexNumber<int> c2(3, 4);
        ComplexNumber<double> result = c1 / c2;
        REQUIRE(result.getReal() == Catch::Approx(0.44).epsilon(0.01));
        REQUIRE(result.getImaginary() == Catch::Approx(0.08).epsilon(0.01));

        ComplexNumber<float> c3(1.5, 2.5);
        ComplexNumber<float> c4(3.5, 4.5);
        ComplexNumber<double> result2 = c3 / c4;
        REQUIRE(result2.getReal() == Catch::Approx(0.507).margin(0.0007));
        REQUIRE(result2.getImaginary() == Catch::Approx(0.06).margin(0.002));
    }

    SECTION("Unary minus operator") {
        ComplexNumber<int> c1(1, -2);
        ComplexNumber<int> result = -c1;
        REQUIRE(result.getReal() == Catch::Approx(-1.0));
        REQUIRE(result.getImaginary() == Catch::Approx(2.0));

        ComplexNumber<float> c2(1.5, -2.5);
        ComplexNumber<float> result2 = -c2;
        REQUIRE(result2.getReal() == Catch::Approx(-1.5));
        REQUIRE(result2.getImaginary() == Catch::Approx(2.5));
    }
}