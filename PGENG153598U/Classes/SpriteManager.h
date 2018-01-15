#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "SingletonTemplate.h"
#include "cocos2d.h"

using namespace cocos2d;
#include <vector>
#include <map>

using std::vector;
using std::map;

struct SpriteInfo;
class SpriteManager : public Singleton<SpriteManager>
{
	friend Singleton<SpriteManager>;
public:
	virtual ~SpriteManager();

	void GenerateSprite(const std::string& fileName, int numCol = 1, int numRow = 1);
	SpriteFrame* GetSpriteFrame(const std::string& fileName, unsigned spriteIndex = 0);

	Size GetContentSize(const std::string& fileName);
	float GetSpriteWidth(const std::string& fileName);
	float GetSpriteHeight(const std::string& fileName);

protected:
	SpriteManager();

	std::map<std::string, SpriteInfo> spriteInfoMap;
};

struct SpriteInfo
{
	std::vector<SpriteFrame*> spriteFrameList;
	float width;
	float height;
};

#endif