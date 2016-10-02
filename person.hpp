#ifndef _PERSON_HPP
#define _PERSON_HPP

#include <map>
#include "food.hpp"
#include "evaluation.hpp"

class Person
{
	public:
		Person();
		~Person();

		void processFood(const Food& food);
		int getEnergy() const;

		void reset();

		void meet(Person& other_person);
		void generateChild(Person* child);
		void mutate();
		
		int getId() const;

		static int EXCHANGE_ENERGY_COST;
		static int POISONOUS_FOOD_ENERGY_COST;
		static int GOOD_FOOD_ENERGY_GAIN;
		
		Evaluation* getFoodEvaluation();
		Evaluation* getPersonEvaluation();

		int* getBehavior() const;
		
	private:
		void consumeFood(const Food& food);

		bool evaluateFood(const Food& food) const;
		bool evaluatePerson(const Person& person) const;
		
		int getStatus() const;
		
		int energy;
		int id;
		
		Evaluation foodEvaluation;
		Evaluation personEvaluation;
		
		int poisonousFoodNumber;
		
		static int cooperate;
		static int globalId;

//		static void generate(Person* parent, Person* child);
};

#endif
