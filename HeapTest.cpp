//
// Created by Fady on 1/8/2018.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Exceptions.h"
#include "Heap.h"
#include "Group.h"
#include "Gladiator.h"

using namespace std;

int main() {
    int num_of_groups = 5;
    Group* G1 = new Group(1);
    Group* G2 = new Group(2);
    Group* G3 = new Group(3);
    Group* G4 = new Group(4);
    Group* G5 = new Group(5);

    Group* arr[5];
    arr[0] = G5;
    arr[1] = G3;
    arr[2] = G2;
    arr[3] = G4;
    arr[4] = G1;

    Heap test_heap(5 ,arr);
    cout << "1 == " << test_heap.FindMin() << "?" << endl;
    test_heap.DelMin();
    cout << "2 == " << test_heap.FindMin() << "?" << endl;
    test_heap.DelIndex(1);
    cout << "-1 == " << G3->GetHeapIndex() << "?" << endl;

    Group** arr2 = test_heap.getArr();
    for (int i = 0; i < 3; ++i) {
        cout << arr2[i]->getID() << ", ";
    }
    cout << endl;
    test_heap.Insert(G3);
    cout << "2 == " << test_heap.FindMin() << "?" << endl;
    test_heap.Insert(G1);
    cout << "1 == " << test_heap.FindMin() << "?" << endl;


    return 0;
}
