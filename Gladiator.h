//
// Created by Fady on 1/8/2018.
//

#ifndef WET2_GLADIATOR_H
#define WET2_GLADIATOR_H
#include "Exceptions.h"

class Trainer;

class Gladiator{
public:

    //returns the ID of the Gladiator
    int getID() const;

    //returns the level of the Gladiator
    int getScore() const;

    //insert operator
    Gladiator& operator=(const Gladiator& G);

    //copy C'tor
    Gladiator(const Gladiator &G);


    Gladiator(int ID , int Score);


    //default C'tor
    Gladiator();

    //destructor
    ~Gladiator();                                              //???

    //compare functions for Gladiator
    bool operator<(const Gladiator &b) const;
    bool operator>(const Gladiator &b) const;

    bool operator<=(const Gladiator &b) const;

    bool operator>=(const Gladiator &b) const;

    bool operator==(const Gladiator &b) const;

private:
    int ID;
    int score;
};



#endif //WET2_GLADIATOR_H
