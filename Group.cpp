//
// Created by Fady on 1/7/2018.
//

#include "Group.h"

Group::Group(int ID){
    this->ID = ID;
    this->heap_index = -1;
    this->gladiators = new SplayTree<Gladiator>();
}

Group::~Group(){
    delete(gladiators);
}

void Group::SetHeapIndex(int index){
    this->heap_index = index;
}

int Group::GetHeapIndex(){
    return this->heap_index;
}

int Group::getID(){
    return this->ID;
}

void Group::InsertGladiator(int g_score , int g_ID){
    if(g_ID < 0 || g_score < 0)
        throw Invalid_Input();
    Gladiator g(g_ID , g_score);
    bool answer = this->gladiators->find(g);

    if(answer == true)
        throw Fail();

    this->gladiators->insert(g , g_score);
}

int Group::GetMaxKScores(int k){
    return this->gladiators->GetBestK(k);
}

