
namespace lasd {

/* ************************************************************************** */

    template <typename Data>
    SetLst<Data>::SetLst() : Set<Data>(), List<Data>(){}

    template <typename Data>
    SetLst<Data>::SetLst(TraversableContainer<Data>& container) {
    container.Traverse([this](const Data& val) {
        this->Insert(val);
    });
    }

    template <typename Data>
    SetLst<Data>::SetLst(MappableContainer<Data>& container) {
    container.Map([this](Data& val) {
        this->Insert(val);
    });
    }

    template <typename Data>
    SetLst<Data>::SetLst(const SetLst<Data>& set) {
        this->head = nullptr;
        this->size = 0;

        typename List<Data>::Node* current = set.head;
        typename List<Data>::Node** tail = &this->head;

        while (current != nullptr) {
            *tail = new typename List<Data>::Node(current->val);  
            tail = &((*tail)->next);
            ++(this->size);
            current = current->next;
        }
    }

    template <typename Data>
    SetLst<Data>::SetLst(SetLst<Data>&& other) noexcept {
        std::swap(this->head, other.head);
        std::swap(this->size, other.size);
    }

    template <typename Data>
    SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& set){ 
        if( this != set){
            Clear(); 
            typename List<Data>::Node* current = set.head; 
            typename List<Data>::Node** tail = &this->head;

            while(current != nullptr){ 
                *tail = new typename List<Data>::Node(current->val); // deep copy
                tail = &((*tail)->next);
                ++(this->size);
                current = current->next;
            }
        }

        return *this; 
    }

    template <typename Data>
    SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& set) {
        if (this != &set) {
            this->Clear(); // libera risorse attuali
            std::swap(this->head, set.head);
            std::swap(this->size, set.size);
        }
        return *this;
    }

    template <typename Data>
    bool SetLst<Data>::operator==(const SetLst<Data>& set) const noexcept {
        if (this->size != set.size) return false;

        typename List<Data>::Node* thisCurr = this->head;
        typename List<Data>::Node* otherCurr = set.head;

        while (thisCurr != nullptr && otherCurr != nullptr) {
            if (thisCurr->val != otherCurr->val) {
                return false;
            }
            thisCurr = thisCurr->next;
            otherCurr = otherCurr->next;
        }

        return true;
}

    template <typename Data>
    bool SetLst<Data>::operator!=(const SetLst<Data>& set) const noexcept {
        return !(*this == set);
    }

    template <typename Data>
    SetLst<Data>::~SetLst() {
    typename List<Data>::Node* curr = this->head;

    while (curr != nullptr) {
        typename List<Data>::Node* temp = curr;
        curr = curr->next;
        delete temp;
    }

    this->head = nullptr;
    this->size = 0;
    }

/* ************************************************************************** */

    template <typename Data>
    void SetLst<Data>::Clear() {
        typename List<Data>::Node* curr = this->head;
        while (curr != nullptr) {
            typename List<Data>::Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        this->head = nullptr;
        this->size = 0;
    }

/* ************************************************************************** */
    template <typename Data>
    bool SetLst<Data>::Insert(const Data& val) {
        if (this->Exists(val)) return false;

        typename List<Data>::Node* newNode = new typename List<Data>::Node(val);

        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            typename List<Data>::Node* prev = FindPrev(val);
        
            if (prev == nullptr) {
                newNode->next = this->head;
                this->head = newNode;
            } else {
                newNode->next = prev->next;     
                prev->next = newNode;          
            }
        }
        ++(this->size); 
        return true; 
    }

    template <typename Data>
    bool SetLst<Data>::Insert(Data&& val) {
        if (this->Exists(val)) return false;

        typename List<Data>::Node* newNode = new typename List<Data>::Node(std::move(val));

        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            typename List<Data>::Node* prev = FindPrev(newNode->val);

            if (prev == nullptr) {
                newNode->next = this->head;
                this->head = newNode;
            } else {
                newNode->next = prev->next;
                prev->next = newNode;
            }
        }

        ++(this->size);
        return true;
    }


    template <typename Data>
    bool SetLst<Data>::Remove(const Data& val) {
        if (!Exists(val)) return false;

        typename List<Data>::Node* prev = FindPrev(val);
        typename List<Data>::Node* target = nullptr;

        if (prev == nullptr) {
            target = this->head;
            this->head = this->head->next;
        } else {
            target = prev->next;
            prev->next = target->next;
        }

        delete target;
        --(this->size);
        return true;
    }

