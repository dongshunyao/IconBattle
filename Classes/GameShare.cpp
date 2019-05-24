#include "GameShare.h"
using namespace GameShareNamespace;

USING_NS_CC;

GameShare* GameShare::instance = nullptr;

GameShare* GameShare::getInstance()
{
	if (instance == nullptr) instance = new GameShare;
	return instance;
}

void GameShare::sharePicToTencent()
{
	// µ¯³öä¯ÀÀÆ÷´ò¿ªQQ·ÖÏíÍøÖ·
	CCApplication::getInstance()->openURL(QQ_SHARE_URL);
}

void GameShare::sharePicToXinlang()
{
	CCApplication::getInstance()->openURL(XINLANG_SHARE_URL);
}

void GameShare::sharePicToRenren()
{
	CCApplication::getInstance()->openURL(RENREN_SHARE_URL);
}

void GameShare::sharePicToDouban()
{
	CCApplication::getInstance()->openURL(DOUBAN_SHARE_URL);
}

