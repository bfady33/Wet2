//
// Created by Fady on 1/8/2018.
//

#include "Colosseum.h"


Colosseum::Colosseum(int n , int* trainingGroupsIDs){

    colo_HT= new HashTable(n);
    Group** GArr = new Group*[n];
    for (int i = 0; i < n; ++i) {
        if (trainingGroupsIDs[i] < 0) {
            delete(colo_HT);
            delete[](GArr);
            throw Fail();
        }
        colo_HT->Insert(trainingGroupsIDs[i]);
        GArr[i] = colo_HT->getGroup(trainingGroupsIDs[i]);
    }
    colo_heap= new Heap(n , GArr);
    delete[](GArr);
    Gladiators = new SplayTree<int>();
}

Colosseum::~Colosseum() {
    delete(colo_heap);
    delete(colo_HT);
    delete(Gladiators);
}

void Colosseum::addTrainingGroup (int trainingGroupID){
    if(trainingGroupID < 0)
        throw Invalid_Input();
    colo_HT->Insert(trainingGroupID);
    colo_heap->Insert(colo_HT->getGroup(trainingGroupID));
}

void Colosseum::addGladiator(int gladiatorID, int score, int trainingGroup){
    if(gladiatorID < 0 || score < 0 || trainingGroup < 0)
        throw Invalid_Input();

    Group* pointer = colo_HT->getGroup(trainingGroup);
    if (pointer == NULL)
        throw Fail();

    if(Gladiators->find(gladiatorID) == true){
        throw Fail();
    }
    Gladiators->insert(gladiatorID , 0);

    pointer->InsertGladiator(score , gladiatorID);
}

void Colosseum::trainingGroupFight (int trainingGroup1, int trainingGroup2, int k1, int k2){
    if(k1 <= 0 || k2<= 0 || trainingGroup1 <0 || trainingGroup2 < 0)
        throw Invalid_Input();

    if(trainingGroup1 == trainingGroup2)
        throw Fail();

    Group* pointer1 = colo_HT->getGroup(trainingGroup1);
    Group* pointer2 = colo_HT->getGroup(trainingGroup2);
    if (pointer1 == NULL || pointer2 == NULL)
        throw Fail();

    if(pointer1->GetHeapIndex() == -1 || pointer2->GetHeapIndex() == -1)
        throw Fail();

    int max1 = pointer1->GetMaxKScores(k1);
    int max2 = pointer2->GetMaxKScores(k2);
    if(max1 == -1 || max2 == -1)
        throw Fail();

    if(max1 == max2) {
        if(pointer1->getID() < pointer2->getID())
            colo_heap->DelIndex(pointer2->GetHeapIndex());
        else
            colo_heap->DelIndex(pointer1->GetHeapIndex());
    }
    else if(max1 > max2)
        colo_heap->DelIndex(pointer2->GetHeapIndex());
    else
        colo_heap->DelIndex(pointer1->GetHeapIndex());
}

void Colosseum::getMinTrainingGroup (int* trainingGroup){
    if(trainingGroup == NULL)
        throw Invalid_Input();

    *trainingGroup = colo_heap->FindMin();
}