/* ************************************************************************** */

    template <typename Data>
    Data& SetLst<Data>::Min() const { 
        if(this->head ==nullptr){
            throw std::length_error("The Set is empty");
        }else{
            return this->head->val; 
        }
    }

    template <typename Data>
    Data SetLst<Data>::MinNRemove() {
        if(this->head == nullptr){ 
            throw std::length_error("Set is empty "); 
        }
        Data min = this->head->val;
        typename List<Data>::Node* target = this->head;
        this->head = this->head->next;
        delete target;
        --(this->size);
        return min;
    
    }

    template <typename Data>
    void SetLst<Data>::RemoveMin() {
        if (this->head == nullptr) {
            throw std::length_error("The Set is empty");
        }

        typename List<Data>::Node* target = this->head;
        this->head = this->head->next;
        delete target;
        --(this->size);
    }

//potrei aggiungere tail per avere le operazioni a tempo O(1), ma comunque con il controllo 
    // per verificare che la lista sia ordinata avrei tempo O(n).
    template <typename Data>
    Data& SetLst<Data>::Max() const{ 
        if (this->head == nullptr) {
            throw std::length_error("The Set is empty");
        } else {
            typename List<Data>::Node* current = this->head;
            Data* max = &(current->val);
            while (current != nullptr) {
                if (current->val > *max){   
                    max = &(current->val);
                }
                current = current->next;
            }
            return *max;
        }
    }

    template <typename Data>
    Data SetLst<Data>::MaxNRemove(){ 
        typename List<Data>::Node* maxNode = nullptr;
        typename List<Data>::Node* maxPrev = nullptr;

        std::tie(maxNode,maxPrev) = FindMaxWithPrev(); 
        
        Data max = maxNode->val;

        if (maxNode == this->head) {
            this->head = this->head->next;
        } else {
            maxPrev->next = maxNode->next;
        }
    
        delete maxNode;
        --(this->size);
    
        return max;
        
    }

    template <typename Data>
    void SetLst<Data>::RemoveMax(){ 
        typename List<Data>::Node* maxNode = nullptr;
        typename List<Data>::Node* maxPrev = nullptr;
        try{
            std::tie(maxNode, maxPrev) = FindMaxWithPrev();
        }catch (const std::length_error& e) {
            throw;
        }
        if (maxNode != nullptr) {
            if (maxNode == this->head) { //solo quando ha un elemento 
                this->head = this->head->next;
            } else {
                if (maxPrev != nullptr) {
                    maxPrev->next = maxNode->next;
                }
            }
            delete maxNode;
            --(this->size);
        }
    }

    template <typename Data>
    Data& SetLst<Data>::Predecessor(const Data& val) const{ 
        if(this->head == nullptr){ 
            throw std::length_error("The set is empty"); 
        }

        typename List<Data>::Node* prevNode = FindPrev(val); 

        if(prevNode == nullptr){ 
            throw std::length_error("The Set has only one element!!!"); 
        }
       
        return prevNode->val; 
    }


    template <typename Data>
    Data SetLst<Data>::PredecessorNRemove(Data& val){ 
        if (this->head == nullptr) {
            throw std::length_error("The set is empty");
        }
    
        typename List<Data>::Node* predPred = FindPrevOfPrev(val);
        typename List<Data>::Node* pred = nullptr;
        
        if(predPred == nullptr){ 
            pred = this->head; 
            this->head = this->head->next; 
        }else{ 
            pred = predPred->next;
            predPred->next = pred->next; 
        }

        if(pred == nullptr){
            throw std::length_error("no predecessor found"); 
        }

        Data result = pred->val; 
        delete pred; 
        --(this->size);
        return result;
    }

    template <typename Data>
    void SetLst<Data>::RemovePredecessor(Data& val){ 
        if(this->head ==nullptr){ 
            throw std::length_error("The set is empty"); 
        }

        typename List<Data>::Node* predPredNode = FindPrevOfPrev(val); 
        typename List<Data>::Node* predNode = nullptr;
        
        if (predPredNode == nullptr) {
            predNode = this->head;
            this->head = this->head->next;
        } else {
            predNode = predPredNode->next;
            if (predNode == nullptr) {
                throw std::length_error("No predecessor exists for the given value");
            }
            predPredNode->next = predNode->next;
        }
    
        delete predNode;
        --(this->size);

    }

    template <typename Data>
    Data& SetLst<Data>::Successor(const Data& val) const{ 
       typename List<Data>::Node* node = FindSuccNode(val); 
        if(node == nullptr){ 
            throw std::length_error("Set is empty"); 
        }

        if(node->next == nullptr){ 
            throw std::length_error("The value is the tail of the list, has no successor"); 
        }

        return node->val; 
    }

    template <typename Data>
    Data SetLst<Data>::SuccessorNRemove(Data& val){ 
        typename List<Data>::Node* node = FindNode(val); 
        
        if(node == nullptr){ 
            throw std::length_error("Set is empty"); 
        }

        if(node->next == nullptr){ 
            throw std::length_error("The value is the tail of the list, has no successor"); 
        }

        typename List<Data>::Node* succ = node->next;
        Data result = succ->val;  
        node->next = succ->next; 

        delete succ; 
        --(this->size); 
        return result; 
    }

    template <typename Data>
    void SetLst<Data>::RemoveSuccessor( Data& val) {
        typename List<Data>::Node* node = FindNode(val);

        if (node == nullptr) {
            throw std::length_error("The value is not present in the set");
        }

        if (node->next == nullptr) {
            throw std::length_error("The value is the last element, no successor to remove");
        }

        typename List<Data>::Node* succ = node->next;
        node->next = succ->next;
        delete succ;
        --(this->size);
    }

    
