#include <string>
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <sqlite3.h>

#include "Gallery.hpp"

using std::cout;
using std::endl;

Gallery::Gallery()
{
	// Initialization of the vector
	this->gallery =	std::vector<Person>();
		
	sqlite3 *db;
	int sqlError = 0;
	
	sqlError = sqlite3_open("FacesDatabase.db", &db);
	
	if (sqlError){
		cout << "Error: can't open the database" << endl;
	}
	else {
		cout << "FaceFramboise: database opened successfully" << endl;
		
		// Retrieve all the database
		const char *zSql = "SELECT * FROM faces;";
		sqlite3_stmt *pStmt;
		
		sqlError = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
		
		if (sqlError != SQLITE_OK){
			cout << "Error: preparing statement failed" << endl;
		}
		
		// Keep calling sqlite3_step until it returned something other than SQLITE_ROW
		while ((sqlError = sqlite3_step(pStmt)) == SQLITE_ROW){
			
			// Load the firstname and lastname
			std::string firstname((const char *)sqlite3_column_text(pStmt, 1));
			std::string lastname((const char *)sqlite3_column_text(pStmt, 2));
			
			// Load the histogram
			std::string filename((const char *)sqlite3_column_text(pStmt, 3));
			cout << "Debug: histogram filename = " << filename << endl;
			
			Histogram h;
			/*
			char *pzBlob; // Pointer to the retrieved blob 
			int sizeOfBlob;
			
			sizeOfBlob = sqlite3_column_bytes(pStmt, 3);
			cout << "Debug: sizeOfBlob = " << sizeOfBlob << endl;
			pzBlob = (char *) malloc(sizeOfBlob); // essayer void *
			memcpy(pzBlob, sqlite3_column_blob(pStmt, 3), sizeOfBlob); // Free pzBlob ?
			*/
			{
				std::fstream fs(filename.c_str());
				// Debug: display the stream retrieved from the database
				//cout << fs.str() << endl;
				
				boost::archive::text_iarchive ia (fs);
				ia >> h; // load the histogram
			}
			
			cout << "Debug: in gallery constructor, histogram = " << endl << h.toString() << endl;
			
			Person p(firstname, lastname, h); // Constructeur de recopie par défault ? on risque pas de perde l'histo ?
			
			// Fill the vector
			gallery.push_back(p);
		}
		
		// Finalize the statement
		sqlError = sqlite3_finalize(pStmt);
		
		if (sqlError != SQLITE_OK){
			cout << "Error: SQL query" << endl;
		}
		else{
			cout << "FaceFramboise: database loaded in the gallery" << endl;
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
	cout << "FaceFramboise: adding the face in the database ..." << endl;
	
	sqlite3 *db; // Database to insert data into

	int sqlError = sqlite3_open("FacesDatabase.db", &db); //Open the database
	
	if (sqlError != SQLITE_OK){
		cout << "Error: can't open the database" << endl;
		return sqlError;
	}
	else {
		cout << "FaceFramboise: database opened successfully" << endl;
		
		const char *zSql = "INSERT INTO faces (firstname, lastname, histogram) VALUES (?, ?, ?);";
		sqlite3_stmt *pStmt;
		
		do {
		
			sqlError = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
		
			if (sqlError != SQLITE_OK){
				cout << "Error: SQL query" << endl;
				return sqlError;
			}

			Histogram h = p.getHistogram();
			
			// Serialization of the histogram in a file stream
			
			std::stringstream ss_filename;
			ss_filename << p.getFirstname() << p.getLastname() << ".histo";
			
			
			std::fstream fs(ss_filename.str().c_str(), std::ios_base::out);
			{
				boost::archive::text_oarchive oa(fs);
				oa << h;
			}

			sqlite3_bind_text(pStmt, 1, p.getFirstname().c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(pStmt, 2, p.getLastname().c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(pStmt, 3, ss_filename.str().c_str(), -1, SQLITE_STATIC);
			
			sqlError = sqlite3_step(pStmt);
			 
			if(sqlError == SQLITE_DONE){
				cout << "FaceFramboise: face added in the database" << endl;
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

Person Gallery::search(Person p)
{
	cout << "FaceFramboise: searching the closest Person in the gallery ..." << endl;
	float dmin = p.getHistogram().distance(gallery.front().getHistogram());
	float d = 0;
	int indexClosest = 0;
	int i = 0;
	
	for (std::vector<Person>::iterator it = gallery.begin() ; it != gallery.end() ; ++it){
		
		d = p.getHistogram().distance(it->getHistogram());
		cout << "Debug: distance = " << d << endl;
		
		if (d >= 0 && d < dmin){
			dmin = d;
			indexClosest = i;
		}
		
		i++;
	}
	
	cout << "Debug: distance min = " << dmin << ", index = " << indexClosest << endl;
	
	return gallery.at(indexClosest);
}


