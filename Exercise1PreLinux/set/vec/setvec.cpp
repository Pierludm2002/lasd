
namespace lasd {

/* ************************************************************************** */
    template <typename Data> SetVec<Data>::SetVec(){ 
        capacity = 4; 
        size = 0; 
        head = 0; 
        this->elements = new Data[capacity]; 
    }

    template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data>& sv) {
        this->size = sv.size;
        this->capacity = sv.capacity;
        this->head = 0; 
        this->isOrdered = sv.isOrdered;

        this->elements = new Data[this->capacity];

        for (ulong i = 0; i < this->size; ++i) {
            this->elements[i] = sv.elements[(sv.head + i) % sv.capacity];
        }
    }

    template <typename Data> SetVec<Data>::SetVec(SetVec&& sv){
        std::swap(elements, sv.elements); 
        std::swap(size, sv.size); 
        std::swap(capacity, sv.capacity); 
        std::swap(head, sv.head); 
    }

    template <typename Data> SetVec<Data>::SetVec(TraversableContainer<Data>& sv){
        sv.Traverse([this](const Data& cur){ 
            Insert(cur); 
        }); 
    }

    template <typename Data> SetVec<Data>::SetVec(MappableContainer<Data>& sv){
        sv.Map([this](Data& cur){
            Insert(std::move(cur));
        });
    }

    //destructor
    template <typename Data>
    SetVec<Data>::~SetVec() {
        delete[] this->elements;
        this->elements = nullptr; 
    }

/* ************************************************************************** */
    
    template <typename Data> bool SetVec<Data>::operator==(const SetVec& sv) const noexcept{ 
        if(size != sv.size){ 
            return false; 
        }

        for(ulong i=0; i< size; ++i){ 
            const Data& val = this->elements[(this->head + i) % this->capacity];
            if (!sv.Exists(val))
            return false;
        }
        return true;
    }

    template <typename Data> bool SetVec<Data>::operator!=(const SetVec& sv) const noexcept{ 
        return !(this == sv); 
    }

