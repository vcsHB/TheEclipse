#include "pch.h"
#include "RectTransform.h"
#include "CanvasComponent.h"

RectTransform::RectTransform()
{
}

RectTransform::~RectTransform()
{
	for (CanvasComponent* com : _components)
	{
		if (com != nullptr)
			delete com;
	}
	_components.clear();
}

void RectTransform::Initialize()
{

	for (CanvasComponent* com : _components)
	{
		if (com != nullptr)
			com->Initialize();
	}
	  
}

void RectTransform::Update()
{
	if (!enabled) return;

	for (CanvasComponent* com : _components)
	{
		if (com)
		{
			com->Update();
		}
	}
}

void RectTransform::Render(HDC hdc)
{
	if (!enabled) return;
	for (CanvasComponent* com : _components)
	{
		if (com)
		{
			com->Render(hdc);
		}
	}
}
