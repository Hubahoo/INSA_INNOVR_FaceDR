/**
 * @file Gallery.hpp
 * The gallery object contains all the known faces.
 * A std::vector of Person is used to handle the data. The Gallery is loaded from a sqlite database.
 * The faces database stores the first name, the last name and the histogram of a person.
 * The histograms are serialized and stored in the database or in single files with the Boost library.
 */

#ifndef GALLERY_HPP
#define GALLERY_HPP

#include <vector>
#include "Person.hpp"

/**
 * The Gallery class is basically a collection of persons.
 * It provides all the tools needed to handle the faces database. The information are loaded with the 
 * default constructor.
 */
class Gallery
{
public:
	/**
	 * The default constructor.
	 * Loads all the needed information in the vector of Person
	 */
	Gallery();
	
	/**
	 * The default deconstructor.
	 */
	~Gallery();
	
	/**
	 * Add a Person in the sqlite database.
	 * @param p The Person to add in the database.
	 * @return int sqlite error code.
	 */
	int addToDatabase(Person p);
	
	/**
	 * Return a string describing all the gallery.
	 * Describe every Person in the Gallery.
	 */
	std::string toString();
	
	/**
	 * Search in the gallery for the closest face of the query Person.
	 * @param p The query Person.
	 * @return The closest Person found.
	 */
	Person search(Person p);

private:
	std::vector<Person> gallery;
};

#endif //GALLERY_HPP


