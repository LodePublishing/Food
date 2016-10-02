#ifndef _FOREST_HPP
#define _FOREST_HPP

#include "food.hpp"

#define MAX_FOOD_TYPES 100

class Forest
{
	public:
		Forest();
		~Forest();
		void addFood(const Food& food, int amount);		
		const Food& gatherRandomFood();
		void reset();
	private:
		int foodTypeCount;
		int foodAmount[MAX_FOOD_TYPES];
		Food foodType[MAX_FOOD_TYPES];
};

#endif
