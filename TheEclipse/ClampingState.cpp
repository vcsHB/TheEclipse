#include "pch.h"
#include "State.h"
#include "ClampingState.h"
#include "Enemy.h"
#include "Player.h"
#include "StateMachine.h"
#include "Projectile.h"



Projectile* projectiles[4];
void ClampingState::Enter()
{
	State::Enter();
}

void ClampingState::Exit()
{
	State::Exit();
}

void ClampingState::Movement(float _dt)
{

}

void ClampingState::Shooting(float _dt)
{
}
