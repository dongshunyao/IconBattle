#include "JetBrainTheme.h"

JetBrainTheme* JetBrainTheme::instance = nullptr;

JetBrainTheme* JetBrainTheme::getInstance()
{
	if (instance == nullptr) instance = new JetBrainTheme();
	return instance;
}
