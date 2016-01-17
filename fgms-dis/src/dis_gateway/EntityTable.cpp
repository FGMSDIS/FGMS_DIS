#include "EntityTable.h"





EntityTable::EntityTable()
{
}

EntityTable::~EntityTable()
{
}

void EntityTable::InsertEntity(DIS::EntityType Entity, std::string model){
   	
	string key = EntitytoString(Entity);
	//store the key and the model
	//m_entity.insert(std::pair<std::string, std::string>(key, model));
	m_entity[key]=model;
	//m_entity.insert(map_entity.begin(), map_entity.end());
	}

void EntityTable::clear(){
	m_entity.clear();
	}

string EntityTable::ToZahl(unsigned char wert){
	int zahl;
	ostringstream Str;
	zahl = wert;
	Str << zahl;
	string super(Str.str());
	return super;
	}
unsigned short EntityTable::ToInt(std::string wert)
	{
	//stringstream for convert string to int 
	istringstream convert(wert);
	//int for returning the result
	unsigned short result;
	convert >> result;
	return result;
	}

string EntityTable::EntitytoString(DIS::EntityType Entity){
	//get Entity Type Strings and build into new String
	std::string key;
	//kind
	key.append(ToZahl(Entity.getEntityKind()));
	key.append(":");
	//domain
	key.append(ToZahl(Entity.getDomain()));
	key.append(":");
	key.append(ToZahl(Entity.getCountry()));	
	key.append(":");
	key.append(ToZahl(Entity.getCategory()));
	key.append(":");
	key.append(ToZahl(Entity.getSubcategory()));
	key.append(":");
	key.append(ToZahl(Entity.getSpecific()));
	key.append(":");
	key.append(ToZahl(Entity.getExtra()));
	return key;
	
	}

Map::iterator EntityTable::FindPrefix(const string& search){
	Map::iterator i = m_entity.lower_bound(search);
	if(i != m_entity.end())
		{
		const string& key = i->first;
		if (key.compare(0, search.size(), search) == 0)
			return i;

		}
	return m_entity.end();
	}
Map::iterator EntityTable::FindSuffix(const string& search)
	{
	Map::iterator i = m_entity.begin();
	while (i != m_entity.end() )
		{
		const string& key = i->second;
		if (key.compare(0, search.size(), search) == 0)
			return i;
		i++;
		}
	return m_entity.end();
	}

string EntityTable::reduceKey(std::string key){

	unsigned found = key.find_last_of(":");
	if (found == string::npos){
		key = "NULL";
		return key;
		}
	else return key.substr(0,found);
	}



string EntityTable::getModel(DIS::EntityType Entity){

	string model;
	string key = EntitytoString(Entity);
	/*Loop
	It loops until it finds a fitting model 
	and with every loop it reduces the key until
	there is just the Entity Type "KIND" left.**/
	while(key != "NULL"){
		Map::iterator i = FindPrefix(key);
		if (i != m_entity.end()){
			model = i->second;
			return model;
			}
		else  key = reduceKey(key);
		}
	//no fitting model found so return a default model
	return model = "/default/model";
	}

DIS::EntityType EntityTable::getModel(string model)
	{
	//a DIS EntityType for the return value
	DIS::EntityType entityType;
	string type;
	//find entry in map
	Map::iterator i = FindSuffix(model);

	//if correct entry is found
	if (i != m_entity.end())
		{
			string value;
			//get the DIS EntityType out of the map
			type = i->first;
			//first substring  -> kind
			value = type.substr(0, type.find_first_of(":") );
			entityType.setEntityKind( ToInt(value) );
			//second substring   -> domain
			type = type.substr(type.find_first_of(":") + 1 , type.size() );
			value = type.substr(0, type.find_first_of(":") );
			entityType.setDomain( ToInt(value) );
			//third substring   -> country
			type = type.substr(type.find_first_of(":") + 1 , type.size() );
			value = type.substr(0, type.find_first_of(":") );
			entityType.setCountry( ToInt(value) );
			//fourth substring   -> category
			type = type.substr(type.find_first_of(":") + 1 , type.size() );
			value = type.substr(0, type.find_first_of(":") );
			entityType.setCategory ( ToInt(value) );
			//fifth substring   -> subcategory
			type = type.substr(type.find_first_of(":") + 1 , type.size() );
			value = type.substr(0, type.find_first_of(":") );
			entityType.setSubcategory ( ToInt(value) );
			//sixth substring   -> specific
			type = type.substr(type.find_first_of(":") + 1 , type.size() );
			value = type.substr(0, type.find_first_of(":") );
			entityType.setSpecific ( ToInt(value) );
			type = type.substr(type.find_first_of(":") + 1 , type.size() );
			entityType.setExtra ( ToInt(type) );

		}
	//if no matching entry is found
	else
		{
		 	//set EntityType manually to default values
			entityType.setEntityKind( 1 );
			entityType.setDomain( 3 );
			entityType.setCountry( 78 );
			entityType.setCategory ( 50 );
			entityType.setSubcategory ( 2 );
			entityType.setSpecific ( 1 );
			entityType.setExtra ( 0 );
		}

	return entityType;
	}

void EntityTable::initializeEntityTable(){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("entitytable.xml");
	pugi::xml_node entitys = doc.child("EntityTable");
	std::cout << "Loading Entity Table: " << result.description() << std::endl;
	for (pugi::xml_node entity = entitys.first_child(); entity; entity = entity.next_sibling())
		{
		string model, key;
		DIS::EntityType entype;
		for (pugi::xml_node attr = entity.first_child(); attr; attr = attr.next_sibling())
			{
			// Tag = "entitytype"
			string name = attr.name();
			if(name == "entitytype")
				{
				//std::cout << "EntityType: ";
				for (pugi::xml_node type = attr.first_child(); type; type = type.next_sibling()){
					string tag = type.name();
					if(tag == "kind"){
						int id = type.text().as_int();
						entype.setEntityKind(id);
						//std::cout << type.text().as_string() << ":";
						}
					if(tag == "domain"){
						int id = type.text().as_int();
						entype.setDomain(id);
						//std::cout << type.text().as_string() << ":";
						}
					if(tag == "country"){
						int id = type.text().as_int();
						entype.setCountry(id);
						//std::cout << type.text().as_string() << ":";
						}
					if(tag == "category"){
						int id = type.text().as_int();
						entype.setCategory(id);
						//std::cout << type.text().as_string() << ":";
						}
					if(tag == "subcategory"){
						int id = type.text().as_int();
						entype.setSubcategory(id);
						//std::cout << type.text().as_string() << ":";
						}
					if(tag == "specific"){
						int id = type.text().as_int();
						entype.setSpecific(id);
						//std::cout << type.text().as_string() << ":";
						}
					if(tag == "extra"){
						int id = type.text().as_int();
						entype.setExtra(id);
						//std::cout << type.text().as_string() << std::endl;
						}
					}
				
				
				//std::cout << "Key: " << key << std::endl;
			}
			// Tag = "name"
		if(name == "name"){
				//std::cout << "Name: " << attr.text().as_string() << std::endl;
			}
		if(name == "model"){
				model = attr.text().as_string();
				//std::cout << "Model: " << attr.text().as_string() << std::endl;
			}
			
		
		//InsertEntity(entype, model);
		//m_entity[key]=model;
		}												  
		InsertEntity(entype, model);

		}
	for(Map::const_iterator it = m_entity.begin(); it != m_entity.end(); it++)
		{
	std::cout << it->first << " " << it->second << std::endl;
		}
}