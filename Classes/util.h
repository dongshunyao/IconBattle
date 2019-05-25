#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::sort;

namespace Util
{
#pragma region Hash
	const long long BASE = 233;
	const long long MOD = 1000000000 + 9;

	long long getStringHash(const string& str);
	long long getStringHash(vector<string> str);
#pragma endregion
};

#endif
