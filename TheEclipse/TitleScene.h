#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;


	int ming = 100; // 나중에 지워야됨.

private:
	bool _isExiting;
	float _exitDuration = 0.5f;
	float _currentExitTime = 0.f;

private :

	void HandleGameStart(bool value);
};

