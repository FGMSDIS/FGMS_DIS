#if !defined CALLSIGNMANAGER_HXX
#define CALLSIGNMANAGER_HXX

#include <map>
#include <string>
#include <sstream>
#include <iostream>


class CallSignManager
{
public:
	CallSignManager(void);
	~CallSignManager(void);
	static std::string getCallSign( int site, int app, int id );

private:
	static std::map<std::string, std::string > m_siteAppPrefix;

	static int CallSignManager::getASCIalphaEnum(int asciEnumerator);
};

#endif



