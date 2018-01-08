//
// Created by Aviv on 29/11/2017.
//

#ifndef DSWET1_NODE_H
#define DSWET1_NODE_H

#include <stdlib.h>

template <typename T>
class Node {
public:
    Node *parent;
    Node *left_son;
    Node *right_son;
    T value;
    int personal_score;
    int subtree_size;
    int subtree_score_sum;

    Node(int my_score) {
        parent = NULL;
        left_son = NULL;
        right_son = NULL;
        subtree_size=1;
        subtree_score_sum=my_score;
        personal_score=my_score;
    }

    /*
     * given a Node "this", Gets the maximum value in the Splay BST.
     */
    Node *GetMax() {
        if (right_son == NULL) return this;
        return right_son->GetMax();
    }

    /*
     * given a Node "this", Gets the minimum value in the Splay BST.
     */
    Node *GetMin() {
        if (left_son == NULL) return this;
        return left_son->GetMin();
    }

    /*
     * given a root "this" and a Node "target", Gets the Node in the Tree that has the same value like target.
     * returns NULL if not found.
     */
    Node *Find(Node *target) {
        if (this == NULL) return NULL;
        if (value == target->value) return this;
        if (target->value < value) {
            if(left_son!= NULL){
                return left_son->Find(target);
            } else{
                RollItUp();
                return NULL;
            }
        } else {
            if(right_son!= NULL){
                return right_son->Find(target);
            } else{
                RollItUp();
                return NULL;
            }
        }
    }

    /*
     * updates my parents with the score and the tree size
     */
    void update_daddies(){
        Node *iterator=parent;
        while(iterator!=NULL){
            iterator->subtree_score_sum+=subtree_score_sum;
            iterator->subtree_size++;
            iterator=iterator->parent;
        }
    }

    /*
     * Given a root "this" and a Node, Inserts a copy of the Node to the tree while maintaining the BST.
     * returns the inserted node or NULL if this node already exists.
     */
    Node *Insert(Node *newMember, int score) {
        if (newMember->value == value){
            return NULL;
        }
        if (newMember->value > value) {
            if (right_son == NULL) {
                right_son = new Node(score);
                right_son->value = newMember->value;
                right_son->parent = this;
                right_son->update_daddies();
                return right_son;
            } else {
                return right_son->Insert(newMember, score);
            }
        } else {
            if (left_son == NULL) {
                left_son = new Node(score);
                left_son->value = newMember->value;
                left_son->parent = this;
                left_son->update_daddies();
                return left_son;
            } else {
                return left_son->Insert(newMember, score);
            }
        }
    }

    /*
     * remove a given node from the tree, returns true if success otherwise false.
	 * this function was never used
     */
    bool Erase(Node *target) {
        Node *actual = Find(target);
        if (actual == NULL) {
            return false;
        }
        Node *pp = actual->parent;
        if (actual->right_son == NULL && actual->left_son == NULL) {
            if (pp->left_son == actual) {
                pp->left_son = NULL;
            } else {
                pp->right_son = NULL;
            }
            delete actual;
            return true;
        }
        if (actual->right_son == NULL || actual->left_son == NULL) {
            if (actual->right_son == NULL) {
                if (pp->left_son == actual) {
                    pp->left_son = actual->left_son;//
                } else {
                    pp->right_son = actual->left_son;//
                }
                actual->left_son->parent = pp;//
            } else {
                if (pp->left_son == actual) {
                    pp->left_son = actual->right_son;//
                } else {
                    pp->right_son = actual->right_son;//
                }
                actual->right_son->parent = pp;
            }
            delete actual;
            return true;
        }
        Node *replace_with = actual->right_son->GetMin();
        T temp = replace_with->value;
        replace_with->value = actual->value;
        actual->value = temp;
        return replace_with->Erase(replace_with);
    }

    /*
     * updates myself acording to my 2 sons, assumes that both of my sons values are valid
     */
    void updateMyself() {
        subtree_score_sum = personal_score;
        subtree_size = 1;
        if (left_son != NULL) {
            subtree_size += left_son->subtree_size;
            subtree_score_sum += left_son->subtree_score_sum;
        }
        if (right_son != NULL) {
            subtree_size += right_son->subtree_size;
            subtree_score_sum += right_son->subtree_score_sum;
        }
    }

