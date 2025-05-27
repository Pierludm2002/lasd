#include "linear.hpp"

namespace lasd {
    /* ************************************************************************** */

    // Implementazione dei metodi inline dichiarati in linear.hpp

    template <typename Data>
    inline bool LinearContainer<Data>::operator==(const LinearContainer& other) const noexcept {
        if(this->size != other.size) {
            return false;
        }

        for(unsigned long i = 0; i < this->size; ++i) {
            if((*this)[i] != other[i]) {
                return false;
            }
        }
        
        return true;
    }

    template <typename Data>
    inline bool LinearContainer<Data>::operator!=(const LinearContainer& other) const noexcept {
        return !(*this == other);
    }

    /* ************************************************************************** */

    template <typename Data>
    inline void LinearContainer<Data>::Traverse(TraverseFun fun) const{ 

        for(unsigned long i = 0; i < this->size; ++i) {
            fun((*this)[i]);
        }

    }

    template <typename Data>
    inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const { 
        Traverse(fun);
    }

    template <typename Data>
    inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const { 
        for(unsigned long i = this->size; i > 0; --i) {
            fun((*this)[i-1]);
        }
    }

    /* ************************************************************************** */

    template <typename Data>
    inline void MutableLinearContainer<Data>::Map(MapFun fun) { 
        for(ulong i = 0; i < this->size; i++){ 
            fun((*this)[i]); 
        }
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PreOrderMap(MapFun fun){
        Map(fun); 
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PostOrderMap(MapFun fun){ 
        for(long i = this->size - 1; i >= 0; --i){ 
            fun((*this)[i]); 
        }
    }
}