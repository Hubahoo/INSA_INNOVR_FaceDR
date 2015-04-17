#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

#include "Histogram.hpp"

class Person
{
public:
	Person();
	Person(std::string firstname, std::string lastname, Histogram h);
	~Person();
	
	inline std::string getFirstname() const
	{
		return firstname;
	}
	
	inline std::string getLastname()
	{
		return lastname;
	}
	
	inline Histogram getHistogram()
	{
		return h;
	}
	
	std::string toString();

private:
	std::string firstname;
	std::string lastname;
	Histogram h;
	
};

#endif //PERSON_HPP
