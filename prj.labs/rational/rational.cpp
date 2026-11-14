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

void Rational::Normalize(){
    int gcd = std::gcd(this->num_, this->den_);
    this->num_ = this->num_/gcd;
    this->den_ = this->den_/gcd;
}