    /*
     * rotates the Nodes right (given algorithm), assumes I am a left son of my dad.
     */
    void RotateRight() {
        Node *P = parent;
        Node *N = this;
        Node *Y = right_son;
        Node *PP = NULL;
        if (parent != NULL) {
            PP = parent->parent;
        }
        P->left_son = Y;
        if (Y != NULL) {
            Y->parent = P;
        }
        P->updateMyself();//<----
        P->parent = N;
        N->right_son = P;
        N->updateMyself();//<----
        N->parent = PP;
        if (PP != NULL) {
            if (PP->right_son == P) {
                PP->right_son = N;
            } else {
                PP->left_son = N;
            }
        }
    }

    /*
     * rotates the Nodes left (given algorithm), assumes I am a right son of my dad.
     */
    void RotateLeft() {
        Node *P = parent;
        Node *N = this;
        Node *Y = left_son;
        Node *PP = NULL;
        if (parent != NULL) {
            PP = parent->parent;
        }
        P->right_son = Y;
        if (Y != NULL) {
            Y->parent = P;
        }
        P->updateMyself();//<----
        P->parent = N;
        N->left_son = P;
        N->updateMyself();//<----
        N->parent = PP;
        if (PP != NULL) {
            if (PP->right_son == P) {
                PP->right_son = N;
            } else {
                PP->left_son = N;
            }
        }
    }

    /*
     * given a root and a node, rolls the node up to the root while using the given algorithms from the tutorials
     * (zig, zigzig, zigzag) maintaining the BST.
     */
    void RollItUp() {
        Node *p, *pp, *me = this;
        if (parent == NULL) return;
        p = parent;
        if (parent->parent == NULL) {//zig
            if (p->right_son == this) {
                RotateLeft();
            } else {
                RotateRight();
            }
            return;
        }
        pp = p->parent;
        if (pp->right_son == p && p->left_son == this) {//zigzag
            RotateRight();
            RotateLeft();
            RollItUp();
            return;
        }
        if (pp->left_son == p && p->right_son == this) {//symmetric zigzag
            RotateLeft();
            RotateRight();
            RollItUp();
            return;
        }
        if (pp->right_son == p && p->right_son == this) {//zigzig
            p->RotateLeft();
            me->RotateLeft();
            RollItUp();
            return;
        }
        if (pp->left_son == p && p->left_son == this) {//symmetric zigzig
            p->RotateRight();
            me->RotateRight();
            RollItUp();
            return;
        }
    }

    /*
     * given a function object func and a root returns the number of elements in the tree that fulfils the given function object
     */
    template<typename R>
    int NumOfSonsWhich(const R &func) {
        int leftSons = 0, rightSons = 0;
        if (left_son != NULL) {
            leftSons = left_son->NumOfSonsWhich(func);
        }
        if (func(value)) {
            leftSons++;
        }
        if (right_son != NULL) {
            rightSons = right_son->NumOfSonsWhich(func);
        }
        return leftSons + rightSons;
    }

    /*
     * given a function object and a root and apply the function on each of the tree members (inorder)
     */
    template<typename F>
    void ApplyFunctionOnNodes(F &func) {
        if (left_son != NULL) {
            left_son->ApplyFunctionOnNodes(func);
        }
        func(value);
        if (right_son != NULL) {
            right_son->ApplyFunctionOnNodes(func);
        }
    }

    template <typename F>
    void ReverseApplyFunctionOnNodes(F &func){
        if (right_son != NULL) {
            right_son->ReverseApplyFunctionOnNodes(func);
        }
        func(value);
        if (left_son != NULL) {
            left_son->ReverseApplyFunctionOnNodes(func);
        }
    }

    /*
     * destroys all the nodes considers "this" the root (post order)
     */
    void Destroy_all_Nodes(){
        if(left_son!= NULL){
            left_son->Destroy_all_Nodes();
        }
        if(right_son!= NULL){
            right_son->Destroy_all_Nodes();
        }
        delete this;
    }

    int GetScoreOfBest(int k){
        if(k==0){
            return 0;
        }
        if(k>subtree_size){
            return -1;
        }
        if(right_son!=NULL) {
            if(k==right_son->subtree_size){
                return right_son->subtree_score_sum;
            }
            if(k<right_son->subtree_size){
                return right_son->GetScoreOfBest(k);
            }
            return personal_score + right_son->subtree_score_sum+left_son->GetScoreOfBest(k-1-right_son->subtree_size);
        } else{
            return personal_score+left_son->GetScoreOfBest(k-1);
        }
    }


/////// for tests

};


/*
template<class T>
std::ostream& operator<<(std::ostream& out, Node<T> *node) {
    if(!node) {
        return out;
    }
    out << node->left_son;
    out << " " << node->value;
    out << node->right_son;
    return out;
}
*/


#endif //DSWET1_NODE_H
