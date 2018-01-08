//
// Created by Fady on 1/7/2018.
//

#ifndef WET2_GROUP_H
#define WET2_GROUP_H

#include "Gladiator.h"
#include "SplayTree.h"

#include "Exceptions.h"

using namespace DataStructure;



class Group {
private:
    int heap_index;
    int ID;
    SplayTree <Gladiator>* gladiators;

public:

    /*
     * we get correct ID
     */
    Group(int ID);

    /*
     * default
     */
    ~Group();

    void SetHeapIndex(int index);

    int GetHeapIndex();

    int getID();

    void InsertGladiator(int g_score , int g_ID);

    int GetMaxKScores(int k);
};


#endif //WET2_GROUP_H
