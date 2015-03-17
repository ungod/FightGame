#pragma once

#include <vector>
#include <string>

using namespace std;

static inline void splitString(std::string src, const char* token, std::vector<std::string>& vect)
{
	int nend=0;
	int nbegin=0;
	while(nend != -1)
	{
		nend = src.find(token, nbegin);
		if(nend == -1)
			vect.push_back(src.substr(nbegin, src.length()-nbegin));
		else
			vect.push_back(src.substr(nbegin, nend-nbegin));
		nbegin = nend + strlen(token);
	}
}

static void splitStringWithForm(std::string str, std::vector<std::string>& strs)
{
	size_t nPosLeft  = str.find('{');
	size_t nPosRight = str.find('}');

	if (nPosLeft == std::string::npos || nPosRight == std::string::npos)
		return;

	string sub = str.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
	splitString(sub, ",", strs);
}