#include "pch.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "RectTransform.h"
#include "ClearPanel.h"
#include "OverPanel.h"

void GameManager::Initialize(RectTransform* clearPanel, RectTransform* overPanel)
{
	_isGameOver = false;
	_clearPanel = clearPanel;
	_overPanel = overPanel;
};

void GameManager::GameClear()
{
	_isGameOver = true;
	_clearPanel->GetComponent<ClearPanel>()->Open();
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
}

void GameManager::GameOver()
{
	_isGameOver = true;
	_overPanel->GetComponent<OverPanel>()->Open();
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);

}

void GameManager::Update()
{
	if (!_isGameOver) return;
	_currentWaitTime += fDT;
	if (_currentWaitTime > _waitTime)
	{
		GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
		GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
	}

}
