#include "list.hpp"

namespace lasd {

    /* ************************************************************************** */
    template <typename Data> //data copy constr
    List<Data>::Node::Node(const Data & data){ 
        val = data; 
        next = nullptr; 
    }

    template <typename Data> //data move constr
    List<Data>::Node::Node(Data && data) noexcept{ 
        std::swap(data , val);  
    }

    template <typename Data>
    List<Data>::Node::Node(const Node & node){ 
        val = node.val; 
        next = node.next; 
    }

    template <typename Data>
    List<Data>::Node::Node(Node && node) noexcept{ 
        std::swap(node.val, val); 
        std::swap(node.next, next); 
    }

    template <typename Data> 
    List<Data>::Node::~Node(){
        // if(next != nullptr){ 
        //     delete next; 
        // }
    }

    template <typename Data>
    inline bool List<Data>::Node::operator==(const Node& node) const noexcept{ 
        return (val == node.val && next == node.next); 
    }

    template <typename Data>
    inline bool List<Data>::Node::operator!=(const Node & node) const noexcept{ 
        return !(*this == node);
    }

    /* ************************************************************************** */

    template <typename Data>
    List<Data>::List(const TraversableContainer<Data> & cont){ 
        cont.Traverse([this](const Data& data){
            InsertAtBack(data);
        });
    }

    template <typename Data>
    List<Data>::List(MappableContainer<Data> && cont){ 
        cont.Map([this](const Data & data){
            InsertAtBack(std::move(data)); 
        }); 
    }

    template <typename Data>
    List<Data>::List(const List<Data> & list){ 
        Node *temp = list.head; 
        while(temp != nullptr){
            InsertAtBack(temp->val);
            temp = temp->next;
        }
    }

    template <typename Data>
    List<Data>::List(List<Data> && list){
        std::swap(head, list.head);
        std::swap(size, list.size);
    }

    template <typename Data>
    List<Data>::~List(){ 
        delete head;
        head = nullptr;
        size = 0;
    }

    template <typename Data>
    List<Data> & List<Data>::operator=(const List<Data>& list){ 
        if(list.size == 0){ 
            Clear();
            return *this;
        }

        if(this!=&list){
            Node *temp = list.head; 
            while(temp != nullptr){ 
                InsertAtBack(temp->val);
                temp = temp->next;
            } 
        }
    return *this;
    }

    template <typename Data>
    List<Data> & List<Data>::operator=(List<Data> &&list) noexcept{
        if(this != &list){
            Clear();
            std::swap(head, list.head);
            std::swap(size, list.size);
            
            //invalidazione della lista passata
            list.head = nullptr;
            list.size = 0;
        }
        return *this;
    }

    template <typename Data>
    inline bool List<Data>::operator==(const List<Data> & list) const noexcept{ 

        if(size != list.size) return false;

        Node *thisNode = head;
        Node *otherNode = list.head;
        while(thisNode != nullptr && otherNode != nullptr) {//so che hanno stessa dimensione!
            if(thisNode->val != otherNode->val) return false;
            thisNode = thisNode->next;
            otherNode = otherNode->next;
        }
        return true;
    }

    template <typename Data>
    inline bool List<Data>::operator!=(const List<Data> & list) const noexcept{ 
        return !(*this == list);
    }

    /* ************************************************************************** */

    template <typename Data>
    void List<Data>::InsertAtFront(const Data & data){ 
        Node *newNode = new Node(data); 
        if(this->head == nullptr){
            this->head = newNode; 
        }else{ 
            newNode->next = this->head; 
            this->head = newNode; 
        }
        size++; 
    }

    template <typename Data>
    void List<Data>::InsertAtFront(Data && data){ 
        typename List<Data>::Node *newNode = new typename List<Data>::Node(std::move(data)); 
        if(this->head == nullptr){
            this->head = newNode; 
        }else{ 
            newNode->next = this->head; 
            this->head = newNode; 
        }
        this->size++; 
    }

