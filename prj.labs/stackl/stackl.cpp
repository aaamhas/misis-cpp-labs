#include "stackl.hpp"
#include <memory>
#include <stdexcept>

StackL::StackL(const StackL& src){
    if (!src.is_empty()){
        head_ = new Node{src.head_->val};
        Node* p_src = src.head_;
        Node* p_dst = head_;
        while (p_src->next) {
            p_dst->next = new Node{p_src->next->val };
            p_src = p_src->next;
            p_dst = p_dst->next;
        }
    }
}