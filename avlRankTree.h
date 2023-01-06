#ifndef AVLRANKTREE_H_
#define AVLRANKTREE_H_

#include <iostream>
#include <exception>
#include "exception.h"

template <class T, class S>
class AvlRankTree
{
    class Node
    {
        private:
            S key;
            Node* left;
            Node* right;
            T value;
            int height;
            int rank;
    
        public:
        friend class AvlRankTree<T, S>;

        Node(const S& key, const T& value): key(key), value(value){
                    left= nullptr;
                    right= nullptr;
                    height=0;
                    rank=1;
                }

                const T& getValue() const
                {
                    return this->value;
                }

                int getHeight() const
                {
                    return this->height;
                }

                int getBalanceFactor() const
                {
                    if (this ->left == nullptr && this->right == nullptr)
                        return 0;
                    else if (this ->left == nullptr && this->right != nullptr)
                        return (-1 - this->right->calcHeight());
                    else if (this ->left != nullptr && this->right == nullptr)
                        return this->left->calcHeight() + 1;
                    else
                        return (this->left->calcHeight() - this->right->calcHeight());
                }

                int calcHeight() const 
                {
                    if (this ->left == nullptr && this->right == nullptr)
                        return 0;
                    else if (this ->left == nullptr && this->right != nullptr)
                        return this->right->calcHeight() + 1;
                    else if (this ->left != nullptr && this->right == nullptr)
                        return this->left->calcHeight() + 1;
                    else
                        return max(this->left->calcHeight(), this->right->calcHeight()) + 1;    
                }

                int calcRank() const
                {
                    int sum=1;
                    if(this->left != nullptr)
                        sum+=this->left->rank;
                    if(this->right != nullptr)
                        sum+=this->right->rank;
                    return sum;
                }
    };

    Node* root;

    /*---------------------privete func------------------------------------*/

    /*-------- rotation functions ---------------*/
    Node* rotateRight(Node* root);// working
    Node* rotateLeft(Node* root); // working
    Node* rotate(Node* root); // working
    Node* insertHelper(const S& key, const T& value, Node* node); // working


    /*Helper functions*/
    Node* getLeft();
    Node* getRight();
    static int max(int a, int b) //yes
    {
        return (a > b) ? a : b;
    }
     
    void removeTree(Node* node); //yes
    Node* internalRemoveNode(const S& key, Node* tree); //yes


    Node* findHelper(const S& key,Node* tree); //yes
    Node* findFatherHelper(const S& key, Node* tree) const;
    const S& getMaxKeyHelper(Node* node);
    const T& getMaxValueHelper(Node* node);
    void printInorderHelper(Node* treeToPrint) const;
    Node* getMinCloserHelper(Node* node, const S& keyMin);
    int getRankHelper(const S& key, Node* node) const;
    Node* selectHelper(const int k, Node* node) const;

    public:
        AvlRankTree() {root=nullptr;}; //yes
        AvlRankTree(Node* root1) : root(root1) {}; //yes
        AvlRankTree(const AvlRankTree& other) = default;
        ~AvlRankTree(); //yes
        AvlRankTree& operator=(const AvlRankTree& other) = default;
        void insert(const S& key, const T& value); //yes
        void remove(const S& key); //yes
        Node* getRoot()
        {
            return this->root;
        }
        Node* find(const S& key);//yes
        void printInorder() const;
        Node* findFather(const S& key) const;
        int getRank(const S& key) const;
        Node* select(const int k) const;

        //binary tree functions
        Node* getNextMinValue(Node* node); //yes
        const S& getMaxKey();
        const T& getMaxValue();
        Node* getMinCloser(const S& keyMin);

};