/* ************************************************************************** */

    template <typename Data>
    Data& SetLst<Data>::operator[](ulong i) const { 
        if(i >= this->size){ 
            throw std::out_of_range("Went to far! The set is smaller"); 
        }

        typename List<Data>::Node* curr = this->head; 
        for(ulong j = 0; j<i; ++j){ 
            curr = curr->next;
        }
        return curr->val; 
    } 

    template <typename Data>
    bool SetLst<Data>::Exists(const Data& val )const noexcept{ 
        if(this->head == nullptr){ 
            return false;
        }

        typename List<Data>::Node* curr = this->head;


        while(curr != nullptr && curr->val <= val){ 
            if(curr->val == val)return true; 
            curr = curr->next; 
        }
        return false; 
    }

/* ************************************************************************** */

    template <typename Data>
    typename List<Data>::Node* SetLst<Data>::FindPrev(const Data& val) const {
        typename List<Data>::Node* current = this->head;
        typename List<Data>::Node* prev = nullptr;

        while (current != nullptr && current->val < val) {
            prev = current;
            current = current->next;
        }
        return prev;
    }

    template <typename Data>
    typename List<Data>::Node* SetLst<Data>::FindPrevOfPrev(const Data& val) const {
        typename List<Data>::Node* prevPrev = nullptr;
        typename List<Data>::Node* prev = nullptr;
        typename List<Data>::Node* curr = this->head;

        while (curr != nullptr && curr->val < val) {
            prevPrev = prev;
            prev = curr;
            curr = curr->next;
        }

        return prevPrev;
    }

    template <typename Data>
    typename List<Data>::Node* SetLst<Data>::FindSuccNode(const Data& val) const {
        if (this->head == nullptr) {
            return nullptr;
        }

        if (this->head->val == val) {
            return this->head;
        }

        typename List<Data>::Node* current = this->head; 
        while (current != nullptr) {
            if (current->val > val) {
                return current; 
            }
            current = current->next;
        }
        return nullptr; 
    }

    template <typename Data>
    typename List<Data>::Node* SetLst<Data>::FindNode(const Data& val) const {
        typename List<Data>::Node* current = this->head;
        typename List<Data>::Node* prev = nullptr;

        while (current != nullptr && current->val <= val) {
            prev = current;
            current = current->next;
        }

        return prev; 
    }


    template <typename Data>
    std::pair<typename List<Data>::Node*, typename List<Data>::Node*> SetLst<Data>::FindMaxWithPrev() const {
    if (this->head == nullptr) {
        throw std::length_error("The Set is empty");
    }
    typename List<Data>::Node* curr = this->head;
    typename List<Data>::Node* maxNode = curr;
    typename List<Data>::Node* prev = nullptr;
    typename List<Data>::Node* maxPrev = nullptr;

    while (curr != nullptr) {
        if (curr->val >= maxNode->val) {
        maxNode = curr;
        maxPrev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    return {maxNode, maxPrev}; 
    }

    template <typename Data>
    void SetLst<Data>::Print() const {
        typename List<Data>::Node* current = this->head;
        std::cout << "[ ";
        while (current != nullptr) {
            std::cout << current->val;
            if (current->next != nullptr) std::cout << " -> ";
            current = current->next;
        }
        std::cout << " ]\n";
    }


    



}
