#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sqlite3.h>

#include "Gallery.hpp"

Gallery::Gallery()
{
	std::cout << "FaceRecognition: creating the Gallery ..." << std::endl;
	
	// Initialization of the vector
	this->gallery =	std::vector<Person>();
		
	sqlite3 *db;
	int sqlError = 0;
	
	sqlError = sqlite3_open("FacesDatabase.db", &db);
	
	if (sqlError){
		std::cout << "Error: can't open the database" << std::endl;
	}
	else {
		std::cout << "FaceRecognition: database opened successfully" << std::endl;
		
		// Retrieve all the database
		const char *zSql = "SELECT * FROM faces;";
		sqlite3_stmt *pStmt;
		
		sqlError = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
		
		std::cout << "Debug: sqlError = " << sqlError << std::endl; 
		if (sqlError != SQLITE_OK){
			std::cout << "Error: preparing statement" << std::endl;
		}
		
		// Keep calling sqlite3_step until it returned something other than SQLITE_ROW
		while ((sqlError = sqlite3_step(pStmt)) == SQLITE_ROW){
			
			std::cout << "Debug: sqlError = " << sqlError << std::endl;
			
			// Load the firstname and lastname
			std::string firstname((const char *)sqlite3_column_text(pStmt, 1));
			std::string lastname((const char *)sqlite3_column_text(pStmt, 2));
			
			// Load the histogram
			Histogram h;
			char *pzBlob; // Pointer to the retrieved blob 
			int sizeOfBlob;
			
			sizeOfBlob = sqlite3_column_bytes(pStmt, 3);
			std::cout << "Debug: sizeOfBlob = " << sizeOfBlob << std::endl;
			pzBlob = (char *) malloc(sizeOfBlob); // essayer void *
			memcpy(pzBlob, sqlite3_column_blob(pStmt, 3), sizeOfBlob); // Free pzBlob ?
			
			//still in test
			
			{
				std::stringstream ss(pzBlob);
				// Debug: display the stream retrieved from the database
				//std::cout << ss.str() << std::endl << std::endl;
				
				boost::archive::text_iarchive ia (ss);
				ia >> h; // load the histogram
			}
			
			Person p(firstname, lastname, h); // Constructeur de recopie par défault ? on risque pas de perde l'histo ?
			
			// Fill the vector
			gallery.push_back(p);
		}
		
		if(sqlError == SQLITE_DONE){
			std::cout << "Debug: SQLITE_DONE" << std::endl;
		}
		
		// Finalize the statement
		sqlError = sqlite3_finalize(pStmt);
		
		if (sqlError != SQLITE_OK){
			std::cout << "Error: SQL query" << std::endl;
		}
		else{
			std::cout << "FaceRecognition: database loaded in the gallery" << std::endl;
		}
		sqlite3_close(db);
	}

}

Gallery::~Gallery()
{
}

// Add a Person in the database, but not in the gallery
int Gallery::addToDatabase(Person p)
{
	std::cout << "FaceRecognition: adding the face in the database ..." << std::endl;
	
	sqlite3 *db;	//Database to insert data into

	int sqlError = sqlite3_open("FacesDatabase.db", &db); //Open the database
	
	
	if (sqlError != SQLITE_OK){
		std::cout << "Error: can't open the database" << std::endl;
		return sqlError;
	}
	else {
		std::cout << "FaceRecognition: database opened successfully" << std::endl;
		
		const char *zSql = "INSERT INTO faces (firstname, lastname, histogram) VALUES (?, ?, ?);";
		sqlite3_stmt *pStmt;
		
		do {
		
			sqlError = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
		
			if (sqlError != SQLITE_OK){
				std::cout << "Error: SQL query" << std::endl;
				return sqlError;
			}
		
			
			//serialisation de l'histogramme
			//encore en test !

			Histogram h = p.getHistogram();
			
			// Serialization of the histogram in a stringstream
			std::stringstream ss;
			{
				boost::archive::text_oarchive oa(ss);
				oa << h;
			}

			sqlite3_bind_text(pStmt, 1, p.getFirstname().c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(pStmt, 2, p.getLastname().c_str(), -1, SQLITE_STATIC);
			int test = sqlite3_bind_blob(pStmt, 3, ss.str().data(), ss.str().size(), SQLITE_STATIC);
			//essayer avec void *
			std::cout << "Debug: test bind blob = " << test << std::endl;// bind blob OK
			
			std::cout << "Debug: size of blob string added = " << ss.str().size() << std::endl;
			std::cout << "Debug: blob added = " << ss.str().data() << std::endl;
			
			sqlError = sqlite3_step(pStmt);
			
			if(sqlError == SQLITE_DONE){
				std::cout << "FaceRecognition: face added in the gallery" << std::endl;
			}
			
			sqlError = sqlite3_finalize(pStmt);
			
		}while (sqlError == SQLITE_SCHEMA);
			
		sqlite3_close(db);
	}
	return sqlError;
}

//A FINIR !
std::string Gallery::toString()
{
	return "";
}

Person Gallery::search(Person p){
	float dmin = p.getHistogram().distance(gallery.front().getHistogram());
	float d = 0;
	int indexClosest = 0;
	int i = 0;
	
	for (std::vector<Person>::iterator it = gallery.begin() ; it != gallery.end() ; ++it){
		
		d = p.getHistogram().distance(it->getHistogram());
		std::cout << "Debug: distance = " << d << std::endl;
		
		if (d >= 0 && d < dmin){
			dmin = d;
			indexClosest = i;
		}
		
		i++;
	}
	
	std::cout << "Debug: distance min = " << dmin << ", index = " << indexClosest << std::endl;
	
	return gallery.at(indexClosest);
}


