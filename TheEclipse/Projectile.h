#pragma once
#include "Object.h"
#include "GameScene.h"
#include "IPoolable.h"
class Texture;

class Projectile : public Object, public IPoolable
{
public:
	Projectile();
	Projectile(WorldSpaceScene* scene);
	~Projectile();
	void Update() override;
	void Render(HDC _hdc) override;

public:

	void SetProjectile(int damage);
	void SetAngle(float _f)
	{
		m_angle = _f;
	}
	void SetDir(Vec2 _dir)
	{
		m_vDir = _dir;
		m_vDir.Normalize();
	}
	void SetPos(Vec2 v) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);

public:
	PoolingType GetPoolingType() override;
	Object* GetPoolObject() override;
	void ResetItem() override;
public:
	Texture* m_pTex;
	int _damage;
	bool isAnimated = false;
	float moveSpeed = 1.f;
	float lifeTime = 10.f;
private:
	//float m_dir;
	WorldSpaceScene* currentScene;
	float m_angle;
	Vec2 m_vDir;
	Vec2 originPos;
	float _currentLifeTime = 0.f;


};

