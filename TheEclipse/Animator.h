#pragma once
#include "Component.h"
class Texture;
class Animation;
class Object;
class Animator : public Component
{
public:
	Animator();
	~Animator();
public:
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
public:
	// �ִϸ��̼� �����Լ�
	void CreateAnimation(const wstring& _strName, Texture* _pTex,
		Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep,
		UINT _framecount, float _fDuration, bool _isRotate = false);
	// �ִϸ��̼� ã���Լ�
	Animation* FindAnimation(const wstring& _strName);

	// �ִϸ��̼� �÷��� �Լ�
	void PlayAnimation(const wstring& _strName, bool _IsRepeat, int _repeatcnt = 1);
	void StopAnimation();
public:
	Animation* GetCurrentAnim() { return m_pCurrentAnimation; }
	const bool& GetRepeat() const { return m_IsRepeat; }
	const int& GetRepeatcnt() const { return m_repeatcnt; }
	void SetRepeatcnt() { --m_repeatcnt; }
private:
	map<wstring, Animation*> m_mapAnimations;
	Animation* m_pCurrentAnimation;
	bool	m_IsRepeat;
	int		m_repeatcnt;
};

