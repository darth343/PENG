#include "ParticleEffectManager.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace NC;

ParticleEffectManager::ParticleEffectManager()
{
	
}

void ParticleEffectManager::Init()
{

}

void ParticleEffectManager::Update(float dt)
{

}

//This is a wrapper function to call existing Cocos2d ParticleEffects
void ParticleEffectManager::CreateParticleEffect
(int type, Vec2 Position, float Duration, Scene Currentscene)
{
	ParticleSystemQuad* _Particle;
	switch (type)
	{
		case 1:
		{
			_Particle = new ParticleExplosion();
			break;
		}
		case 2:
		{
			_Particle = new ParticleFire();
			break;
		}
		case 3:
		{
			_Particle = new ParticleFireworks();
			break;
		}
	}
	_Particle->setPosition(Position);
	_Particle->setDuration(Duration);
	Currentscene.addChild(_Particle, 10);
	
}

ParticleObject::ParticleObject()
	:m_position(0, 0), m_scale(0.f, 0.f), rotation(0.f)
	, m_rotationspeed(0.f), active(false)
{

}