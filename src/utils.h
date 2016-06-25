#ifndef UTILS_H_
#define UTILS_H_

#include <string>

std::wstring to_wstring(std::string str) {
	std::wstring wstr(str.begin(), str.end());
	return wstr;
}

#endif /*UTILS_H_*/
