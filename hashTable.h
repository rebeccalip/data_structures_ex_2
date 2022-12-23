#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "listNode.h"
#include "exception.h"

const int DEFAULT_TABLE_SIZE = 64;

template<class T>
class hashTable
{
    private:
        int size;
        int maxCurrentSize;
        int currentSize;
        ListNode<T>** data;

        void resize();

        int hashFunc(int num) {return num % size};

        
    
    public:
        hashTable();
        hashTable(cosnt hashTable& other) = delete;
        hashTable& operator=(const hashTable& other) = delete;
        ~hashTable();
        bool isInTable(int key) const; 

        const T& get(int key) const; 
        void insert(int key, const T& data);
        //void remove(int key); //TODO

};

/* ------------------------ function implementetion ---------------------*/

template<class T>
hashTable<T>::hashTable()
{
    this->size = DEFAULT_TABLE_SIZE;
    currentSize = 0;
    maxCurrentSize = DEFAULT_TABLE_SIZE;
    this->data = new ListNode<T>*[size];
}

template<class T>
void hashTable<T>::resize()
{
    int newSize = this->size * 2;
    this->size = newSize;
    ListNode<T>** newData = new ListNode<T>*[newSize];
    for (int i = 0; i < size; i++)
    {
        ListNode<T>* currentNode = data[i];
        while (currentNode != nullptr)
        {
            ListNode<T>* temp = currentNode->getNext();
            currentNode->setNext(nullptr);
            if(newData[hashFunc(currentNode->getId())] != nullptr)
                newData[hashFunc(currentNode->getId())]->insert(currentNode);
            else
                newData[hashFunc(currentNode->getId())] = currentNode;
            currentNode = temp;
        }
    }

    maxCurrentSize = newSize;
    delete[] data;
    this->data = newData;
}

template<class T>
hashTable<T>::~hashTable()
{
    for(int i=0; i< size; i++)
    {
        ListNode<T>* currentNode = data[i];
        while(currentNode != nullptr)
        {
            ListNode<T>* temp = currentNode->getNext();
            if(currentNode->getData() != nullptr) // assume the data in the linked list is pointer
                delete currentNode->data;
            delete currentNode;
            currentNode = temp;
        }
    }

    delete[] data;
}

template<class T>
const T& hashTable<T>::get(int key) const
{
    ListNode<T>* currentNode = data[hashFunc(key)];
    if(currentNode == nullptr)
        throw NoKeyFounded(); // cant return "default" value casue dont know what T is
    if(currentNode->isInList(key))
    {
        while (currentNode != nullptr)
        {
            if(currentNode->getId() == key)
                return currentNode->getData();
            else
                currentNode = currentNode->next;
        }
    }

    throw NoKeyFounded();
}

template<class T>
bool hashTable<T>::isInTable(int key) const
{
    ListNode<T>* currentNode = data[hashFunc(key)];
    if(currentNode == nullptr)
        return false;
    if(currentNode->isInList(key))
        return true;
    return false;
}

template<class T>
void hashTable<T>::insert(int key, const T& data)
{
    if(isInTable(key))
        return;

    ListNode<T>* currentNode = data[hashFunc(key)];
    if(currentNode == nullptr)
        currentNode = new ListNode<T>(data, key);
    else
        currentNode->insert(new ListNode<T>(data, key));
    currentSize++;
    if(currentSize == maxCurrentSize)
        resize();
    
}


/* ----------------------------------------------------------------------*/


#endif // HASHTABLE