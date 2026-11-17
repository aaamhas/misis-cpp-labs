#include "stacka.hpp"
#include <utility>
#include <stdexcept>
StackA::StackA(const StackA& src){
    if (!src.is_empty()){
        int64_t size = src.data_[0];
        int64_t capacity = src.data_[1];
        data_ = new int64_t[capacity+2];
        data_[0] = size;
        data_[1] = capacity;
        for (int64_t i = 2; i < size+2; ++i){
            data_[i] = src.data_[i];
        }
    }
}

StackA::~StackA(){
    delete[] data_;
}

StackA& StackA::operator=(const StackA& src){
    if (this != &src) {
        StackA temp(src);
        std::swap(data_, temp.data_);
    }
  return *this;
}

bool StackA::is_empty() const noexcept{
    return (data_ == nullptr || data_[0] == 0);
}


void StackA::pop() noexcept{
    if (!this->is_empty()){
        data_[0] -= 1;
    }
}

void StackA::push(const int64_t val){
    if (data_ != nullptr){
        if (data_[1] > data_[0]){
            data_[0] += 1;
            data_[data_[0] + 1] = val;
        } else{
            int64_t new_capacity = data_[1] * 2;
            int64_t* new_data = new int64_t[new_capacity + 2];
            for (int64_t i = 2; i < data_[0]+2; ++i){
                new_data[i] = data_[i];
            }
            new_data[0] = data_[0];
            new_data[1] = new_capacity;

            new_data[0] += 1;
            new_data[new_data[0] + 1] = val;
            delete[] data_;
            data_ = new_data;
        }
    }
    else {
        data_ = new int64_t[5+2];
        data_[0] = 1;
        data_[1] = 5;
        data_[2] = val;
    }
}

int64_t& StackA::top() {
    if (is_empty()) {
        throw std::logic_error("StackA::top: empty stack");
    }
    return data_[data_[0] + 1];
}

int64_t StackA::top() const {
    if (is_empty()) {
        throw std::logic_error("StackA::top: empty stack");
    }
    return data_[data_[0] + 1];
}

void StackA::clear() noexcept {
    if (data_ != nullptr) {
        data_[0] = 0;
    }
}