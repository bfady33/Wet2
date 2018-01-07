//
// Created by Fady on 1/7/2018.
//

#ifndef WET2_HEAP_H
#define WET2_HEAP_H

#include "Group.h"
#include "Exceptions.h"

class Heap {
private:
    Group **arr;
    int size;
    int capacity;

    /*
     * we want to sift down in makeheap from [n/2] to 1
     */
    void siftDown(int index);

    void siftUp(int index);

    void incraseArr();

    void decreaseArr();

public:

    Heap(int num_of_groups, group **trainingGroupsPointers);

    ~Heap();

    void Insert(Group *pointer);

    int FindMin();

    void DelMin();


    void DelIndex(int index);

};



#endif //WET2_HEAP_H
