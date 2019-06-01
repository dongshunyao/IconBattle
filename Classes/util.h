#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using std::string;
using std::vector;
using std::sort;
using std::mt19937;

namespace Util
{
#pragma region Hash
	const long long BASE = 233;
	const long long MOD = 1000000000 + 9;

	int getStringHash(const string& str);
	int getStringHash(vector<string> str);
#pragma endregion

#pragma region random
	// 随机数，左右均为闭区间
	int getRandomNumber(int l, int r);
#pragma endregion
};

#endif
