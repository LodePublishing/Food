#ifndef _EXPERIENCE_HPP
#define _EXPERIENCE_HPP

class Experience
{
	public:
		Experience();
		~Experience();
		int getValue(int item);
		void setValue(int item, int value);
	private:
		int item;
		int value;
}

#endif
