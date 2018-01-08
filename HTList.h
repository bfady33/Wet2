//
// Created by Fady on 1/7/2018.
//

#ifndef WET2_HTLIST_H
#define WET2_HTLIST_H

#include "HashNode.h"

class HTList {
public:
    HashNode *head;
    HTList(){
        head=NULL;
    }

    void Insert(Group *g1){
        HashNode *toadd=new HashNode(g1);
        toadd->next=head;
        head=toadd;
    }

    void Insert(HashNode *n1){
        n1->next=head;
        head=n1;
    }

    Group *GetHead(){
        return head->Gteam;
    }
};


#endif //WET2_HTLIST_H
