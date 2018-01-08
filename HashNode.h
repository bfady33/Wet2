//
// Created by Aviv on 08/01/2018.
//

#ifndef WET2_HASHNODE_H
#define WET2_HASHNODE_H

#include "Group.h"

class HashNode {
public:
    Group *Gteam;
    HashNode *next;
    HashNode(Group *g1){
        Gteam=g1;
    }
};


#endif //WET2_HASHNODE_H
