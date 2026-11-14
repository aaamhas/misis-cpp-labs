#include "rational.hpp"
#include <stdexcept>
#include <numeric>

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