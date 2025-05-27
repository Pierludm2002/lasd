#include "vector.hpp"
#include <iostream>

namespace lasd {

    /* ************************************************************************** */
    template <typename Data> //costruttore specifico
    Vector<Data>::Vector(unsigned long newSize){ 
        this->size = newSize; 
        elements = new Data[this->size];
    }

    template <typename Data>
    Vector<Data>::Vector(TraversableContainer<Data> & container){ 
        this->size = container.Size(); 
        elements = new Data[this->size]; 

        ulong i = 0; 
        container.Traverse([this, &i](const Data& data){ 
            elements[i++] = data; 
        });
    }

    template <typename Data>
    Vector<Data>::Vector(MappableContainer<Data> && container){ 
        this->size = container.Size();
        elements = new Data[this->size]; 

        ulong i = 0; 
        container.Map([this, &i](Data& data){
            elements[i++] = data; 
        }); 

    }

    template <typename Data> // costrutore copia
    Vector<Data>::Vector(const Vector<Data>& vec) {
        this->size = vec.size;
        elements = new Data[this->size];
        
        for(unsigned long i = 0; i < this->size; ++i) {
            elements[i] = vec.elements[i];
        }
    }

    template<typename Data>//move construtor
    Vector<Data>::Vector(Vector && vec) noexcept { 
        std::swap(this->size, vec.size); 
        std::swap(elements, vec.elements);
    }

    template <typename Data> //distruttore
    Vector<Data>::~Vector(){
        delete[] elements; 
    } 

    /* ************************************************************************** */

    //Copy and move assignment

    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec){ 
        Vector<Data>* tmpvec = new Vector<Data>(vec); 
        std::swap(*tmpvec,*this); 
        delete tmpvec; 
        return *this; 
    }

    
    template <typename Data>//move
    Vector<Data> & Vector<Data>::operator=(Vector<Data> && vec) noexcept{
        std::swap(size,vec.size); 
        std::swap(elements, vec.elements);
        return *this; 
    }

    /* ************************************************************************** */

    //comparison op
    template <typename Data>
    bool Vector<Data>::operator==(const Vector<Data> &vec) const noexcept {
    if (this->size != vec.size) {
        return false;
    }

    for (unsigned long i = 0; i < this->size; i++) {
        if (elements[i] != vec[i]) {
        return false;
        }
    }
    return true;
    }

    template <typename Data>
    bool Vector<Data>::operator!=(const Vector<Data> &vec) const noexcept {
    return !(*this == vec);
    }
    

    /* ************************************************************************** */

    //Specific member functions
    template <typename Data>
    Data& Vector<Data>::operator[](unsigned long index){ 
        if(index >= this->size || index < 0) throw std::out_of_range("Index out of range"); 
        return elements[index]; 
    }


    template <typename Data>
    const Data& Vector<Data>::operator[](unsigned long index) const{ 
        if(index >= this->size ) throw std::out_of_range("Index out of range"); 
        return elements[index]; 
    }

    template <typename Data>
    Data& Vector<Data>::Front(){ 
        if(this->size > 0){
            return elements[0]; 
        }else{ 
            throw std::length_error("The vector is empty."); 
        }
    }

    template <typename Data>
    const Data& Vector<Data>::Front() const{ 
        if(this->size > 0){
            return elements[0]; 
        }else{ 
            throw std::invalid_argument("The vector is empty."); 
        }
    }

    template <typename Data>
    Data& Vector<Data>::Back(){ 
        if(this->size > 0){ 
            return elements[this->size - 1]; 
        }else{ 
            throw std::length_error("The vector is empty."); 
        }
    }

    template <typename Data>
    const Data& Vector<Data>::Back() const { 
        if(this->size > 0){ 
            return elements[this->size - 1]; 
        }else{ 
            throw std::invalid_argument("The vector is empty."); 
        }
    }

    template <typename Data>
    void Vector<Data>::Print() const{ 
        if(this->size > 0) {
            for(ulong i=0; i<this->size; ++i){ 
                std::cout << elements[i] << " " ; 
            }
            std::cout << std::endl; 
        }else{ 
            throw std::invalid_argument("The vector is empty"); 
        }
    }

    template <typename Data>
    void Vector<Data>::Resize(unsigned long newSize) {
        if (newSize == this->size) return; 
        if(newSize == 0){ 
            Clear(); 
            return; 
        }

        Data* newElements = new Data[newSize];

        ulong minSize = std::min(newSize, this->size);
        for (ulong i = 0; i < minSize; ++i) {
            newElements[i] = std::move(elements[i]);
        }

        delete[] elements;
        elements = newElements;
        this->size = newSize;
    }


    template <typename Data>
    void Vector<Data>::Clear() {
        delete[] elements;
        elements = nullptr;
        this->size = 0;
    }


    template <typename Data>
    inline void Vector<Data>::Map(MapFun fun) {
        for (ulong i = 0; i < size; ++i) {
            fun(elements[i]);
        }
    }

    template <typename Data>
    inline void Vector<Data>::PreOrderMap(MapFun fun) {
        Map(fun); 
    }

    template <typename Data>
    inline void Vector<Data>::PostOrderMap(MapFun fun) {
        for (long i = static_cast<long>(size) - 1; i >= 0; --i) {
            fun(elements[i]);
        }
    }


    /* ************************************************************************** */

    //Sortable Vector
    template <typename Data>
    SortableVector<Data>::SortableVector(ulong size)
    : Vector<Data>(size) {}

    template <typename Data>
    SortableVector<Data>::SortableVector(TraversableContainer<Data>& container)
    : Vector<Data>(container) {}

    template <typename Data>
    SortableVector<Data>::SortableVector(MappableContainer<Data>&& container)
    : Vector<Data>(container) {}

    template <typename Data>
    SortableVector<Data>::SortableVector(const SortableVector<Data>& vec)
    : Vector<Data>(vec) {}
    
    template <typename Data>
    SortableVector<Data>::SortableVector(SortableVector<Data>&& vec) noexcept
    : Vector<Data>(std::move(vec)) {}

        
    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data> & vec){ 
        Vector<Data>::operator=(vec); 
        return *this; 
    }

    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data> && vec) noexcept{ 
        Vector<Data>::operator=(std::move(vec)); 
        return *this;
    }

    template <typename Data>
void SortableVector<Data>::Sort() {
    InsertionSort();
}

template <typename Data>
void SortableVector<Data>::InsertionSort() {
    for (ulong i = 1; i < this->size; ++i) {
        Data key = (*this)[i];
        long j = i - 1;

        while (j >= 0 && (*this)[j] > key) {
            (*this)[j + 1] = (*this)[j];
            --j;
        }

        (*this)[j + 1] = key;
    }
}

    

   
}
