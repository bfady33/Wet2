//
// Created by Fady on 1/8/2018.
//

#ifndef WET2_COLOSSEUM_H
#define WET2_COLOSSEUM_H

#include "Exceptions.h"
#include "Group.h"
#include "Heap.h"
#include "HashTable.h"
#include "Gladiator.h"

using namespace DataStructure;

class Colosseum {
// a list of trainers
public:
    //C'tor for the DS
    Colosseum(int n , int* trainingGroupsIDs);

    //Destructor for the DS
    ~Colosseum();

    //add trainerGroup to the DS
    void addTrainingGroup (int trainingGroupID);

    //adds Gladiator to the DS
    void addGladiator(int gladiatorID, int score, int trainingGroup);

    void trainingGroupFight (int trainingGroup1, int trainingGroup2, int k1, int k2);

    void getMinTrainingGroup (int* trainingGroup);

private:
    Heap* colo_heap;
    HashTable* colo_HT;
};


#endif //WET2_COLOSSEUM_H
