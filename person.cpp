#include "person.hpp"

Person::Person():
	energy(0),
	id(++globalId)
{}

Person::~Person()
{}

int Person::getEnergy() const
{
	return energy;
}

int Person::getId() const
{
	return id;
}

int Person::getStatus() const
{
	return 0;
	if(energy >= 0)
		return 1;
	else return 0;
}

int Person::evaluateFood(const Food& food) const
{
	return foodEvaluation.getBehavior(food.getId());
}

int Person::evaluatePerson(const Person& person) const
{
	return personEvaluation.getBehavior(person.getId());
}

void Person::consumeFood(const Food& food)
{
	
	if(food.isPoisonous())
	{
		energy -= POISONOUS_FOOD_ENERGY_COST;
		foodEvaluation.updateEvaluation(food.getId(), -100);
	}
	else 
	{
		energy += GOOD_FOOD_ENERGY_GAIN;
		foodEvaluation.updateEvaluation(food.getId(), 100);
	}	
}

int Person::generateParent(int selection_size)
{
	int t = ((rand()%selection_size) + (rand()%selection_size));
	if(t < selection_size)
		t = selection_size - t;
	else t -= selection_size;
	return t;
}




void Person::processFood(const Food& food)
{
	if((rand()%200) - 100 >= evaluateFood(food))
		consumeFood(food);
}

void Person::meet(Person& other_person)
{
	bool my_action = ((rand()%200) - 100 >= evaluatePerson(other_person));
	bool other_action = ((rand()%200) - 100 >= other_person.evaluatePerson(*this));	
	int w1 = 0;
	int w2 = 0;
	

// exchange evaluations
	if(my_action)
	{
		w2 = 100;
//		energy -= EXCHANGE_ENERGY_COST;
		other_person.personEvaluation.exchangeEvaluation(personEvaluation);
		other_person.foodEvaluation.exchangeEvaluation(foodEvaluation);
	} else w2 = -100;
	
	if(other_action)
	{
		w1 = 100;
//		other_person.energy -= EXCHANGE_ENERGY_COST;
		personEvaluation.exchangeEvaluation(other_person.personEvaluation);
		foodEvaluation.exchangeEvaluation(other_person.foodEvaluation);		
	} else w1 = -100;

// update evaluation of person we have just met
	personEvaluation.updateEvaluation(other_person.getId(), w1);
	other_person.personEvaluation.updateEvaluation(getId(), w2);	

}

void Person::reset()
{
	foodEvaluation.reset();
	personEvaluation.reset();
	
	energy = 0;
}

void Person::generateChild(Person* partner, Person* child)
{
	foodEvaluation.generateChild(partner->getFoodEvaluation(), child->getFoodEvaluation());
	personEvaluation.generateChild(partner->getPersonEvaluation(), child->getPersonEvaluation());
}

void Person::mutate()
{
	foodEvaluation.mutate();
	personEvaluation.mutate();
}

Evaluation* Person::getFoodEvaluation()
{
	return &foodEvaluation;
}

/*int Person::getBehavior(int id) const
{
	return personEvaluation.getBehavior[0];
}*/

Evaluation* Person::getPersonEvaluation()
{
	return &personEvaluation;
}

int Person::cooperate = 0; // statistical
int Person::globalId = 0;
int Person::EXCHANGE_ENERGY_COST = 0;
int Person::POISONOUS_FOOD_ENERGY_COST = 0;
int Person::GOOD_FOOD_ENERGY_GAIN = 0;
