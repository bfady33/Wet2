//
// Created by Fady on 1/7/2018.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "HTList.h"

class HashTable {
private:
    int size;
    int num_of_obj;
    HTList *hash;
public:
    ~HashTable(){
        HTList current_list;
        HashNode *iterator, *to_del;
        for (int i = 0; i < size; ++i) {
            current_list=hash[i];
            iterator=current_list.head;
            while(iterator!=NULL){
                delete iterator->Gteam;
                to_del=iterator;
                iterator=iterator->next;
                delete to_del;
            }
        }
        delete [] hash;
    }

    HashTable(int n){
        hash=new HTList[n];
        size=n;
        num_of_obj=0;
    }

    Group *getGroup(int ID){
        if(ID<0){
            throw Invalid_Input();
        }
        HashNode *iterator=hash[ID%size].head;
        while(iterator!=NULL){
            if(ID==iterator->Gteam->getID()){
                return iterator->Gteam;
            }
            iterator=iterator->next;
        }
        return NULL;
    }
/*
    void Insert(Group *g1){
        if(size<=num_of_obj){
            ReHash();
        }
        if(getGroup(g1.))//check if already exists
        hash[g1->getID()%size].Insert(g1);
        num_of_obj++;
    }
    */
    void Insert(int ID){
        if(size<=num_of_obj){
            ReHash();
        }
        if(NULL==getGroup(ID)){
            hash[ID%size].Insert(new Group(ID));
            num_of_obj++;
            return;
        }
        throw Fail();
    }
    /*not needed
    void Delete(Group g1){
        HTList target_list=hash[g1.getID()%size];

    }
    */
    void ReHash(){
        HTList *newHash = new HTList[3*size];
        int oldsize=size;
        size*=3;
        HashNode *iterator, *next;
        for (int i = 0; i < oldsize; ++i) {
            iterator=hash[i].head;
            while(iterator!=NULL){
                next=iterator->next;
                newHash[iterator->Gteam->getID()%size].Insert(iterator);
                iterator=next;
            }
        }
        delete [] hash;
        hash=newHash;
    }

};


#endif //WET2_HASHTABLE_H
