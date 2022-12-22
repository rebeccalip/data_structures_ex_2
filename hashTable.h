#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "listNode.h"

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
        ~hashTable(); //TODO

        const T& get(int key) const; //TODO
        void insert(int key, const T& data); //TODO
        void remove(int key); //TODO

};

/* ------------------------ function implementetion ---------------------*/

template<class T>
hashTable<T>::hashTable()
{
    this->size = DEFAULT_TABLE_SIZE;
    currentSize = 0;
    maxCurrentSize = 64;
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
            delete currentNode;
            currentNode = temp;
        }
    }

    delete[] data;
}

template<class T>
const T& get(int key) const


/* ----------------------------------------------------------------------*/


#endif // HASHTABLE