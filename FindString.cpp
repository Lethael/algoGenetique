/**
By Lethael
11/22/2018

Algorithme génétique permettant la recherche d'une chaine de caractères données
à partir d'une population ayant des chromosomes (string) aléatoire, et évoluant et
mutant à chaque génération.
*/

#include <Person.h>
#include <vector>
#include <iterator>
#include <algorithm>

bool greaterThan(Person p, Person p1);
void nextGeneration(vector<Person> &pop, string toFind);
vector<Person> MattingPool(vector<Person> pop);

int main()
{
    srand(time(NULL));
    string toFind = "Si belle, si froide, comme un pale matin de printemps frissonnant encore d'un hiver glacial";
    vector<Person> population(200);

    for(vector<Person>::iterator it = population.begin(); it != population.end(); it++){
        it->Init(toFind);
    }
    for(int i = 0; i < 20000; i++){
      sort(population.begin(), population.end(), greaterThan);
      nextGeneration(population, toFind);
      sort(population.begin(), population.end(), greaterThan);
      if(i % 100 == 0){
        cout << population[0].getSequence() << endl;
        cout << "Score : "<< population[0].getScore() << endl;
      }
      for(vector<Person>::iterator it = population.begin(); it != population.end(); it++){
        if(it->getScore() == toFind.length()){
            cout << "La solution a ete trouve au tour : " << i << endl;
            cout << it->getSequence() << endl;
            return 0;
        }
      }
    }

    return 0;
}

bool greaterThan(Person p, Person p1){
    return p.getScore() > p1.getScore();
}

/** Deux enfants par parents **/
void nextGeneration(vector<Person> &pop, string toFind){
    vector<Person> matting;
    matting = MattingPool(pop);
    for(int i = 0; i < pop.size(); i++){
        int rndMutate = rand()%100;
        int rndFather;
        int rndMother;
        do{
              rndFather =  rand()%matting.size();
              rndMother = rand()%matting.size();
        }while(rndFather == rndMother);

        int scale = rand()%pop[i].getSequence().length();
        if(i > pop.size()){
            string newS = matting[rndFather].getSequence().substr(0, scale)
            + matting[rndMother].getSequence().substr(scale, pop[i].getSequence().length());
            pop[i].setSequence(newS);
            string newS1 = matting[rndMother].getSequence().substr(0, scale)
            + matting[rndFather].getSequence().substr(scale, pop[i].getSequence().length());
            pop[i+1].setSequence(newS1);
            if(rndMutate < 10)
                pop[i].Mutate();
        }else{
           string newS = matting[rndFather].getSequence().substr(0, scale)
            + matting[rndMother].getSequence().substr(scale, pop[i].getSequence().length());
            pop[i].setSequence(newS);
            if(rndMutate < 30)
                pop[i].Mutate();
        }


        i++;
    }
    for(int i = 0; i < pop.size(); i++){
        for(int j = 0; j < pop[i].getSequence().length(); j++){
            pop[i].Score(toFind);
        }
    }
}

vector<Person> MattingPool(vector<Person> pop){
    vector<Person>mattingPool;
    double scoreTotal = 0.0;

    for(int i = 0; i < pop.size(); i ++)
    scoreTotal += pop[i].getScore();

    for(int i = 0; i < pop.size(); i++){
        pop[i].CalculFitness(scoreTotal);
        if(pop[i].getFitness() > 0){
            for(int j = 1; j < pop[i].getFitness(); j++){
                mattingPool.push_back(pop[i]);
            }
        }
    }
    return mattingPool;
}
