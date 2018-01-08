//
// Created by Fady on 1/8/2018.
//

#include "Gladiator.h"


using namespace DataStructure;

int Gladiator::getID() const{
    return this->ID;
}

int Gladiator::getScore() const{
    return this->score;
}

Gladiator& Gladiator::operator=(const Gladiator& G){
    if(this == &G)
        return *this;

    this->ID = G.ID;
    this->score = G.score;

    return *this;
}

Gladiator::Gladiator(const Gladiator& G){
    this->ID = G.ID;
    this->score = G.score;
}


Gladiator::Gladiator(int ID , int Score){
    this->ID = ID;
    this->score = Score;
}


Gladiator::Gladiator(){
    this->score = 0;
    this->ID =0;
};

Gladiator::~Gladiator(){}


bool Gladiator::operator<(const Gladiator &b) const{
    if(this->score == b.score){
        return this->ID < b.ID;
    }
    return this->score < b.score;
}

bool Gladiator::operator>(const Gladiator &b) const{
    if(this->score == b.score){
        return this->ID > b.ID;
    }
    return this->score > b.score;
}

bool Gladiator::operator==(const Gladiator &b) const{
    return this->ID == b.ID;
}

bool Gladiator::operator<=(const Gladiator &b) const{
    return this->score <= b.score;
}

bool Gladiator::operator>=(const Gladiator &b) const{
    return this->score >= b.score;
}

