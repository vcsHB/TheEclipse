#pragma once
#include "Scene.h"
class WorldSpaceScene : public Scene
{
public:
	Vec2 m_WorldPosition = { 0.f, 0.f };
	///Vec2 m_WorldPosition =//WorldPos
	//{ GetSystemMetrics(SM_CXSCREEN) / 2 - SCREEN_WIDTH / 2
	//, GetSystemMetrics(SM_CYSCREEN) / 2 - SCREEN_HEIGHT / 2 };
	Vec2 m_deltaPos;
	float m_moveSpeed = 100.f;
};

