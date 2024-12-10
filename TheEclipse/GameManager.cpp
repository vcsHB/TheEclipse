#include "pch.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "RectTransform.h"
#include "ClearPanel.h"


void GameManager::Initialize(RectTransform* clearPanel, RectTransform* overPanel)
{
	_isGameOver = false;
	_clearPanel = clearPanel;
	_overPanel = overPanel;
}

void GameManager::GameClear()
{
	_isGameOver = true;
	_clearPanel->GetComponent<ClearPanel>()->Open();
}

void GameManager::GameOver()
{
	_isGameOver = true;
	_overPanel->GetComponent<ClearPanel>()->Open();

}

void GameManager::Update()
{
	if (!_isGameOver) return;
	_currentWaitTime += fDT;
	if (_currentWaitTime > _waitTime)
	{
		GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
	}

}
