#if !defined ENTITYTABLE_HXX
#define ENTITYTABLE_HXX

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
		//map to store names of entities
		Map m_name;

		//function to reduce EntityType	stepwise to find match
		std::string EntityTable::reduceKey(std::string key);
		//search function, here first entry in map is the search key
		Map::iterator EntityTable::FindPrefix(const string& search);
		//search function, here second entry in map is the search key
		Map::iterator EntityTable::FindSuffix(const string& search);	

		//std::string EntityTable::EntitytoString(DIS::EntityType Entity);	

		std::string EntityTable::ToZahl(unsigned char wert);
		unsigned short EntityTable::ToInt(std::string wert);

	public:
		EntityTable();
		virtual ~EntityTable();
		//returns the model-name for a given EntityType
		std::string EntityTable::getFGModel(DIS::EntityType Entity);
		//returns the EntityType for a given model-path
		DIS::EntityType* EntityTable::getDISModelFromModelName(std::string model);
		//returns the EntityType for a given model-path
		DIS::EntityType* EntityTable::getDISModelFromFGModel(std::string model);
		//returns Entity Name for given EntityType
		std::string EntityTable::getName(DIS::EntityType Entity);

		Map EntityTable::getm_name();
		std::string EntityTable::EntityToString(DIS::EntityType Entity);
		DIS::EntityType* EntityTable::StringToEntity(string type);

		//init-function, here the .xml is loaded
		void EntityTable::initializeEntityTable();
		void EntityTable::InsertEntity(DIS::EntityType Entity,  std::string FGmodel, std::string name);
		void EntityTable::clear();
		

};

#endif