#include "food.hpp"

Food::Food()
{
	id = globalId;
	globalId++;
}

Food::~Food()
{}

void Food::setPoisonous(bool poisonous)
{
	this->poisonous = poisonous;
}

bool Food::isPoisonous() const
{
	return poisonous;
}

int Food::getId() const
{
	return id;
}

int Food::globalId = 0;
