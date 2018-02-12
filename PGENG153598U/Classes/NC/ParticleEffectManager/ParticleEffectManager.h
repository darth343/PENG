#ifndef PARTICLE_EFFECT_MANAGER_H_
#define PARTICLE_EFFECT_MANAGER_H_

#include "cocos2d.h"

using cocos2d::Vec3;
using cocos2d::Vec2;

USING_NS_CC;

#define MAX_PARTICLE_COUNT 300
namespace NC
{
	class ParticleEffectManager
	{
	private:
		int m_particlecount;
		//vector<Particle>
	public:
		static ParticleEffectManager& getInstance()
		{
			static ParticleEffectManager instance;
			return instance;
		}
		ParticleEffectManager();

		void Init(Scene* scene);
		void Update(float dt);

		//Wrapper for existing Particle Effects
		void CreateParticleEffect(int type, Vec2 Position, float Duration);

		CCNode* getnode() { return node; }
	private:
		ParticleEffectManager(ParticleEffectManager const&);
		void operator= (ParticleEffectManager const&);

		CCNode* node;
	};

	class ParticleObject
	{
	public:
		ParticleObject();
		~ParticleObject() {}
	private:
		Vec2 m_position;
		Vec2 m_velocity;
		Vec2 m_scale;
		float rotation;
		float m_rotationspeed;
		bool active;
	};
}


#endif
