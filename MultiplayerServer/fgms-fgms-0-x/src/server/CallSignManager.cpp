#include "CallSignManager.h"


CallSignManager::CallSignManager(void)
{
}


CallSignManager::~CallSignManager(void)
{
}

 std::map <std::string, std::string > CallSignManager::m_siteAppPrefix;

std::string CallSignManager::getCallSign(int site, int app, int id)
{
	//string for callsign (return value)
	std::string callSign;
	//stringstream for int to string
	std::stringstream temp1;
	temp1 << site;
	temp1 << ":";
	temp1 << app;
	//string with Site:App (=mapKey)
	std::string siteApp(temp1.str() );

	std::map<std::string,std::string>::iterator it;
	//check if already in map
	it = m_siteAppPrefix.find(siteApp);
	if ( it == m_siteAppPrefix.end() )
	{
		if ( (int)m_siteAppPrefix.size() < 62*62)
		{
			//map does not contain siteApp combination
			//create Prefix
			int char1 = (int)m_siteAppPrefix.size() / 62;
			int char2 = (int)m_siteAppPrefix.size() % 62;
			//map to alpanumeric ASCI-code
			char1 = CallSignManager::getASCIalphaEnum(char1);
			char2 = CallSignManager::getASCIalphaEnum(char2);

			std::stringstream temp2;
			temp2 << (char)char1;
			temp2 << (char)char2;
			//Add to Map
			m_siteAppPrefix[ siteApp ] = temp2.str();
			callSign.append( temp2.str() );
		}
		else
		{
			std::cout << "CallSignManager: Map reached maxSize, PDU from  " << site << ":" << app << ":" << id << " can not be converted to unique flightgear CallSign!\n";

			return ("IMWRONG");
		}
	}
	else
	{
		//map contains siteApp combination
		callSign.append( m_siteAppPrefix[siteApp] );
	}
	//append DIS-id to callSign
	std::stringstream temp3;
	temp3 << id;
	callSign.append(temp3.str() );
	return callSign;
}

//function to map an int enumerator to alphanumeric ASCI-codes
int CallSignManager::getASCIalphaEnum(int asciEnumerator)
	{
	int result = asciEnumerator;
	result += 48;//offset for first number
	if (result > 57 && result < 65)//jump to 65, which is the first capital character
		result += 7;
	if (result > 90 && result < 97)//jump to 97, which is the first non capital character
		result += 6;
	if (result > 122)
		result = 0;

	return result;

	}
