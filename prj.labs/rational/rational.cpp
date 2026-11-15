#include "rational.hpp"
#include <stdexcept>
#include <numeric>
#include <ostream>
#include <istream>

Rational::Rational(const std::int32_t num, const std::int32_t den)
  : num_(num), den_(den) {
  if (0 == den_) {
    throw std::invalid_argument("Zero denumenator in Rational ctor");
  }
  Normalize();
}

void Rational::Normalize() noexcept {
    int gcd = std::gcd(this->num_, this->den_);
    this->num_ = this->num_/gcd;
    this->den_ = this->den_/gcd;
    if (den_ < 0){
        den_ *= -1;
        num_ *= -1;
    }
}

bool Rational::operator==(const Rational& rhs) const noexcept {
    return (this->num_ == rhs.num() && this->den_ == rhs.den());}

bool Rational::operator!=(const Rational& rhs) const noexcept {
    return !(this->num_ == rhs.num() && this->den_ == rhs.den());}

bool Rational::operator<(const Rational& rhs) const noexcept { 
    return (static_cast<std::int64_t>(num_)*rhs.den() < static_cast<std::int64_t>(den_)*rhs.num());} 
bool Rational::operator<=(const Rational& rhs) const noexcept {
    return (*this<rhs || *this == rhs);}  

bool Rational::operator>(const Rational& rhs) const noexcept { 
    return (static_cast<std::int64_t>(num_)*rhs.den() > static_cast<std::int64_t>(den_)*rhs.num());} 
bool Rational::operator>=(const Rational& rhs) const noexcept {
    return (*this>rhs || *this == rhs);}  

Rational& Rational::operator+=(const Rational& rhs) noexcept {
    num_ = num_*rhs.den() + rhs.num()*den_;
    den_ = den_*rhs.den();
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) noexcept {
    num_ = num_*rhs.den() - rhs.num()*den_;
    den_ = den_*rhs.den();
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) noexcept {
    num_ = num_*rhs.num();
    den_ = den_*rhs.den();
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num() == 0){
        throw std::invalid_argument("Division by zero");
    }
    std::int32_t a = num_*rhs.den();
    std::int32_t b = den_*rhs.num();
    num_ = a;
    den_ = b;
    Normalize();
    return *this;
}

Rational& Rational::operator+=(const int32_t rhs) noexcept { return operator+=(Rational(rhs)); };
Rational& Rational::operator-=(const int32_t rhs) noexcept { return operator-=(Rational(rhs)); };
Rational& Rational::operator*=(const int32_t rhs) noexcept { return operator*=(Rational(rhs)); };
Rational& Rational::operator/=(const int32_t rhs) { return operator/=(Rational(rhs)); };


Rational operator+(const Rational& lhs, const Rational& rhs) noexcept { return Rational{ lhs } += rhs; }
Rational operator-(const Rational& lhs, const Rational& rhs) noexcept { return Rational{ lhs } -= rhs; }
Rational operator*(const Rational& lhs, const Rational& rhs) noexcept { return Rational{ lhs } *= rhs; }
Rational operator/(const Rational& lhs, const Rational& rhs) { return Rational{lhs} /= rhs; }

Rational operator+(const Rational& lhs, const int32_t rhs) noexcept { return Rational{ lhs } += rhs; }
Rational operator-(const Rational& lhs, const int32_t rhs) noexcept { return Rational{ lhs } -= rhs; };
Rational operator*(const Rational& lhs, const int32_t rhs) noexcept { return Rational{ lhs } *= rhs; };
Rational operator/(const Rational& lhs, const int32_t rhs) { return Rational{ lhs } /= rhs; }

Rational operator+(const int32_t lhs, const Rational& rhs) noexcept { return operator+(rhs, lhs); }
Rational operator-(const int32_t lhs, const Rational& rhs) noexcept { return Rational{lhs} -= rhs; }
Rational operator*(const int32_t lhs, const Rational& rhs) noexcept { return operator*(rhs, lhs); }
Rational operator/(const int32_t lhs, const Rational& rhs) { return Rational{lhs} /= rhs; }

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
    ostrm<<rhs.num()<<'/'<<rhs.den();
    return ostrm;}

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
    std::int32_t num{};
    std::int32_t den{};
    char slash{};

    try {
        if (!(istrm >> num >> slash) || slash != '/' ||
            !(istrm >> den) || den == 0) {
            istrm.setstate(std::ios::failbit);
            return istrm;
        }

        rhs = Rational{num, den};
    } catch (...) {
    }

    return istrm;
}
