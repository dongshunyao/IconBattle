#include "User.h"

User* User::instance = nullptr;

User* User::getInstance()
{
	if (instance == nullptr) instance = new User;
	return instance;
}

User::User()
{
}
