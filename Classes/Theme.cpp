#include "Theme.h"

Theme* Theme::instance = nullptr;

Theme* Theme::getInstance()
{
	if (instance == nullptr) instance = new Theme;
	return instance;
}
