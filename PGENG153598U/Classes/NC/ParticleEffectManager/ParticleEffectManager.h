#ifndef PARTICLE_EFFECT_MANAGER_H_
#define PARTICLE_EFFECT_MANAGER_H_

#include <vector>
#include "cocos2d.h"

using std::vector;
using cocos2d::Vec3;
using cocos2d::Vec2;


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

		void Init();
		void Update(float dt);

		void CreateParticleEffect(int type, Vec2 Position, float Duration, Scene Currentscene);
	private:
		ParticleEffectManager(ParticleEffectManager const&);
		void operator= (ParticleEffectManager const&);
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
