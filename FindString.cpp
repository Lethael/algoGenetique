/**
By Lethael
11/22/2018

Algorithme génétique permettant la recherche d'une chaine de caractères données
à partir d'une population ayant des chromosomes (string) aléatoire, et évoluant et
mutant à chaque génération.
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

class Person{
    public:
    string sequence;
    double fitness;
    int score;

    Person(){sequence = ""; fitness = 0; score = 0;}
    Person(Person const &per){sequence = per.sequence; fitness = per.fitness; score = per.score;}
    ~Person(){}

    bool operator >(Person const &ch1) const;
    bool operator <(Person const &ch1) const;
    Person& operator =(Person const &p);
    friend ostream& operator<<( ostream &flux, Person const& person )
    {
        cout << person.sequence << endl;
        cout << person.fitness<< endl;
        cout << person.score << endl;
        return flux;
    }

    void Init(int lengthSentence);
    void Score(string toFind);
    void Mutation();


};
//OPERATOR
Person& Person::operator = (Person const &p){
    sequence = p.sequence;
    fitness = p.fitness;
    score = p.score;
    return *this;
}
bool Person::operator >(Person const &ch1) const{
    return this->fitness > ch1.fitness;
}
bool Person::operator <(Person const &ch1) const{
    return this->score < ch1.score;
}

//METHODS
/**
Add random letter into sequence string
*/
void Person::Init(int lengthSentence){
    sequence = "";
    string alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.!?,;: ";
    for(int i = 0; i < lengthSentence; i++){
        sequence += alph[rand()%alph.length()];
    }
}

void Person::Score(string toFind){
    score = 0;
    for(unsigned int i = 0; i < toFind.length(); i++){
        if(sequence[i] == toFind[i])
            score += 1;
    }
}

void Person::Mutation(){
    string alph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.!?,;: ";
    int geneFromPerson = rand() % sequence.length();
    int geneRandom = rand() % alph.length();

    sequence[geneFromPerson] = alph[geneRandom];
}

//FUNCTIONS
void InitAndTestFitness(Person &ch, string toFind);
bool greaterThan(Person p, Person p1);

vector<Person> NexGeneration(vector<Person> oldGen, int toFind, string toFindstr);
vector<Person> MattingPool(vector<Person> oldGen);
int main()
{
    srand(time(NULL));
    string toFind = "Vous ne passerez pas !";
    double totalFitness = 0.0;
    vector<Person> population(100);
    vector<Person>::iterator it = population.begin();


    for(it;it != population.end(); ++it){
        InitAndTestFitness(*it, toFind);
    }

    sort(population.begin(), population.end(), greaterThan);

    for(int i = 0; i < 10000; i++){
        population = NexGeneration(population, toFind.length(), toFind);
        sort(population.begin(), population.end(), greaterThan);
        if(i % 100 == 0){
            cout << "Turn " << i  << " the best is : "<< endl;
            cout << population[0].sequence << "\n" << population[0].score << endl;
        }

        if(population[0].sequence == toFind){
            cout << "Au tour : " << i <<"\n" << population[0].sequence << "\n a ete trouve" << endl;
            cout << "Affichage des 10 premiers de la pop en fonction du score : \n";
            for(int i = 0; i < 10; i++)
                cout << population[i].sequence << "\n Score : " << population[i].score << endl;
            return 0;
        }
    }

    return 0;
}


void InitAndTestFitness(Person &ch, string toFind){
   //Initialisation des Personnes + Scoring;
        ch.Init(toFind.length());
        ch.Score(toFind);
}

bool greaterThan(Person p, Person p1){
    return p.score > p1.score;
}

    /** Insérer dans le vector x fois la même personne en fonction
    * De son % de fitness
    */
    /** augmente le nombre de proba pour les plus fort d'avoir des enfants
    *   totalFit = nb total de score de la génération
    *   p.fitness = p.score / totalFit * 100
    *
    *   Insertion de p.fitness * la personne dans un vector
    */
vector<Person> MattingPool(vector<Person> p){
    vector<Person> mattingPool;
    double totalFit = 0.0;

    for(int i = 0; i < p.size(); i++){
        totalFit += p[i].score;
    }
     for(int i = 0; i < p.size(); i++){
        p[i].fitness = p[i].score / totalFit * 100.0;
        for(int j = 1; j < p[i].fitness; j++){
            mattingPool.push_back(p[i]);
        }
     }
    return mattingPool;

}

/**
*   Génération suivante en récupérant les gênes de la
*   génération actuelle.
*   30% de chance de mutation d'un gène
*/
vector<Person> NexGeneration(vector<Person> oldGen, int toFind, string toFindstr){
    for(int i = 0; i < oldGen.size(); i++){
        oldGen[i].Score(toFindstr);
    }


     vector<Person> nextGen(oldGen.size());
     vector<Person> mattingPool = MattingPool(oldGen);
     for(int i = 0; i < nextGen.size()-1; i++){
        /**
        *   Random du père et de la mère ainsi que de la possible mutation
        */
        int scalepoint = rand()%toFind;
        int rndMutate = rand()% 100;
        int posPere = rand()%mattingPool.size();
        int posMere = rand()%mattingPool.size();
        /**
        *   Deux enfants par couples
        */
        nextGen[i].sequence = mattingPool[posPere].sequence.substr(0, scalepoint) + mattingPool[posMere].sequence.substr(scalepoint, mattingPool[posMere].sequence.length());
        if(rndMutate <= 30)
            nextGen[i].Mutation();
        nextGen[i+1].sequence = mattingPool[posMere].sequence.substr(0, scalepoint) + mattingPool[posPere].sequence.substr(scalepoint, mattingPool[posPere].sequence.length());
        nextGen[i].Score(toFindstr);
        nextGen[i+1].Score(toFindstr);
        i++;
     }
     return nextGen;
}
