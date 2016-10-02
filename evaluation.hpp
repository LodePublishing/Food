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

		int getBehavior(const int id, const int status) const;

		void updateEvaluation(int id, bool experience);
		void generateChild(Evaluation* child) const;
		void mutate();
		
		static int EVALUATION_SIZE;
		static int STATUS_SIZE;
		static int ACTION_SIZE;
		int* behavior;
	private:
		int evaluationOfExchange(int my_evaluation, int other_evaluation) const;
		int getEvalNumber(const int id) const;

// Liste von Bewertungen fuer verschiedene IDs
		std::map<int, int> evaluation;

// Funktion die eine Bewertung zusammen mit dem Status auf eine Handlung mappt		


// Funktion die eine Bewertung zusammen mit der gerade gemachten Erfahrung auf eine neue Bewertung updated
		int* evaluationExperience;

// Funktion die Bewertungen des gegenueber zusammen mit der Bewertung des anderen die Eintraege in evaluation updated
		int* evaluationExchange;
};

#endif


// Problem: erst giftig, dann gesund => gesundes wird nicht akzeptiert.
