#include "SpriteManager.h"

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
	for (auto q : spriteInfoMap)
	{
		for (auto r : q.second.spriteFrameList)
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
	spriteInfoMap[fileName].width = width;
	spriteInfoMap[fileName].height = height;
	spriteInfoMap[fileName].spriteFrameList.reserve(numCol * numRow);

	for (int i = 0; i < numRow; ++i)
	{
		for (int j = 0; j < numCol; ++j)
		{
			SpriteFrame* sprite = SpriteFrame::createWithTexture(texture, Rect(j * width, i * height, width, height));
			sprite->retain();

			spriteInfoMap[fileName].spriteFrameList.push_back(sprite);
		}
	}
}

SpriteFrame* SpriteManager::GetSpriteFrame(const std::string& fileName, unsigned spriteIndex)
{
	if (spriteInfoMap[fileName].spriteFrameList.size() <= spriteIndex)
	{
		cocos2d::log("SpriteManager::GetSprite-> %s has less than %d number of frames", fileName, spriteIndex);
		return nullptr;
	}

	SpriteFrame* newSprite = SpriteFrame::createWithTexture(
		spriteInfoMap[fileName].spriteFrameList.at(spriteIndex)->getTexture(),
		spriteInfoMap[fileName].spriteFrameList.at(spriteIndex)->getRect()
	);
	return newSprite;
}

float SpriteManager::GetSpriteWidth(const std::string& fileName)
{
	return spriteInfoMap[fileName].width;
}

float SpriteManager::GetSpriteHeight(const std::string& fileName)
{
	return spriteInfoMap[fileName].height;
}