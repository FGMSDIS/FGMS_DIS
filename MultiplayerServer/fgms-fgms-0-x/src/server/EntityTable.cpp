#include "EntityTable.h"





EntityTable::EntityTable()
{
}

EntityTable::~EntityTable()
{
}

void EntityTable::InsertEntity(DIS::EntityType Entity, std::string FGmodel, std::string name){
   	
	string key = EntityToString(Entity);
	//store the key and the model
	//m_entity.insert(std::pair<std::string, std::string>(key, model));
	m_entity[key]=FGmodel;
	m_name[key]=name;
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

string EntityTable::EntityToString(DIS::EntityType Entity){
	//get Entity Type Strings and build into new String
	std::string key;
	// always insert kind and domain
	key.append(ToZahl(Entity.getEntityKind()));
	key.append(":");
	key.append(ToZahl(Entity.getDomain()));
	//only insert country if country is not 0 or if country is zero (other countries) but category is non-zero
	if((Entity.getCountry()==0 && Entity.getCategory()!=0) || Entity.getCountry()!=0)
	{
		key.append(":");
		key.append(ToZahl(Entity.getCountry()));
		// if category is zero, assume that all other values are zero (according to IEEE1278.1 enumerations)
		if(Entity.getCategory()!=0)
		{
			key.append(":");
			key.append(ToZahl(Entity.getCategory()));
			// if subcategory is zero, assume that all other values are zero (according to IEEE1278.1 enumerations)
			if(Entity.getSubcategory()!=0)
			{
				key.append(":");
				key.append(ToZahl(Entity.getSubcategory()));
				// if specific is zero, assume that all other values are zero (according to IEEE1278.1 enumerations)
				if(Entity.getSpecific()!=0)
				{
					key.append(":");
					key.append(ToZahl(Entity.getSpecific()));
					// if extra is zero, assume that all other values are zero (according to IEEE1278.1 enumerations)
					if(Entity.getExtra()!=0)
					{
						key.append(":");
						key.append(ToZahl(Entity.getExtra()));
					}
				}
			}
		}
	}
	return key;
}

DIS::EntityType* EntityTable::StringToEntity(string type){
	string value;
	DIS::EntityType* entityType = new DIS::EntityType();
	//first substring  -> kind
	value = type.substr(0, type.find_first_of(":") );
	entityType->setEntityKind( ToInt(value) );
	//second substring   -> domain
	type = type.substr(type.find_first_of(":") + 1 , type.size() );
	value = type.substr(0, type.find_first_of(":") );
	entityType->setDomain( ToInt(value) );
	//third substring   -> country (only if value exists in enumeration)
	unsigned int pos = type.find_first_of(":");
	if(pos != string::npos)
	{
		type = type.substr(pos + 1 , type.size() );
		value = type.substr(0, type.find_first_of(":") );
		entityType->setCountry( ToInt(value) );
		//fourth substring   -> category (only if value exists in enumeration)
		pos = type.find_first_of(":");
		if(pos != string::npos)
		{
			type = type.substr(pos + 1 , type.size() );
			value = type.substr(0, type.find_first_of(":") );
			entityType->setCategory ( ToInt(value) );
			//fifth substring   -> subcategory (only if value exists in enumeration)
			pos = type.find_first_of(":");
			if(pos != string::npos)
			{
				type = type.substr(pos + 1 , type.size() );
				value = type.substr(0, type.find_first_of(":") );
				entityType->setSubcategory ( ToInt(value) );
				//sixth substring   -> specific (only if value exists in enumeration)
				pos = type.find_first_of(":");
				if(pos != string::npos)
				{
					type = type.substr(pos + 1 , type.size() );
					value = type.substr(0, type.find_first_of(":") );
					entityType->setSpecific ( ToInt(value) );
					//seventh substring -> extra (only if value exists in enumeration)
					pos = type.find_first_of(":");
					if(pos != string::npos)
					{
						type = type.substr(pos + 1 , type.size() );
						entityType->setExtra ( ToInt(type) );
					}
				}
			}
		}
	}
	return entityType;
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



string EntityTable::getFGModel(DIS::EntityType Entity){

	string model;
	string key = EntityToString(Entity);
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

DIS::EntityType* EntityTable::getDISModelFromModelName(string model)
	{
		//find entry in map
		Map::iterator k = m_name.begin();
		Map::iterator i;
		bool entryfound = false;
		while (!entryfound && k != m_name.end())
		{
			const string& key = k->second;
			if (key.compare(0, model.size(), model) == 0)
			{
				i = k;
				entryfound = true;
			}
			k++;
		}

		//if correct entry is found
		if (entryfound)
		{
			return StringToEntity(i->first);
		}
		//if no matching entry is found
		else
		{
			return NULL;
		}

	}

DIS::EntityType* EntityTable::getDISModelFromFGModel(string model)
	{
		//find entry in map
		Map::iterator i = FindSuffix(model);

		//if correct entry is found
		if (i != m_entity.end())
		{
			return StringToEntity(i->first);
		}
		//if no matching entry is found
		else
		{
			return NULL;
		}
	}

std::string EntityTable::getName(DIS::EntityType Entity)
	{
		string key = EntityToString(Entity);
		try
		{
			string name = m_name.at(key);
			return name;
		}
		catch(exception e)
		{
			return "";
		}
	}

void EntityTable::initializeEntityTable(){
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("entitytable.xml");
	pugi::xml_node entitys = doc.child("EntityTable");
	std::cout << "Loading Entity Table: " << result.description() << std::endl;
	for (pugi::xml_node entity = entitys.first_child(); entity; entity = entity.next_sibling())
		{
		string FGmodel;
		string modelName;
		DIS::EntityType entype;
		for (pugi::xml_node attr = entity.first_child(); attr; attr = attr.next_sibling())
			{
				string attributeName = attr.name();
				// Tag = "name"
				if(attributeName == "name")
				{
					modelName = attr.text().as_string();
				}
				// Tag = "entitytype"
				if(attributeName == "entitytype")
				{
				//std::cout << "EntityType: ";
				for (pugi::xml_node type = attr.first_child(); type; type = type.next_sibling()){
					string tag = type.name();
					if(tag == "kind"){
						int id = type.text().as_int();
						entype.setEntityKind(id);
						//std::cout << type.text().as_string() << ":";
						}
					else if(tag == "domain"){
						int id = type.text().as_int();
						entype.setDomain(id);
						//std::cout << type.text().as_string() << ":";
						}
					else if(tag == "country"){
						int id = type.text().as_int();
						entype.setCountry(id);
						//std::cout << type.text().as_string() << ":";
						}
					else if(tag == "category"){
						int id = type.text().as_int();
						entype.setCategory(id);
						//std::cout << type.text().as_string() << ":";
						}
					else if(tag == "subcategory"){
						int id = type.text().as_int();
						entype.setSubcategory(id);
						//std::cout << type.text().as_string() << ":";
						}
					else if(tag == "specific"){
						int id = type.text().as_int();
						entype.setSpecific(id);
						//std::cout << type.text().as_string() << ":";
						}
					else if(tag == "extra"){
						int id = type.text().as_int();
						entype.setExtra(id);
						//std::cout << type.text().as_string() << std::endl;
						}
					else{
							std::cout << "unknown tag " << tag << " in entitytable.xml\n";
						}
					}
				
				
				//std::cout << "Key: " << key << std::endl;
				}
				if(attributeName == "model"){
					FGmodel = attr.text().as_string();
					//std::cout << "Model: " << attr.text().as_string() << std::endl;
				}
			
		
			//InsertEntity(entype, model);
			//m_entity[key]=model;
			}												  
			InsertEntity(entype, FGmodel, modelName);

		}
	for(Map::const_iterator it = m_entity.begin(); it != m_entity.end(); it++)
		{
			std::cout << it->first << " " << it->second << std::endl;
		}
}