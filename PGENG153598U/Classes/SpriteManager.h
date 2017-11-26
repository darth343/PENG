#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "SingletonTemplate.h"
#include "cocos2d.h"

using namespace cocos2d;
#include <vector>
#include <map>

using std::vector;
using std::map;

class SpriteManager : public Singleton<SpriteManager>
{
	friend Singleton<SpriteManager>;
public:
	virtual ~SpriteManager();

	void GenerateSprite(const std::string& fileName, int numCol = 1, int numRow = 1);
	SpriteFrame* GetSpriteFrame(const std::string& fileName, unsigned spriteIndex = 0);

protected:
	SpriteManager();

	std::map<std::string, std::vector<SpriteFrame*>> spriteFrameMap;
};

#endif