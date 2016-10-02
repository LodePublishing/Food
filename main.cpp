#include <stdlib.h>
#include <stdio.h>

#include "forest.hpp"
#include "food.hpp"
#include "person.hpp"

#define RUNS 100
#define POP_SIZE 10
#define PLANTS 2
#define SELECTION_SIZE (POP_SIZE/2)

int main()
{
	srand(time(NULL));

	Person::EXCHANGE_ENERGY_COST = 0;
	Person::POISONOUS_FOOD_ENERGY_COST = 1;
	Person::GOOD_FOOD_ENERGY_GAIN = 10;
	
	Food my_food[PLANTS];
	for(int i = 0; i < PLANTS; i++)
		my_food[i].setPoisonous((i%2) == 0);
	
	Forest forest;

	bool hs[POP_SIZE];

	Person* person[POP_SIZE];
	for(int i = 0; i < POP_SIZE; i++)
		person[i] = new Person();
	
	while(true)
	{
		for(int	i = 0; i < PLANTS; i++)
			forest.addFood(my_food[i], 10000);
		
		for(int k = 0; k < RUNS; k++)
		{
			for(int i = 0; i < POP_SIZE; i++)
				person[i]->processFood(forest.gatherRandomFood());

			for(int i = 0; i < POP_SIZE; i++)
				hs[i] = false;
			
			for(int i = 0; i < POP_SIZE; i++)
			{
				int j = rand()%POP_SIZE;
				while(hs[j])
					j = rand()%POP_SIZE;
				person[i]->meet(*person[j]);
				hs[j] = true;
			}
		}
// sort
		for(int l = 0; l < POP_SIZE-1; l++)
			for(int m = 0; m < POP_SIZE-1-l; m++)
				if(person[m]->getEnergy() < person[m+1]->getEnergy())
				{
					Person* t = person[m];
					person[m] = person[m+1];
					person[m+1] = t;
				}

		int average = 0;
		for(int i = 0; i < POP_SIZE; i++)
			average += person[i]->getEnergy();	
		printf("Average: %4i [best: %4i] [first: %i]\n", average / POP_SIZE, person[0]->getEnergy(), person[0]->getPersonEvaluation()->behaviorAdaption);
/*		for(int j = 0; j < Evaluation::STATUS_SIZE; j++)
		{
			printf(" ");
//			for(int i = 0; i < Evaluation::EVALUATION_SIZE; i++)
//				printf("%i", person[0]->behavior[i + j*Evaluation::EVALUATION_SIZE]>SELECTION_SIZE?1:0);
			printf(" ");
		}
		printf("}\n");*/
// reset for the new run
		for(int i = 0; i < POP_SIZE; i++)
			person[i]->reset();
		forest.reset();
		
		int i = 0;
		
		
		int parent1 = Person::generateParent(SELECTION_SIZE);
		int parent2 = Person::generateParent(SELECTION_SIZE);
		
		while((i < SELECTION_SIZE) && (person[POP_SIZE - i - 1]->getEnergy() <= 0))
		{
			person[parent1]->generateChild(person[parent2], person[POP_SIZE - i - 1]);
			i++;
		}
			
		for(int i = 0; i < POP_SIZE; i++)
			person[i]->mutate();

	}
   	for(int i = 0; i < POP_SIZE; i++)
   		delete person[i];
    
    return EXIT_SUCCESS;
}


// handeln - Beduerfnisse, 'Rucksack', gezieltes Sammeln?, Preis
// Beduerfnis, Angebot
