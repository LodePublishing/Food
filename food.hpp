#ifndef _FOOD_HPP
#define _FOOD_HPP

class Food
{
	public:
		Food();
		~Food();
		void setPoisonous(bool poisonous);
		bool isPoisonous() const;
		int getId() const;
	private:
		bool poisonous;
		int id;
		
		static int globalId;
};

#endif
