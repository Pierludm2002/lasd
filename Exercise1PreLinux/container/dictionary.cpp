#include "dictionary.hpp"

namespace lasd {

/* ************************************************************************** */

template<typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & TContainer){ //da classdiagram deve usare Traversable (uses)
    bool all = true; 
    TContainer.Traverse(
        [this, &all](const Data & data){ 
            all &= Insert(data); 
        }
    ); 
    return all; 

}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> && MContainer){ 
    bool all= true;
    MContainer.Map(
        [this, &all](Data & data){ 
            all &= Insert(data);
        }
    ); 
    return all; 
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> & TContainer){ 
    bool all= true;
    TContainer.Traverse(
        [this, &all](const Data & data){ 
            all &= Remove(data); 
        }
    ); 
    return all; 
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & TContainer){ 
    bool some= false;
    TContainer.Traverse(
        [this, &some](const Data & data){ 
            some |= Insert(data); //ritorna true se Insert ha successo (in almeno un caso). 
        }
    ); 
    return some; 
}
template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> && MContainer){ 
    bool some= false;
    MContainer.Map(
        [this, &some](Data & data){ 
            some |= Insert(data); 
        }
    ); 
    return some; 
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> & TContainer){ 
    bool some= false;
    TContainer.Traverse(
        [this, &some](const Data & data){ 
            some |= Remove(data); 
        }
    ); 
    return some; 
}


/* ************************************************************************** */

}
