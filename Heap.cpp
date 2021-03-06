//
// Created by Fady on 1/7/2018.
//

#include "Heap.h"

void swap(Group** arr , int index , int min_index){
    Group* temp;

    temp = arr[index];
    arr[index]->SetHeapIndex(min_index);
    arr[min_index]->SetHeapIndex(index);
    arr[index] = arr[min_index];
    arr[min_index] = temp;
}

void Heap::decreaseArr(){
    capacity = capacity/2;
    Group** new_arr = new Group* [capacity];
    for(int i= 0 ; i < size ; i++){
        new_arr[i] = arr[i];
    }
    delete[](arr);
    arr = new_arr;
}

void Heap::incraseArr(){
    capacity = capacity*2;
    Group** new_arr = new Group* [capacity];
    for(int i = 0 ; i < size ;i++){
        new_arr[i] = arr[i];
    }
    delete[](arr);
    arr = new_arr;
}

void Heap::siftUp(int index) {
    if(index <= 0)
        return;

    if(arr[(index-1) / 2]->getID() > arr[index]->getID()){
        swap(arr , index , (index-1) / 2);
        siftUp((index-1) / 2);
    }
}
/*
Group** Heap::getArr() {
    return arr;
}*/

void Heap::siftDown(int index){
    if(index > size/2-1)
        return;

    int min_index;

    if(2*index+1 >= size){
        return;
    }
    if(2*index+2 >= size){
        min_index = 2*index+1;
    }
    else if(arr[2*index+1]->getID() < arr[2*index+2]->getID()) {
        min_index = 2*index + 1;
    }
    else{
        min_index = 2*index + 2;
    }

    if(arr[index]->getID() > arr[min_index]->getID()) {
        swap(arr, index, min_index);
        siftDown(min_index);
    }
}

/*
     * heap creats a heap with capacity 2n and size of n of the n pointer that are sent to it
     * trainingGroupsPointers is an array on n pointers
    */
Heap::Heap(int num_of_groups , Group** trainingGroupsPointers){
    size = num_of_groups;
    capacity = 2*num_of_groups;
    arr = new Group*[capacity];

    for(int i = num_of_groups-1 ; i>= 0 ; i--){
        arr[i] = trainingGroupsPointers[i];
        arr[i]->SetHeapIndex(i);
    }

    for (int j = (num_of_groups/2-1); j >= 0 ; j--){
        siftDown(j);
    }
}

Heap::~Heap() {
    delete[](arr);
}

void Heap::Insert(Group* pointer){
    size++;

    arr[size-1] = pointer;
    arr[size-1]->SetHeapIndex(size-1);
    siftUp(size-1);

    if(size == capacity){
        incraseArr();
    }
}

int Heap::FindMin(){
    return arr[0]->getID();
}

void Heap::DelMin() {
    if(size-1 <= capacity/4){
        decreaseArr();
    }
    arr[0]->SetHeapIndex(-1);
    arr[size-1]->SetHeapIndex(0);
    arr[0] = arr[size -1];
    size--;
    siftDown(0);
}

void Heap::DelIndex(int index){
    //create a group G with id 0
    arr[index]->SetHeapIndex(-1);
    Group* g = new Group(-1);
    g->SetHeapIndex(index);
    arr[index] = g;
    siftUp(index);
    DelMin();
    delete(g);
}