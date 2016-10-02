#include "forest.hpp"
#include <stdlib.h>

Forest::Forest()
{
	foodTypeCount = 0;
	for(int i = 0; i < MAX_FOOD_TYPES; i++)
		foodAmount[i] = 0;	
}

Forest::~Forest()
{}

void Forest::addFood(const Food& food, int amount)
{
	if(foodTypeCount >= MAX_FOOD_TYPES)
		return;
		
	foodAmount[foodTypeCount] = amount;
	foodType[foodTypeCount] = food;
	foodTypeCount++;
}

void Forest::reset()
{
	foodTypeCount = 0;
}

const Food& Forest::gatherRandomFood()
{
	int food_number = rand()%foodTypeCount;
	Food& food_type = foodType[food_number];
	foodAmount[food_number]--;
	if(!foodAmount[food_number])
	{
		for(int i = food_number; i < foodTypeCount-1; i++)
		{
			foodAmount[i] = foodAmount[i+1];
			foodType[i] = foodType[i+1];
		}
		foodTypeCount--;
	}
	return food_type;
}
