#include "AdobeTheme.h"

AdobeTheme* AdobeTheme::instance = nullptr;

AdobeTheme* AdobeTheme::getInstance()
{
	if (instance == nullptr) instance = new AdobeTheme();
	return instance;
}
