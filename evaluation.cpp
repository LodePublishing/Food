#include "evaluation.hpp"

Evaluation::Evaluation()
{
	behavior = new int[EVALUATION_SIZE * STATUS_SIZE];
	evaluationExperience = new int[EVALUATION_SIZE * ACTION_SIZE];
	evaluationExchange = new int[EVALUATION_SIZE * EVALUATION_SIZE];
	initThisForThat();
	initZero();
}

Evaluation::~Evaluation()
{
	delete behavior;
	delete evaluationExperience;
	delete evaluationExchange;
}

void Evaluation::reset()
{
	evaluation.clear();
}

void Evaluation::initZero()
{

	for(int i = 0; i < STATUS_SIZE*EVALUATION_SIZE; i++)
		behavior[i] = 0;

/*	for(int i = 0; i < ACTION_SIZE*EVALUATION_SIZE; i++)
		evaluationExperience[i] = 0;

	for(int i = 0; i < EVALUATION_SIZE; i++)
		for(int j = 0; j < EVALUATION_SIZE; j++)
			evaluationExchange[i + j * EVALUATION_SIZE] = 0;*/
}

void Evaluation::initThisForThat()
{
	// Cooperate in first step if energy is >= 0 or < 0
	behavior[0] = 1;
	behavior[EVALUATION_SIZE] = 1;
	
	// Don't cooperate with evaluation == 1
	behavior[1] = 0;
	behavior[1 + EVALUATION_SIZE] = 0;
	
	// Cooperate in other cases
	for(int i = 2; i < EVALUATION_SIZE; i++)
	{
		behavior[i] = 1;
		behavior[i + EVALUATION_SIZE] = 1;
	}
	
	// Did not cooperate? => Status 1
	for(int i = 0; i < EVALUATION_SIZE; i++)
		evaluationExperience[i] = 1;
	// Did cooperate? => Status 2
	for(int i = 0; i < EVALUATION_SIZE; i++)
		evaluationExperience[i + EVALUATION_SIZE] = 2;
		
	// don't ignore other people
	for(int i = 0; i < EVALUATION_SIZE; i++)
		for(int j = 0; j < EVALUATION_SIZE; j++)
		{
			int e = i;
			if(e == 0)
				e = j;
			else if((j == 1) && (e > 1))
				e--;
			else if((j >= 2) && (e+1 < EVALUATION_SIZE))
				e++;
			evaluationExchange[i + j * EVALUATION_SIZE] = e;
		}
}

void Evaluation::generateChild(Evaluation* child) const
{
	for(int i = 0; i < STATUS_SIZE * EVALUATION_SIZE; i++)
		child->behavior[i] = behavior[i];
	
	for(int i = 0; i < ACTION_SIZE*EVALUATION_SIZE; i++)
		child->evaluationExperience[i] = evaluationExperience[i];
	
	for(int i = 0; i < EVALUATION_SIZE*EVALUATION_SIZE; i++)
		child->evaluationExchange[i] = evaluationExchange[i];
}

void Evaluation::mutate()
{
	for(int i = 0; i < STATUS_SIZE * EVALUATION_SIZE; i++)
		if(rand()%(STATUS_SIZE * EVALUATION_SIZE) == 0)
			behavior[i] = rand()%ACTION_SIZE;
	
//	for(int i = 0; i < ACTION_SIZE*EVALUATION_SIZE; i++)
//		if(rand()%(EVALUATION_SIZE) == 0)
//			evaluationExperience[i] = rand()%EVALUATION_SIZE;

//	for(int i = 0; i < EVALUATION_SIZE*EVALUATION_SIZE; i++)
//		if(rand()%(EVALUATION_SIZE*EVALUATION_SIZE) == 0)
//			evaluationExchange[i] = rand()%EVALUATION_SIZE;
}



// positive oder negative Erfahrung?
void Evaluation::updateEvaluation(int id, bool experience)
{
	int eval_number = getEvalNumber(id);
	if(experience)
		eval_number += EVALUATION_SIZE;
	evaluation[id] = evaluationExperience[eval_number];
}

int Evaluation::getEvalNumber(const int id) const
{
	std::map<int, int>::const_iterator i = evaluation.find(id);
	if(i != evaluation.end())
		return i->second;
	else return 0;
}

int Evaluation::getBehavior(const int id, const int status) const
{
	return behavior[getEvalNumber(id) + status * EVALUATION_SIZE];
}

int Evaluation::evaluationOfExchange(int my_evaluation, int other_evaluation) const
{
	return evaluationExchange[my_evaluation + other_evaluation * EVALUATION_SIZE];
}

void Evaluation::exchangeEvaluation(const Evaluation& other_evaluation)
{
	for(std::map<int, int>::const_iterator i = other_evaluation.evaluation.begin(); i != other_evaluation.evaluation.end(); i++)
	{
		int my_evaluation;
		if(evaluation.find(i->first) == evaluation.end())
			my_evaluation = 0;
		else my_evaluation = evaluation[i->first];

		int other_evaluation = i->second;
		
		int new_evaluation = evaluationOfExchange(my_evaluation, other_evaluation);

		if(new_evaluation != my_evaluation)
			evaluation[i->first] = new_evaluation;
	}
}

int Evaluation::EVALUATION_SIZE = 0;
int Evaluation::STATUS_SIZE = 0;
int Evaluation::ACTION_SIZE = 0;
