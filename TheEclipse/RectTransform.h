#pragma once
#include <vector>

class CanvasComponent;
class RectTransform
{
public:
	RectTransform();
	virtual ~RectTransform();

private:
	vector<CanvasComponent*> _components;
public:
	void Initialize();
	void Update();
	void Render(HDC hdc);

public:
	
	template<typename T>
	void AddComponent()
	{
		T* com = new T;
		com->SetOwner(this);
		_components.push_back(com);
	}
	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (CanvasComponent* com : _components)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}

public:
	bool enabled;

public:
	void SetPos(Vec2 _vPos) { _position = _vPos; }
	void SetSize(Vec2 _vSize) 
	{ 	
		_size = _vSize; 
	}
	RECT GetRect() 
	{ 
		_rect = RECT_MAKE((LONG)_position.x, (LONG)_position.y, (LONG)_size.x, (LONG)_size.y);

		return _rect; 
	
	}
	const Vec2& GetPos() const { return _position; }
	const Vec2& GetSize() const { return _size; }
private:

	Vec2 _position;
	Vec2 _size;
	RECT _rect;

};
