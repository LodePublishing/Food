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

bool Person::evaluateFood(const Food& food) const
{
	return foodEvaluation.getBehavior(food.getId(), getStatus());
}

bool Person::evaluatePerson(const Person& person) const
{
	return personEvaluation.getBehavior(person.getId(), getStatus());
}

void Person::consumeFood(const Food& food)
{
	
	if(food.isPoisonous())
	{
		energy -= POISONOUS_FOOD_ENERGY_COST;
		foodEvaluation.updateEvaluation(food.getId(), false);
	}
	else 
	{
		energy += GOOD_FOOD_ENERGY_GAIN;
		foodEvaluation.updateEvaluation(food.getId(), true);
	}	
}

void Person::processFood(const Food& food)
{
	if(evaluateFood(food))
		consumeFood(food);
}

void Person::meet(Person& other_person)
{
	bool my_action = evaluatePerson(other_person);
	bool other_action = other_person.evaluatePerson(*this);

// exchange evaluations
	if(my_action)
	{
//		energy -= EXCHANGE_ENERGY_COST;
		other_person.personEvaluation.exchangeEvaluation(personEvaluation);
		other_person.foodEvaluation.exchangeEvaluation(foodEvaluation);
	}
	
	if(other_action)
	{
//		other_person.energy -= EXCHANGE_ENERGY_COST;
		personEvaluation.exchangeEvaluation(other_person.personEvaluation);
		foodEvaluation.exchangeEvaluation(other_person.foodEvaluation);		
	}

// update evaluation of person we have just met
	personEvaluation.updateEvaluation(other_person.getId(), other_action);
	other_person.personEvaluation.updateEvaluation(getId(), my_action);	

}

void Person::reset()
{
	foodEvaluation.reset();
	personEvaluation.reset();
	
	energy = 0;
}

void Person::generateChild(Person* child)
{
	foodEvaluation.generateChild(child->getFoodEvaluation());
	personEvaluation.generateChild(child->getPersonEvaluation());
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

int* Person::getBehavior() const
{
	return &personEvaluation.behavior[0];
}

Evaluation* Person::getPersonEvaluation()
{
	return &personEvaluation;
}

int Person::cooperate = 0; // statistical
int Person::globalId = 0;
int Person::EXCHANGE_ENERGY_COST = 0;
int Person::POISONOUS_FOOD_ENERGY_COST = 0;
int Person::GOOD_FOOD_ENERGY_GAIN = 0;
