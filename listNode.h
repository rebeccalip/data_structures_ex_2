#ifndef LISTNODE_H_
#define LISTNODE_H_

template<class T>
class ListNode
{
    
    private:
        ListNode* next;
        T data;
        int id;

    public:
        ListNode() = default;
        ListNode(const T& data, int id)
        {
            this->data = data;
            this->id = id;
            this->next = nullptr;
        }
        ListNode(const ListNode& other) = delete;
        ListNode& operator=(const ListNode& other) = delete;
        

        //Getters and Setters
        const T& getData() {return this->data;};
        void setData(const T& newData) {this->data = newData;};
        ListNode* getNext() {return this->next;};
        void setNext(ListNode* newNext) {this->next = newNext;};
        int getId() {return this->id;};
        void setId(int newId) {this->id = newId;};

        void insert(ListNode* newNode); 
        bool isInList(int idSearch);
        //ListNode* remove(); //TODO

};

template<class T>
void ListNode<T>::insert(ListNode* newNode)
{
    ListNode* temp = this->next;
    this->next = newNode;
    newNode->next = temp;
}

template<class T>
bool ListNode<T>::isInList(int idSearch)
{
    ListNode* node = this;
    while (node!=nullptr)
    {
        if(node->id == idSearch)
            return true;
        node = node->next;
    }
    return false;
    
}


#endif //LISTNODE