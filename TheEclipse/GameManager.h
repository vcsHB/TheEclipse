#pragma once
class RectTransform;
class GameManager
{
	DECLARE_SINGLE(GameManager);

public:
	void Initialize(RectTransform* clearPnel, RectTransform* overPanel);

	void GameClear();
	void GameOver();

	void Update();
private:
	bool _isGameOver;
	RectTransform* _clearPanel;
	RectTransform* _overPanel;

	float _waitTime = 3.f;
	float _currentWaitTime = 0.f;
};

