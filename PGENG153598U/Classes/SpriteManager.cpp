#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
	for (auto q : spriteFrameMap)
	{
		for (auto r : q.second)
		{
			r->release();
		}
	}
}

void SpriteManager::GenerateSprite(const std::string& fileName, int numCol, int numRow)
{
	Sprite* spriteSheet = Sprite::create(fileName);
	if (spriteSheet == nullptr)
	{
		cocos2d::log("Entity: %s not found, failed to create entity", fileName);
		return;
	}

	Texture2D* texture = spriteSheet->getTexture();
	float width = spriteSheet->getContentSize().width / numCol;
	float height = spriteSheet->getContentSize().height / numRow;
	spriteFrameMap[fileName].reserve(numCol * numRow);

	for (int i = 0; i < numRow; ++i)
	{
		for (int j = 0; j < numCol; ++j)
		{
			SpriteFrame* sprite = SpriteFrame::createWithTexture(texture, Rect(j * width, i * height, width, height));
			sprite->retain();
			spriteFrameMap[fileName].push_back(sprite);
		}
	}
}

SpriteFrame* SpriteManager::GetSpriteFrame(const std::string& fileName, unsigned spriteIndex)
{
	if (spriteFrameMap[fileName].size() <= spriteIndex)
	{
		cocos2d::log("SpriteManager::GetSprite-> %s has less than %d number of frames", fileName, spriteIndex);
		return nullptr;
	}

	SpriteFrame* newSprite = SpriteFrame::createWithTexture(
		spriteFrameMap[fileName].at(spriteIndex)->getTexture(),
		spriteFrameMap[fileName].at(spriteIndex)->getRect()
	);
	return newSprite;
}