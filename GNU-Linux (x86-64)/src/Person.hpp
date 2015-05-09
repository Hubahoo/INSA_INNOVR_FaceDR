/**
 * @file Person.hpp
 * Describe the class Person.
 */

#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

#include "Histogram.hpp"

/**
 * Person class.
 * Describe a person by a firstname, a lastname and a Local Binary Pattern histogram.
 */

class Person
{
public:
	
	/**
	 * The default constructor.
	 * Create a person with an empty firstname and lastname and a default histogram.
	 * The firstname and lastname are empty	string and the histogram is filled with zero
	 * @see Person(std::string firstname, std::string lastname, Histogram h)
	 */
	Person();
	
	/**
	 * A basic constructor
	 * @see Person()
	 */
	Person(std::string firstname, std::string lastname, Histogram h);
	
	/**
	 * The default destructor.
	 */
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
	
	/**
	 * Return a string describing the person.
	 * @return std::string
	 */
	std::string toString();

private:
	/**
	 * The firstname of the person.
	 */
	std::string firstname;
	
	/**
	 * The lastname of the person.
	 */
	std::string lastname;
	
	/**
	 * The Local Binary Pattern histogram of the person.
	 * The LBP histogram is computed from the face of the person. If there are several
	 * faces of the person, the average histogram is computed.
	 */
	Histogram h;
	
};

#endif //PERSON_HPP
