#ifndef GALLERY_HPP
#define GALLERY_HPP

#include <vector>
#include "Person.hpp"

class Gallery
{
public:
	Gallery();
	~Gallery();
	int addToDatabase(Person p);
	std::string toString();
	Person search(Person p);

private:
	std::vector<Person> gallery;
};

#endif //GALLERY_HPP


