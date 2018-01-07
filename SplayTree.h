//
// Created by Aviv on 29/11/2017.
//

#ifndef DSWET1_SPLAYTREE_H
#define DSWET1_SPLAYTREE_H

#include "Node.h"

/*template <typename T>
void checkVal(Node<T> *root){
    if(root==NULL) return;
    if(root->left_son!=NULL){
        if(root!=root->left_son->parent){
            std::cout<<"OPS-L "<<root->value;
        }
        checkVal(root->left_son);
    }
    if(root->right_son!=NULL){
        if(root!=root->right_son->parent){
            std::cout<<"OPS-R "<<root->value;
        }
        checkVal(root->right_son);
    }
}*/

template <typename T>
class SplayTree {
private:
    Node<T> *root;

    /*
     * Splay the tree rolls the given node up to the root (given algorithm)
     */
    void Splay(Node<T> *node) {
        if (node == NULL) return;
        node->RollItUp();
        root = node;
    }
public:
    /*
     * C'tor.
     */
    SplayTree() {
        root = NULL;
    }

    /*
     * D'tor for the tree
     */
    ~SplayTree(){
        if(root!= NULL){
            root->Destroy_all_Nodes();
        }
    }

    /*
     * gets the Node<T> root from the tree.
     */
    Node<T> *GetRoot() {
        return root;
    }

    /*
     * gets the root value of the tree.
     */
    T GetRootValue() {
        return root->value;
    }

    /*
     * gets the minimum value in the tree.
     */
    void GetMin() {
        if (root == NULL)
            return;
        Splay(root->GetMin());
    }

    /*
     * gets the maximum value in the tree.
     */
    void GetMax() {
        if (root == NULL)
            return;
        Splay(root->GetMax());
    }

    /*
     * returns true if the tree has no elements otherwise false.
     */
    bool IsEmpty() {
        if (root != NULL) {
            return false;
        }
        return true;
    }

    /*
     * inserts a new value to the tree maintains its BST and splay it up to the root.
     * if the value already exists returns false and do nothing otherwise returns true
     */
    bool insert(const T &val, int gladiators_score) {
        if (root == NULL) {
            root = new Node<T>(gladiators_score);
            root->value = val;
            return true;
        }
        Node<T> to_insert = Node<T>(gladiators_score);
        to_insert.value = val;
        Node<T> *inserted = root->Insert(&to_insert, gladiators_score);
        if (inserted != NULL) {
            Splay(inserted);
            return true;
        }
        find(val);
        return false;
    }

    /*
     * finds a given value in the tree if found splay it up to the root and returns true otherwise returns false.
     */
    bool find(const T &val) {
        Node<T> target = Node<T>(0);
        target.value = val;
        Node<T> *found = root->Find(&target);
        if (found == NULL){
            if(root!=NULL){
                while(root->parent!=NULL){
                    root=root->parent;
                }
            }
            return false;
        }
        Splay(found);
        return true;
    }

    /*
     * erase a given value frodm the tree maintains its BST.
     */
    bool erase(const T &val) {
        if (root == NULL) return false;
        if(!find(val)) return false;
        Node<T> *to_delete=root;
        Node<T> *left=to_delete->left_son;
        Node<T> *right=to_delete->right_son;
        to_delete->right_son=NULL;
        to_delete->left_son=NULL;
        if(left!=NULL){
            left->parent= NULL;
        }
        if(right!=NULL){
            right->parent= NULL;
        }
        if(left==NULL){
            root=right;
        } else{
            root=left;
            GetMax();
            root->right_son=right;
            if(right!=NULL) {
                right->parent=root;
            }
        }
        delete to_delete;
        return true;
    }

    /*
     * returns the number of objects in the tree that fulfil the function object condition func.(inorder)
     */
    template<typename R>
    int NumOfObjects(const R &func) {
        if (root == NULL) {
            return 0;
        }
        return root->NumOfSonsWhich(func);
    }

    /*
     * apply the function object func on each of the tree members.(inorder)
     */
    template<typename F>
    void ApplyFunc(F &func) {
        if (root != NULL) {
            root->ApplyFunctionOnNodes(func);
        }
    }

    template <typename F>
    void InverseApplyFunc(F &func){
        if(root!=NULL){
            root->ReverseApplyFunctionOnNodes(func);
        }
    }




    /////////////////for tests

};

/*
template <class T>
std::ostream& operator<<(std::ostream& out,SplayTree<T>& tree) {
    if(!tree.GetRoot()) return out;
    return out << tree.GetRoot();
}
*/


#endif //DSWET1_SPLAYTREE_H
