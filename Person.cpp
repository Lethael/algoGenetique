/**
By Lethael
*/

#include "Person.h"

Person::Person()
{
    chromosome = "";
    score = 0;
    fitness = 0.0;
}

Person::Person(Person const &p){
    chromosome = p.chromosome;
    score = p.score;
    fitness = p.fitness;
}

Person::~Person()
{
}

Person& Person::operator = (Person const &p){
    chromosome = p.chromosome;
    fitness = p.fitness;
    score = p.score;
    return *this;
}


void Person::setSequence(string seq){
    chromosome = seq;
}

string Person::getSequence(){
    return chromosome;
}

int Person::getScore(){
    return score;
}


void Person::Init(string toFind){
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.!?\', ";
    int length = toFind.length();

    for(int i = 0; i < length; i++){
        int randomLetter = rand()%letters.length();
        chromosome += letters[randomLetter];
    }
    for(unsigned int i = 0; i < toFind.length(); i++){
        if(chromosome[i] == toFind[i])
            score += 1.0;
    }
}

void Person::Score(string toFind){
    score = 0;
    for(int i = 0; i < toFind.length(); i++){
        if(chromosome[i] == toFind[i])
            score += 1.0;
    }
}

void Person::Mutate(){
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.!?\', ";
    int rndLet = rand()%letters.length();
    int rndChrom = rand()%chromosome.length();
    chromosome[rndChrom] = letters[rndLet];
}
