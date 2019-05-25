#include "Util.h"

long long Util::getStringHash(const string& str)
{
	const int length = str.length();
	vector<int> hash(length + 10);

	hash[0] = static_cast<long long>(str[0]) % MOD;
	for (auto i = 1; i < str.length(); i++) hash[i] = (hash[i - 1] * BASE + static_cast<long long>(str[i])) % MOD;

	return (hash[length - 1] - length * BASE + MOD) % MOD;
}

long long Util::getStringHash(vector<string> str)
{
	sort(str.begin(), str.end());

	long long hash = 0;
	for (const auto& it : str) hash = (hash + getStringHash(it)) % MOD;

	return hash;
}
