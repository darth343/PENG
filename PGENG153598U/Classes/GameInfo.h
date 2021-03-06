#ifndef GAMEINFO_H
#define GAMEINFO_H

#define PLAYER_HEALTH_AMOUNT 999
#define PLAYER_MOVE_DURATION 0.05f
#define PLAYER_MOVE_COOLDOWN 0.0f
#define PLAYER_ATTACK1_ANIM_SPEED 0.1f
#define PLAYER_ATTACK1_COOLDOWN 0.1f
#define PLAYER_ATTACK1_SPEED 2000.0f
#define PLAYER_ATTACK2_ANIM_SPEED 0.5f
#define PLAYER_ATTACK2_COOLDOWN 2.0f
#define PLAYER_ATTACK2_SPEED 300.0f


enum MASK
{
	FRIENDLY_ENTITY = 1,
	ENEMY_ENTITY = 2,
	PROJECTILE = 4,
};

enum ButtonTag
{
	BTN_UP,
	BTN_DOWN,
	BTN_LEFT,
	BTN_RIGHT,

	BTN_VIRTUALJOY,

	BTN_A,
	BTN_B,

	BTN_END
};

#endif