#pragma once
#include "Object.h"
#include "GameScene.h"
class Texture;
class CrackLine :
	public Object
{
public:
	CrackLine(WorldSpaceScene* scene);
	~CrackLine();
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetLineDamage(int damage);
	void SetPos(Vec2 v) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
public:
	Texture* m_pTex;
	int _damage;
	float moveSpeed = 1.f;
private:
	//float m_dir;
	WorldSpaceScene* currentScene;
	float m_angle;
	Vec2 m_vDir;
	Vec2 originPos;

};

