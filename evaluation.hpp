#ifndef _EVALUATION_HPP
#define _EVALUATION_HPP

#include <map>

class Evaluation
{
	public:
		Evaluation();
		~Evaluation();
		
		void reset();
		
		void exchangeEvaluation(const Evaluation& other_evaluation);
		void initThisForThat();
		void initZero();

		int getBehavior(const int id) const;

		void updateEvaluation(int id, int experience);
		
		void generateChild(Evaluation* partner, Evaluation* child) const;
		void mutate();
		
//	private:

		std::map<int, int> behavior;

		int behaviorAdaption; // aufgrund eines positiven oder negativen Ereignisses

		int exchangeBehaviorAdaption;

		int firstBehavior;
		int firstBehaviorAdaption;
		
};

#endif


// Problem: erst giftig, dann gesund => gesundes wird nicht akzeptiert.
