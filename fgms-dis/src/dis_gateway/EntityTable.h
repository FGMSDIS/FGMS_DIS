#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <algorithm>
#include <DIS/EntityType.h>
#include <pugixml/pugixml.hpp>

using namespace std;
typedef std::map<std::string, std::string> Map;

//////////////////////////////////////////////////////////////////////
//
//  Central class for processing Entity Type Tables
//
//	reads the mapping-table (entitytable.xml) and puts the EntityType/model pairs in a map
//
//////////////////////////////////////////////////////////////////////
class EntityTable
{
	protected:

		//map to store the entries
		Map m_entity;

		//function to reduce EntityType	stepwise to find match
		std::string reduceKey(std::string key);
		//search function, here first entry in map is the search key
		Map::iterator FindPrefix(const string& search);
		//search function, here second entry in map is the search key
		Map::iterator FindSuffix(const string& search);

		std::string EntitytoString(DIS::EntityType Entity);

		std::string ToZahl(unsigned char wert);
		unsigned short ToInt(std::string wert);

	public:
		EntityTable();
		virtual ~EntityTable();
		//returns the model-name for a given EntityType
		std::string getModel(DIS::EntityType Entity);
		//returns the EntityType for a given model-name
		DIS::EntityType getModel(std::string model);
		//init-function, here the .xml is loaded
		void initializeEntityTable();
		void InsertEntity(DIS::EntityType Entity, std::string model);
		void clear();


};