/* ------------------------ function implementetion ---------------------*/

 /*------------------------ rotation functions impl ------------------------------*/

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::rotateRight(Node* root)
{
    if (root == nullptr || root->left == nullptr)
        return root;
    Node* rootLeft = root->left;
    Node* rootLeftRight = rootLeft->right;

    rootLeft->right = root;
    root->left = rootLeftRight;

    //calc heights of nodes
    root->height = root->calcHeight();
    rootLeft->height = rootLeft->calcHeight();

    //update ranks
    root->rank = root->calcRank();
    rootLeft->rank = rootLeft->calcRank();
    /*
    if(rootLeft-> left != nullptr)
        rootLeft->rank = 1 + rootLeft->left->rank + root->rank;
    else
        rootLeft->rank = 1 + root->rank;
    */


    return rootLeft;
}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::rotateLeft(Node* root)
{
    if (root == nullptr || root->right == nullptr)
        return root;
    Node* rootRight = root->right;
    Node* rootRightLeft = rootRight -> left;

    rootRight->left = root;
    root->right = rootRightLeft;

    //calc heights of nodes
    root->height = root->calcHeight();
    rootRight->height = rootRight->calcHeight();

    //update ranks
    root->rank = root->calcRank();
    rootRight->rank = rootRight->calcRank();

    /*
    if(rootRight ->right != nullptr)
        rootRight->rank = 1 + rootRight->right->rank + root->rank;
    else
        rootRight->rank = 1 + root->rank;
    */

    return rootRight;
}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::rotate(Node* root)
{
    if(root == nullptr)
        return nullptr;
    if(root->getBalanceFactor() > 1)
    {
        // LL rotation
        if( root->left->getBalanceFactor() > -1)
        {
            return rotateRight(root);
        }
        // LR rotation
        else if(root->left->getBalanceFactor() == -1)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        else
        {
            // need to think what to put here
            std::cout << "invalid balance factors in tree" << std::endl;
            return root;
        }
    }
    else if (root->getBalanceFactor() < -1)
    {
        // RR rotation
        if( root->right->getBalanceFactor() < 1)
        {
            return rotateLeft(root);
        }
        // RL rotation
        else if (root->right->getBalanceFactor() == 1)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        else
        {
            // need to think what to put here
            std::cout << "invalid balance factors in tree" << std::endl;
            return root;
        }
    }
    else
    {
        return root;
    }

}


template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::insertHelper(const S& key, const T& value, Node* node)
{
    if(node == nullptr)
    {
        return new Node(key, value);
    }

    
    if(key < node->key)
        node->left = insertHelper(key, value, node->left);  
    else if(key > node->key)
        node->right = insertHelper(key, value, node->right);
    else
        throw InvalidKey();
    
    node->height = node->calcHeight();
    node->rank = node->calcRank();
    
    //return node;
    return rotate(node);
}






 /*--------------------------------------------------------------------------*/

template <class T, class S>
AvlRankTree<T,S>::~AvlRankTree()
{
    removeTree(root);
}

template <class T, class S>
void AvlRankTree<T,S>::removeTree(Node* node)
{
    if(node==nullptr)
        return;
    if(node->left != nullptr)
        removeTree(node->left);
    if(node->right != nullptr)
        removeTree(node->right);
    delete node;
}


/*
* the function insert a new node to the AVL tree.
*
*throws : bad_alloc if an allocation fails
*         InvalidKey if the key alredy exict at the tree.
*/

template <class T, class S>
void AvlRankTree<T,S>::insert(const S& key, const T& value)
{
    if(find(key) != nullptr)
        throw InvalidKey();

   this->root = insertHelper(key, value, this->root);
}


template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::internalRemoveNode(const S& key, Node* tree)
{
    if(tree == nullptr)
    {
        return tree;
    }
    if (key > tree->key)
    {
        tree->right = internalRemoveNode(key, tree->right);
    }
    else if (key < tree->key)
    {
        tree->left = internalRemoveNode(key, tree->left);
    }
    else
    {
        //The current node is the node to delete
        //delete it like in binary tree

        // case of one child or no child
        if(tree->left == nullptr || tree->right == nullptr)
        {
            Node* child = tree->left? tree->left: tree->right;
            
            //case there is no child
            if(child == nullptr)
            {
                child = tree;
                tree = nullptr;
                
            }
            // case of one child
            else
            {
                
                Node* father = findFather(tree->key);
                if (father == nullptr)
                {
                    Node* temp = tree;
                    tree = child;
                    child = temp;
                }
                else
                {
                    Node* temp = child;
                    bool is_exist_right = (father->right != nullptr);
                    bool is_exist_left = (father->left != nullptr);
                    if (is_exist_left && father->left->key == tree->key)
                    {
                        father->left=temp;
                    }
                    if (is_exist_right && father->right->key == tree->key)
                    {
                        father->right=temp;
                    }
                
                    child = tree;
                    tree = temp;
                }

                
            }
            delete child;
        }
            
        // case of two children
        else
        {
            Node* minVal = getNextMinValue(tree);
            //*tree = *minVal;
            tree->key = minVal->key;
            tree->value = minVal->value;
            tree->right = internalRemoveNode(minVal->key, tree->right);
        }
    }

    if(tree == nullptr)
        return tree;
    
    //update the height
    tree->height = tree->calcHeight();
    tree->rank = tree->calcRank();

    //check if balnace is okey and and change it if not
    tree = rotate(tree);

    return tree;
}

