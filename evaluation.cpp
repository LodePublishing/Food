#include "evaluation.hpp"

Evaluation::Evaluation()
{
	initZero();
}

Evaluation::~Evaluation()
{
}

void Evaluation::reset()
{
	behavior.clear();
}

void Evaluation::initZero()
{
		behaviorAdaption = 10;
		exchangeBehaviorAdaption = 10;
		firstBehavior = 10;
		firstBehaviorAdaption = 10;
}

void Evaluation::initThisForThat()
{
}

void Evaluation::generateChild(Evaluation* partner, Evaluation* child) const
{
	child->behaviorAdaption = (partner->behaviorAdaption + behaviorAdaption) / 2;
	child->exchangeBehaviorAdaption = (partner->exchangeBehaviorAdaption + exchangeBehaviorAdaption) / 2;
	child->firstBehavior = (partner->firstBehavior + firstBehavior) / 2;
	child->firstBehaviorAdaption = (partner->firstBehaviorAdaption + firstBehaviorAdaption) / 2;
}

void my_mutate(int& value)
{
	if(rand()%2 == 0)
		return;
	int z = (rand()%100) + (rand()%100) - value;
	value = (value + z)/2;
}

void Evaluation::mutate()
{
	my_mutate(behaviorAdaption);
	my_mutate(exchangeBehaviorAdaption);
	my_mutate(firstBehavior);
	my_mutate(firstBehaviorAdaption);	
}

int adapt(int value1, int adapt_value, int value2)
{
	return (value1 * (100 - adapt_value) + value2 * adapt_value) / 100;
}

// positive oder negative Erfahrung?
void Evaluation::updateEvaluation(int id, int experience)
{
	std::map<int, int>::const_iterator i = behavior.find(id);
	if(i == behavior.end())
	{
		behavior[id] = 0;
		firstBehavior = adapt(firstBehavior, firstBehaviorAdaption, experience);
	}
	behavior[id] = adapt(behavior[id], behaviorAdaption, experience);
}

int Evaluation::getBehavior(const int id) const
{
	std::map<int, int>::const_iterator i = behavior.find(id);
	if(i == behavior.end())
		return firstBehavior;
	else return i->second;
}

void Evaluation::exchangeEvaluation(const Evaluation& other_evaluation)
{
	for(std::map<int, int>::const_iterator i = other_evaluation.behavior.begin(); i != other_evaluation.behavior.end(); i++)
	{
		int my_behavior;
		if(behavior.find(i->first) == behavior.end())
			my_behavior = 0;
		else my_behavior = behavior[i->first];

		int other_behavior = i->second;
		
		int new_behavior = adapt(my_behavior, exchangeBehaviorAdaption, other_behavior);

		if(new_behavior != my_behavior)
			behavior[i->first] = new_behavior;
	}
}