/* ************************************************************************** */
//SetVec è un vettore circolare e ordinato (creascente). Ho aggiunto un controllo per evitare eliminazioni errate.

    template <typename Data> Data& SetVec<Data>::Min() const{
        if(Empty()){ 
            throw std::length_error("The Set is empty"); 
        }else if(isOrdered()){
            return elements[head]; 
        }else{ 
            throw std::logic_error("Min() not yet implemented for unordered sets!");
        }

    }

    template <typename Data> Data SetVec<Data>::MinNRemove(){ 
         
        try{
           Data min = Min();
            head = (head + 1) % capacity; 
            --size;
            return min;
        }catch(const std::length_error &e){ 
           std::cerr << e.what() << std::endl; 
           throw; 
        }catch(const std::logic_error& e){
             std::cerr << "MinNRemove() not yet implemented for unordered sets!" << std::endl; 
             throw;
        }
    }

    template <typename Data> void SetVec<Data>::RemoveMin(){
        if(Empty()){
            throw std::length_error("The Set is empty"); 
        }if(isOrdered()){ 
           head = (head + 1) % capacity; 
           --size;  
        }else{
            throw std::logic_error("RemoveMin() not yet implemented for unordered sets!"); 
        }
        
    }

    template <typename Data> Data& SetVec<Data>::Max() const{
        if(Empty()){
            throw std::length_error("The Set is empty"); 
        }if(isOrdered()){
            long tail = (head + size - 1) % capacity;
            return elements[tail]; 
        }else{
            throw std::logic_error("Max() not yet implemented for unordered sets!"); 
        } 

    }

    template <typename Data> Data SetVec<Data>::MaxNRemove(){ 
        try {
           Data max = Max();
           --size; 
            return max;
        }catch ( const std::length_error& e){
            std::cerr << e.what() << std::endl; 
            throw; 
        }catch(const std::logic_error& e){
            std::cerr << "MaxNRemove() not yet implemented for unordered sets!" << std::endl; 
             throw;
        }
    }

    template <typename Data> void SetVec<Data>::RemoveMax(){ 
        if(Empty()){
            throw std::length_error("The Set is empty");
        }else if(isOrdered()){
            --size; 
        }else throw std::logic_error("RemoveMax() not yet implemented for unordered sets!"); 
    }

    template <typename Data> Data& SetVec<Data>::Predecessor(const Data& val) const{ 
       try{ 
            if(val == Min())
                throw std::length_error("You are looking for the predecessor of the min, news for you: it doesn't exist!"); 
       }catch(const std::logic_error& e){ 
            std::cerr<<"Predecessor() not yet implemented for unordered sets!\n" <<e.what()<< std::endl; 
            throw; 
       }
             
        long index = binSearch(val);
        //  pred; 
        // if(index == 0){ //questo caso dovrebbe essere impossibile (binSearch mi da l'indirizzo logico)
        //     pred = size - 1; 
        // }else 
        long pred = (head + index -1) % capacity;  
        return elements[pred];  
    }

    template <typename Data> Data SetVec<Data>::PredecessorNRemove(Data& val){ 
        
        try{ 
            if(val == Min()) throw std::length_error("You are looking for the predecessor of the min, news for you: it doesn't exist!"); 
        }catch(const std::logic_error& e){ 
            std::cerr<<"PredecessorNRemove not yet implemented for unordered sets\n" << e.what() << std::endl; 
            throw; 
        }
        long index = binSearch(val);
          
        long pred = ( head + index - 1) % capacity;  
        Data result = elements[pred]; 
        Remove(elements[pred]); 
        return result; 
    }

    template <typename Data> void SetVec<Data>::RemovePredecessor(Data& val){ 
        try{ 
            if(val == Min()) 
                throw std::length_error("You are looking for the predecessor of the min, news for you: it doesn't exist!"); 
        }catch(const std::logic_error& e){ 
            std::cerr << "RemovePredecessor not yet implemented for unordered sets!\n" << e.what() << std::endl; 
            throw; 
        }
        long index = binSearch(val); 
        long pred = (head + index - 1) % capacity; 
       
        Remove(elements[pred]); 
    }


    template <typename Data> Data& SetVec<Data>::Successor(const Data& val) const { 
        try{ 
            if(val == Max())
                throw std::length_error("You are looking for the predecessor of the max, news for you: it doesn't exist!"); 
        }catch(const std::logic_error& e){ 
            std::cerr << "Successor not yet implemented for unordered sets\n"<< e.what() << std::endl; 
            throw;
        }

        long index = binSearch(val); 
        long succ = (head + index + 1) % capacity;
        return elements[succ]; 
    }

    template <typename Data> Data SetVec<Data>::SuccessorNRemove(Data & val){ 
        try{ 
            if(val == Max())
                throw std::length_error("You are looking for the predecessor of the max, news for you: it doesn't exist!"); 
        }catch(const std::logic_error& e){ 
            std::cerr << "SuccessorNRemove not yet implemented for unordered sets\n"<< e.what() << std::endl; 
            throw;
        }

        long index = binSearch(val); 
        long succ = (head + index +1) % capacity; 
        Data result = elements[succ]; 
        Remove(elements[succ]);
        return result; 
    }

    template <typename Data> void SetVec<Data>::RemoveSuccessor(Data& val){ 
        try{ 
            if(val == Max())
                throw std::length_error("You are looking for the predecessor of the max, news for you: it doesn't exist!"); 
        }catch(const std::logic_error& e){ 
            std::cerr << "RemoveSuccessor not yet implemented for unordered sets\n"<< e.what() << std::endl; 
            throw;
        }

        long index = binSearch(val); 
        long succ = (head + index +1) % capacity;  
        Remove(elements[succ]);
    }

