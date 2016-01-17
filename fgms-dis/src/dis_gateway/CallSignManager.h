#pragma once
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

	static int getASCIalphaEnum(int asciEnumerator);
};




