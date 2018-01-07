//
// Created by Fady on 1/7/2018.
//

#include "Heap.h"

void swap(Group** arr , int index , int min_index){
    Group* temp;
    int temp_id;

    temp = arr[index];
    arr[index]->SetHeapIndex(min_index);
    arr[index] = arr[min_index];
    arr[min_index]->SetHeapIndex(index);
    arr[min_index] = arr[index];
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
    if(arr[(index-1) / 2]->getID() > arr[index]->getID()){
        swap(arr , index , (index-1) / 2);
        siftUp((index-1) / 2);
    }
}

void Heap::siftDown(int index){
    int min_index;

    if(arr[2*index+1]->getID() < arr[2*index+2]->getID()) {
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

    for(int i = n-1 ; i>= 0 ; i--){
        arr[i] = trainingGroupsPointers[i];
    }

    for (int j = (n/2-1); j >= 0 ; j++){
        siftDown(j);
    }
}

Heap::~Heap() {
    delete[](arr);
}

void Heap::Insert(Group* pointer){
    if(size+1 == capacity){
        incraseArr();
    }
    size++;

    arr[size-1] = pointer;
    arr[size-1]->SetHeapIndex(size-1);
    siftUp(size-1);
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
    swap(arr , 0 , size-1);
    size--;
    siftDown(0);
}

void Heap::DelIndex(int index){
    //create a group G with id 0
    arr[index]->SetHeapIndex(-1);
    Group g(-1);
    arr[index] = &g;
    siftUp(index);
    DelMin();
}