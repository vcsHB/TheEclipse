#pragma once
#include "Object.h"
//class Object; // 클래스 전방선언
class Canvas;
class Scene
{
public:
	Scene();
	virtual ~Scene(); // 가상 소멸자
public:
	virtual void Init() abstract;
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hdc);
	virtual void Release();
public:
	const void AddObject(Object* _obj, LAYER _type)
	{
		_obj->SetId(_objectIdCount);
		_objectIdCount++;
		m_vecObj[(UINT)_type].push_back(_obj);
	}
	const vector<Object*>& GetLayerObjects(LAYER _type)
	{
		return m_vecObj[(UINT)_type];
	}
	Object* FindObjectByName(wstring name);
	Canvas* GetCanvas() { return _canvas; }

	void StartObjects();
private:
	//Object m_obj;
	//Object* m_pObj;
	vector<Object*> m_vecObj[(UINT)LAYER::END];
	int _objectIdCount = 0;
protected:

	Canvas* _canvas;
	void SetCanvas(Canvas* canvas) { _canvas = canvas; }
};

