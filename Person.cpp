#include <stdio.h>
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "Person.hpp"

Person::Person()
{
	this->firstname = "";
	this->lastname = "";
	//ajouter initilisation histogram
}

Person::Person(std::string firstname, std::string lastname, Histogram h)
{
	this->firstname = firstname;
	this->lastname = lastname;
	this->h = h;
}

Person::~Person()
{
}

std::string Person::toString(){
	std::stringstream ss ;
	
	ss << "id = " << firstname << " " << lastname;
	ss << std::endl;
	ss << h.toString();
	
	return ss.str();
}
