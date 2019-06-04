#include "Util.h"

int Util::getStringHash(const string& str)
{
	const int length = str.length();
	vector<int> hash(length + 10);

	hash[0] = length ? static_cast<long long>(str[0]) % MOD : 0;
	for (auto i = 1; i < length; i++) hash[i] = (hash[i - 1] * BASE + static_cast<long long>(str[i])) % MOD;

	return static_cast<int>((hash[length - 1] - length * BASE + MOD) % MOD);
}

int Util::getStringHash(vector<string> str)
{
	sort(str.begin(), str.end());

	long long hash = 0;
	for (const auto& it : str) hash = (hash + getStringHash(it)) % MOD;

	return static_cast<int>(hash);
}

int Util::getRandomNumber(const int l, const int r)
{
	mt19937 rand(time(nullptr));

	auto num = rand();
	num = l + num % (r - l + 1);

	return num;
}

int Util::getRandomNumber(const int r)
{
	return getRandomNumber(0, r - 1);
}
