
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


			
			// Serialization of the histogram in a stringstream
			/*std::stringstream ss;
			{
				boost::archive::text_oarchive oa(ss);
				oa << h;
			}
			std::cout << ss.str() << std::endl;
			*/
			
			// Serialization of the histogram in a fstream
			/*
			std::fstream fs("serializationFile", std::ios::out);
			{
				boost::archive::text_oarchive oa(fs);
				oa << h;
			}*/
			
			
			Person closestPerson = gallery.search(p); //Research the closest person in the gallery
			
	

