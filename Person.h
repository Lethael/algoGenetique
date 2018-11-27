/**
By Lethael
*/

#ifndef PERSON_H
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#define PERSON_H

using namespace std;
class Person
{
    public:
        Person();
        Person(Person const & person);
        ~Person();

        Person& operator =(Person const &p);
        friend ostream& operator<<( ostream &flux, Person const& person )
        {
            cout <<"Sequence : " << person.chromosome << endl;
            cout <<"Fitness : " << person.fitness<< endl;
            cout <<"Score : " << person.score << endl;
            return flux;
        }

        void setSequence(string seq);
        string getSequence();
        int getScore();
        double getFitness(){return fitness;};

        void Init(string toFind);
        void Mutate();
        void Score(string toFind);
        void CalculFitness(double totalScore){
            double rate = 2.0;
                fitness = (double)score / totalScore * 100 * rate;
        };

    protected:
        string chromosome;
        int score;
        double fitness;
};

#endif // PERSON_H
