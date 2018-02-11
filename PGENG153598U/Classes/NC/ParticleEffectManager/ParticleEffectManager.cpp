#include "ParticleEffectManager.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace NC;

ParticleEffectManager::ParticleEffectManager()
{
	node = Node::create();
	node->setName("ParticleNode");
}

void ParticleEffectManager::Init(Scene* scene)
{
	CreateParticleEffect(2, Vec2(100, 100), 5.f);
	scene->addChild(node, 10);
}

void ParticleEffectManager::Update(float dt)
{

}

//This is a wrapper function to call existing Cocos2d ParticleEffects
void ParticleEffectManager::CreateParticleEffect(int type, Vec2 Position, float Duration)
{
	ParticleSystemQuad *_Particle;
	switch (type)
	{
		case 1:
		{
			_Particle = ParticleExplosion::create();
			break;
		}
		case 2:
		{
			_Particle = ParticleFire::create();
			break;
		}
		case 3:
		{
			_Particle = ParticleFireworks::create();
			break;
		}
	}
	_Particle->setPosition(Position);
	//_Particle->setSpeed(5.f);
	_Particle->setDuration(Duration);
	_Particle->setName("Particle");
	//bool test = _Particle->isActive();
	node->addChild(_Particle, 10);
	
}

ParticleObject::ParticleObject()
	:m_position(0, 0), m_scale(0.f, 0.f), rotation(0.f)
	, m_rotationspeed(0.f), active(false)
{

}