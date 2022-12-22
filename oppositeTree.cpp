#include "oppositeTree.h"

OppNode* OppNode::find()
{
    /*
    returns the highest parent, and change all the node's parent in the
    path between the given node and the highest parent
    */

    OppNode* topParent = nullptr;
    if(this->getParent() == nullptr)
        return this;
    else
    {
        topParent = this->getParent()->find();
        this->SetParent(topParent);
        return topParent;
    }      
}

OppNode* oppUnion(OppNode* firstHead, int firstSize, OppNode* secondHead, int secondSize, bool FirstBuySecond)
{
    /*
    *@FirstBuySecond - first team buys the second team
    //TODO: think if the data the union tree points to is also a parameter to the function

    */

   // 1 of 4 case
   if(FirstBuySecond || firstSize > secondSize)
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


};
