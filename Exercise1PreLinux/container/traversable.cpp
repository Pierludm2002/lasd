#include "traversable.hpp"

namespace lasd {

/* ************************************************************************** */
//Traversable Container

    //posso usare traverse per implementare la fold
    template <typename Data>
    template <typename Accumulator>
    Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> function, Accumulator  accum) const { //accum deve essere moificata per riferimento
        Traverse([function, &accum](const Data& dat){ //chiamata a funzione implicita
            accum = function(dat, accum); 
        });
        return accum; 
    }

    template <typename Data>
    bool TraversableContainer<Data>::Exists(const Data & value) const noexcept{
        bool exists = false; 
        Traverse(
            [value, &exists](const Data & dat){
                if(value == dat){
                    exists = true; 
                }
            }
        ); 
        return exists; 

    }
/* ************************************************************************** */
//PreOrderTraversableContainer
    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> function, Accumulator  accum) const {
        PreOrderTraverse(
            [function, &accum](const Data& dat){
                accum = function(dat, accum); 
            }
        );
        return accum; 
    }

    template <typename Data>
    void PreOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
        PreOrderTraverse(function); 
    }

/* ************************************************************************** */

//PostOrderTraversableContainer
    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> function, Accumulator accum) const {
        PostOrderTraverse(
            [function, &accum](const Data& dat){
                accum = function(dat, accum); 
            }
        );
        return accum; 
    }

    template <typename Data>
    void PostOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
        PostOrderTraverse(function); 
    }
/* ************************************************************************** */


}
