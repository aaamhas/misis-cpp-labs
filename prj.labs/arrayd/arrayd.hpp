#ifndef ARRAYD_HPP
#define ARRAYD_HPP

#include <cstddef>

class ArrayD {
public:
    ArrayD() = default;

    ArrayD(const ArrayD&);

    ArrayD(const std::ptrdiff_t size);
  
    ~ArrayD();
  
    ArrayD& operator=(const ArrayD&);

    [[nodiscard]] std::ptrdiff_t size() const noexcept { return size_; }

    void resize(const std::ptrdiff_t size);
    

    [[nodiscard]] float& operator[](const std::ptrdiff_t idx);
    [[nodiscard]] float operator[](const std::ptrdiff_t idx) const;

private:
    std::ptrdiff_t capacity_ = 0;  //!< размер буффера
    std::ptrdiff_t size_ = 0;      //!< число элементов в массиве
    float* data_ = nullptr;             //!< буффер
};


#endif