template <class T, class S>
void AvlRankTree<T,S>::remove(const S& key)
{
    this->root = internalRemoveNode(key, this->root);
}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::getNextMinValue(Node* node)
{
    if(node == nullptr)
    {
        return nullptr;
    }
    if(node->right == nullptr)
    {
        return node;
    }
    else
    {
        Node* current = node->right;
        while(current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }
}


template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::findHelper(const S& key, Node* node)
{
    if(node==nullptr || key == node->key)
        return node;
    else if(key < node->key)
        return findHelper(key, node->left);
    else
        return findHelper(key, node->right);
}

/*
* the function returns a pointer to the node which key is given.
* If such ket doesn't exict at the tree , return NULL
*/
template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::find(const S& key)
{
    return findHelper(key, root);
}

template <class T, class S>
const S& AvlRankTree<T,S>::getMaxKey()
{
    return getMaxKeyHelper(root);
}

template <class T, class S>
const S& AvlRankTree<T,S>::getMaxKeyHelper(Node* node)
{
    if(node->right == nullptr)
        return node->key;

    return getMaxKeyHelper(node->right);
}

template <class T, class S>
const T& AvlRankTree<T,S>::getMaxValueHelper(Node* node)
{
    if(node->right == nullptr)
        return node->value;

    return getMaxValueHelper(node->right);
}

template <class T, class S>
const T& AvlRankTree<T,S>::getMaxValue()
{
    return getMaxValueHelper(root);
}

template <class T, class S>
void AvlRankTree<T,S>::printInorderHelper(Node* treeToPrint) const
{
    if(treeToPrint == nullptr)
    {
        return;
    }    
    printInorderHelper(treeToPrint->left);
    // prints key, balance factor
    std::cout << "key:" << treeToPrint->key << " , balance factor:" << treeToPrint->getBalanceFactor()<< " , height:" << treeToPrint->getHeight() << std::endl;
    printInorderHelper(treeToPrint->right);
    
}

template <class T, class S>
void AvlRankTree<T,S>::printInorder() const 
{
    printInorderHelper(this->root);
}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::findFatherHelper(const S& key, Node* node) const
{
    // if the key is root's key or the node is null - return null
    if(node==nullptr || key == node->key)
        return nullptr;
    else if(key < node->key)
    {
        if(node->left != nullptr)
        {
            if(node->left->key == key)
                return node;
            else
                return findFatherHelper(key, node->left);
        }
        else
        {
            // no key in the tree
            return nullptr;
        }
    }
    else
    {
        if(node->right != nullptr)
        {
            if(node->right->key == key)
                return node;
            else
                return findFatherHelper(key, node->right);
        }
        else
        {
            // no key in the tree
            return nullptr;
        }
    }

}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::findFather(const S& key) const
{
    return findFatherHelper(key, this->root);
}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::getMinCloserHelper(Node* node, const S& keyMin)
{
    if (node == nullptr)
        return nullptr;
    if (node->key == keyMin)
        return node;
    else if (keyMin < node->key)
    {
        Node* other = getMinCloserHelper(node->left, keyMin);
        if (other == nullptr)
            return node;
        return (other->key < node->key ? other : node);
    }
    else
    {
        return getMinCloserHelper(node->right, keyMin);
    }
}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::getMinCloser(const S& keyMin)
{
    return getMinCloserHelper(root, keyMin);
}

template <class T, class S>
int AvlRankTree<T,S>::getRankHelper(const S& key, Node* node) const
{
    if (node == nullptr)
        return 0;

    if(node->key == key)
        return 1 + node->left->rank;

    if (node->key < key)
    {
        if (node->left != nullptr)
            return (1 + node->left->rank + getRankHelper(node->right));
        return (1 + getRankHelper(node->right));
    }
    else
    {
        return getRankHelper(node->left);
    }
}

template <class T, class S>
int AvlRankTree<T,S>::getRank(const S& key) const
{
    if (find(key) == nullptr)
        return 0;

    return getRankHelper(key, root);
}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::selectHelper(const int k, Node* node) const
{   
    if(node->left == nullptr && node->right==nullptr)
        return node;
    if(node->left == nullptr)
    {
        if(k==0)
            return node;
        return selectHelper(k-1, node->right);
    }
    if(node->right == nullptr)
    {
        if(k==node->rank-1)
            return node;
        return selectHelper(k, node->left);
    }
    if(node->left->rank == k)
        return node;
    if(node->left->rank > k-1)
        return selectHelper(k, node->left);
    return selectHelper(k- node->left->rank -1 , node->right);

    /*
    if(node->left == nullptr && node->right==nullptr)
        return node;

    if(node->left != nullptr && node->left->rank == k-1)
    {
        return node;
    }
        
    if(node->left == nullptr && k==1)
    {
        return node;
    }
        
    if(node->left != nullptr && node->left->rank > k-1)
    {
        return selectHelper(k, node->left);
    }     
    if((node->left != nullptr && node->left->rank < k-1))
    {
        return selectHelper(k - node->left->rank - 1, node->right); 
    }
    else
    {
        return selectHelper(k-1, node->right);
    }
    */
}

template <class T, class S>
typename AvlRankTree<T,S>::Node* AvlRankTree<T,S>::select(const int k) const
{
    return selectHelper(k, root);  
}

#endif
