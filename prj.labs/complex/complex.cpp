#include "complex.hpp"
#include <stdexcept>
#include <ostream>
#include <istream>

Complex Complex::operator-() const noexcept { return Complex(-re, -im); }

bool Complex::operator==(const Complex& rhs) const noexcept {
    return this->re == rhs.re && this->im == rhs.im;}
bool Complex::operator!=(const Complex& rhs) const noexcept {
    return this->re != rhs.re || this->im != rhs.im;}

Complex& Complex::operator+=(const Complex& rhs) noexcept {
    this->re += rhs.re;
    this->im += rhs.im;
    return *this;}
Complex& Complex::operator+=(const double rhs) noexcept {
    this->re += rhs;
    return *this;}

Complex& Complex::operator-=(const Complex& rhs) noexcept {
    this->re -= rhs.re;
    this->im -= rhs.im;
    return *this;}
Complex& Complex::operator-=(const double rhs) noexcept {
    this->re -= rhs;
    return *this;}

Complex& Complex::operator*=(const Complex& rhs) noexcept {
    double a = this->re*rhs.re - this->im*rhs.im;
    double b = this->re*rhs.im + this->im*rhs.re;
    this->re = a;
    this->im = b;
    return *this;}
Complex& Complex::operator*=(const double rhs) noexcept {
    this->re *= rhs;
    this->im *= rhs;
    return *this;}

Complex& Complex::operator/=(const Complex& rhs) {
    if (rhs.re==0.0 && rhs.im == 0.0){
        throw std::invalid_argument("Division by zero");
    }
    double a = (this->re*rhs.re + this->im*rhs.im)/(rhs.re*rhs.re + rhs.im*rhs.im);
    double b = (this->im*rhs.re - this->re*rhs.im)/(rhs.re*rhs.re + rhs.im*rhs.im);
    this->re = a;
    this->im = b;
    return *this;}
Complex& Complex::operator/=(const double rhs) {
    if (rhs==0.0){
        throw std::invalid_argument("Division by zero");
    }
    this->re /= rhs;
    this->im /= rhs;
    return *this;}

std::ostream& Complex::WriteTo(std::ostream& ostrm) const noexcept { 
    ostrm<< leftBrace << this->re << separator << this->im << rightBrace;
    return ostrm; }
std::istream& Complex::ReadFrom(std::istream& istrm) noexcept {
    char opening{}, delimiter{}, closing{};
    double real{}, imaginary{};

    try {
        if ((istrm >> opening) && opening == leftBrace &&
            (istrm >> real >> delimiter) && delimiter == separator &&
            (istrm >> imaginary >> closing) && closing == rightBrace) {
            re = real;
            im = imaginary;
        } else {
            istrm.setstate(std::ios::failbit);
        }
    } catch (...) {
    }

    return istrm;
}

Complex operator+(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) += rhs; }
Complex operator+(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) += rhs; }
Complex operator+(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) += rhs; }

Complex operator-(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) -= rhs; }
Complex operator-(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) -= rhs; }
Complex operator-(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) -= rhs; }

Complex operator*(const Complex& lhs, const Complex& rhs) noexcept { return Complex(lhs) *= rhs; }
Complex operator*(const Complex& lhs, const double rhs) noexcept { return Complex(lhs) *= rhs; }
Complex operator*(const double lhs, const Complex& rhs) noexcept { return Complex(lhs) *= rhs; }

Complex operator/(const Complex& lhs, const Complex& rhs) { return Complex(lhs) /= rhs; }
Complex operator/(const Complex& lhs, const double rhs) { return Complex(lhs) /= rhs; }
Complex operator/(const double lhs, const Complex& rhs) { return Complex(lhs) /= rhs; }