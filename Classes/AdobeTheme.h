#ifndef __ADOBE_THEME_H__
#define __ADOBE_THEME_H__
#include "Theme.h"

class AdobeTheme
	: public Theme
{
public:
	const string themeName = "Adobe";


	static AdobeTheme* getInstance();

protected:
	AdobeTheme() = default;

private:
	static AdobeTheme* instance;
};


#endif