    template <typename Data>
    void List<Data>::RemoveFromFront(){
        if(size == 0){ 
            throw std::length_error("The List is Empty"); 
        }

        Node* temp = this->head->next; 
        delete this->head; 
        head = temp; 
        --size; 
    }

    template <typename Data>
    Data List<Data>::FrontNRemove(){
        if(size == 0){ 
            throw std::length_error("The List is Empty"); 
        }
        Data front = std::move(head->val); 
        RemoveFromFront(); 
        return front; 
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data&& val){
        Node* newNode = new Node(std::move(val));
        if (size == 0) {
            head = tail = newNode;
          } else {
            tail->next = newNode;
            tail = newNode;
          }
          ++size;
    }

        
    template <typename Data>
    void List<Data>::InsertAtBack(const Data& val) {
        Node* newNode = new Node(val);
        if (size == 0) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    template <typename Data>
    void List<Data>::RemoveFromBack() {
        if (size == 0) {
            throw std::length_error("The List is Empty");
        }
        if (size == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* prev = head;
            while(prev->next != tail){ 
                prev = prev->next; 
            }
            delete tail;
            tail = prev;
            tail->next = nullptr;
        }
        --size;
    }


    template <typename Data>
    Data List<Data>::BackNRemove() {
        if (size == 0) {
            throw std::length_error("The List is Empty");
        }
        Data value = std::move(tail->val);
        RemoveFromBack();
        return value;
    }


/* ************************************************************************** */


    template <typename Data>
    Data & List<Data>::operator[](unsigned long i){
        if (i >= this->size) {
            throw std::out_of_range("Index out of range");
        }
        Node *current = this->head;
        for (unsigned long j = 0; j < i; ++j) {
            current = current->next;
        }
        return current->val;
    }

    template <typename Data>
    const Data & List<Data>::operator[]( ulong i) const {
        if(i >= this->size){ 
            throw std::out_of_range("Index out of range");
        }

        Node * current = this->head; 
        for(ulong j=0; j<i; ++j){
            current=current->next;
        }
        return current->val; 
    }

    template <typename Data>
     Data & List<Data>::Front(){
        if(size == 0){
            throw std::length_error("List is empty");
        }

        return head->val;
    }

    template <typename Data>
    const Data& List<Data>::Front() const{ 
        if(size == 0){ 
            throw std::length_error("List is empty"); 
        }
        return head->val;
    }

    template <typename Data>
    Data& List<Data>::Back() {
      if (size == 0) {
        throw std::length_error("List is empty");
      }
      return tail->val;
    }
    

    template <typename Data>
    const Data& List<Data>::Back() const {
      if (size == 0) {
        throw std::length_error("List is empty");
      }
      return tail->val;
    }

/* ************************************************************************** */

    template <typename Data>
    inline void List<Data>::Map(MapFun fun){
        PreOrderMap(fun); 
    }

    template <typename Data>
    inline void List<Data>::PostOrderMap(MapFun fun){ 
        Node* current = head; 
       for(ulong i = size; i > 0; ++i){
            fun(current->val);
            current = current->next;
        }

    }

    template <typename Data>
    inline void List<Data>::PreOrderMap(MapFun fun){ 
        Node* current = head; 
        while(current != nullptr){
            fun(current->val);
            current = current->next;
        }
    }

/* ************************************************************************** */

    template <typename Data>
    void List<Data>::Traverse(TraverseFun fun)const{ 
        PreOrderTraverse(fun); 
    }

    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun)const{ 
        std::stack<Node*> stack;
        Node* current = head;
        while (current != nullptr) {
            stack.push(current);
            current = current->next;
        }

        while (!stack.empty()) {
            fun(stack.top()->val);
            stack.pop();
        }
    }

    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun)const{ 
        Node* current = head;
        while (current != nullptr) {
          fun(current->val);
          current = current->next;
        }
    }

/* ************************************************************************** */


    template <typename Data>
    void List<Data>::Clear(){ 
        delete head; 
        head = tail =nullptr; 
        size = 0; 
    }    
}
