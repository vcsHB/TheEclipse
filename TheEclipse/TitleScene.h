#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;


	int ming = 100; // ���߿� �����ߵ�.

private:
	bool _isExiting;
	float _exitDuration = 0.5f;
	float _currentExitTime = 0.f;

private :

	void HandleGameStart(bool value);
};

