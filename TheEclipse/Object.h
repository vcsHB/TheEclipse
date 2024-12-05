#pragma once
class Collider;
class Component;
class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual void Update() abstract;
	virtual void LateUpdate();
	virtual void Render(HDC _hdc) abstract;
	virtual Vec2 OriginPos();
	void ComponentRender(HDC _hdc);
public:
	virtual void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetSize(Vec2 _vSize) { m_vSize = _vSize; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetSize() const { return m_vSize; }
	const bool& GetIsDead() const { return m_IsDie; }
	const void SetActive(bool value) { enabled = value; }
	void SetDead() { m_IsDie = true; }

	const void SetId(int id) { _objectID = id; }
	int GetId() { return _objectID; }
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);

	void SetName(wstring _name) { m_name = _name; }
	const wstring& GetName() const { return m_name; }

public:
	bool m_IsDie;
	bool enabled = true;
	wstring m_name;

public:
	template<typename T>
	void AddComponent()
	{
		T* com = new T;
		com->SetOwner(this);
		m_vecComponents.push_back(com);
	}
	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* com : m_vecComponents)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}
private:
	int _objectID;
	//POINT m_ptPos;
	//POINT m_ptSize;
	Vec2 m_vPos = { 0,0 };
	Vec2 m_vSize;
	vector<Component*> m_vecComponents;
};

