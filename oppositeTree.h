#ifndef OPPOSITETREE_H_
#define OPPOSITETREE_H_

#include "player.h"

class OppNode
{
    private:
        OppNode* parent;
        data;
        // need to think if add and ID to oppNode
    
    public:
        OppNode() = default;
        OppNode(OppNode* otherParent) : parent(otherParent), data(T {}) {};
        OppNode(const OppNode& other) = default;
        ~OppNode() = default;
        OppNode& operator=(const OppNode& other) = default; 

        // Getters and Setters
        const T& getData() const { return this->data};
        void setData(const T& newData) {this->data = newData};
        OppNode* getParent() const { return this->parent};
        void SetParent(OppNode* parent) {this->parent = parent};

        OppNode* find(); 
};


/* ------------------------ external function ------------------------*/

template<class T>
OppNode<T>* oppUnion(OppNode<T>* firstHead, int firstSize, OppNode<T>* secondHead, int secondSize, bool bySize)
{
    /*
    can choose if union by size (small to the big) or not.
    //TODO: think if the data the union tree points to is also a parameter to the function

    */

   if(!bySize || firstSize > secondSize)
   {
        secondHead->SetParent(firstHead);

        // try to do give null or defalut value to the second head data
        secondHead->setData(T {});
   }
   
   else
   {
        firstHead->SetParent(secondHead);
        firstHead->setData(T {});
   }


}

/* ------------------------------------------ ------------------------*/


/* ------------------------ function implementetion ---------------------*/


template<class T>
OppNode<T>* OppNode<T>::find()
{
    /*
    returns the highest parent, and change all the node's parent in the
    path between the given node and the highest parent
    */

    OppNode<T>* topParent = nullptr;
    if(this->getParent() == nullptr)
        return this;
    else
    {
        topParent = this->getParent().find();
        this->SetParent(topParent);
        return topParent;
    }      
}

/* ----------------------------------------------------------------------*/

#endif // OPPOSITETREE