/* ************************************************************************** */

    template <typename Data> bool SetVec<Data>::Insert(const Data& val){ 
        if(!isOrdered()){ 
            return false; 
        }

        if(Exists(val)){ 
            std::cout << "No duplicates addimitted in sets"; 
            return false;  
        }

        if(size == capacity) ResizeSet(size + (size/2) +1); 
        
        long pos = 0; 
        while(pos < long(size)) {
            ulong index = (head + pos) % capacity;
            if (elements[index] > val) break;
            ++pos;
          }


        for(long j = long(size) -1; j>=pos; --j){
            ulong from = (head + j) % capacity;
            ulong to = (head + j + 1) % capacity;
            elements[to] = std::move(elements[from]);
        }

        ulong insertIndex = (head + pos) % capacity;
        elements[insertIndex] = val;
        ++size; 
        return true; 
    }


    template <typename Data> bool SetVec<Data>::Insert(Data && val)noexcept{
        if (!isOrdered()) return false;
        if (Exists(val)) return false;
        if (size == capacity) ResizeSet(size + (size/2) +1);

        ulong pos = 0;
        while (pos < size) {
            ulong index = (head + pos) % capacity;
            if (elements[index] > val) break;
            ++pos;
        }

        for (long i = size - 1; i >= (long)pos; --i) {
            ulong from = (head + i) % capacity;
            ulong to = (head + i + 1) % capacity;
            elements[to] = std::move(elements[from]);
        }

        ulong insertIndex = (head + pos) % capacity;
        elements[insertIndex] = std::move(val);
        ++size;

        return true; 
    }


    template <typename Data> bool SetVec<Data>::Remove(const Data& val){ 
        if(!isOrdered()){ 
            return false; 
        }

        long pos = binSearch(val); 
        if(pos < 0) return false; 

        for(ulong i = pos; i < size -1; ++i){ 
            ulong from = (head + i + 1)% capacity; 
            ulong to =(head +i) % capacity; 
            elements[to] = std::move(elements[from]); 
        }

        --size; 
        return true; 
    }
    
/* ************************************************************************** */

    template <typename Data>
    Data& SetVec<Data>::operator[](ulong index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds in SetVec");
        }

        ulong realIndex = (head + index) % capacity;
        return elements[realIndex];
    }

/* ************************************************************************** */

    template  <typename Data>
    bool SetVec<Data>::Exists(const Data& val) const noexcept{ 
        long pos = binSearch(val); 
        if(pos<0) return false; 
        return true; 
    }

    template <typename Data>
    void SetVec<Data>::Clear() {
        this->size = 0;
        this->head = 0;
    }

/* ************************************************************************** */

    template <typename Data>
    bool SetVec<Data>::isOrdered() const noexcept {
    if (size <= 1)
        return true;

    for (ulong i = 0; i < size - 1; ++i) {
        ulong currentIndex = (head + i) % capacity;
        ulong nextIndex = (head + i + 1) % capacity;
        //std::cout << elements[currentIndex] << " < " << elements[nextIndex] << std::endl; 

        if (elements[currentIndex] > elements[nextIndex])
        return false;
    }

    return true;
    }

    template <typename Data> long SetVec<Data>::binSearch(const Data& key)const{ 
        long i=0, j=size-1; 
        do{
            long q=(i+j)/2;
            ulong ind = (head + q)%capacity; 

            if(elements[ind] == key){ 
                return ind;
            }else if(elements[ind] < key){ 
                i = q +1; 
            }else{ 
                j = q -1; 
            }
        }while( i <= j ); 

        return -1; 
    }

    template <typename Data> void SetVec<Data>::ResizeSet(const ulong newSize){ 
        if(newSize == capacity) return; 
        Data* newElements = new Data[newSize]; 
        for(ulong i = 0; i < size; ++i){
            newElements[i] = std::move(elements[i]); 
        }

        if(elements != nullptr) delete[] this->elements;
         
        this->elements = newElements; 
        capacity = newSize; 
        head = 0; 
    }



// template <typename Data> long SetVec<Data>::findIndexSucc(const Data&) const{ 
       
// }


}
