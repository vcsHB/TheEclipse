#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"
Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

void Scene::Update()
{
	//for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	//{
	//	for (size_t j = 0; j < m_vecObj[i].size();)
	//	{
	//		if (!m_vecObj[i][j]->GetIsDead())
	//			m_vecObj[i][j++]->Update();
	//		else
	//			m_vecObj[i].erase(m_vecObj[i].begin() + j);
	//	}
	//}
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (m_vecObj[i][j] != nullptr && !m_vecObj[i][j]->GetIsDead() && m_vecObj[i][j]->enabled)
				m_vecObj[i][j]->Update();
		}
	}

}

void Scene::LateUpdate()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{

		for (UINT j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (m_vecObj[i][j] != nullptr && !m_vecObj[i][j]->GetIsDead() && m_vecObj[i][j]->enabled)
				m_vecObj[i][j]->LateUpdate();
		}
	}
}

void Scene::Render(HDC _hdc)
{
	//for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	//{
	//	for (size_t j = 0; j < m_vecObj[i].size(); ++j)
	//	{
	//		if (!m_vecObj[i][j]->GetIsDead())
	//			m_vecObj[i][j]->Render(_hdc);
	//	}
	//}
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size();)
		{
			//if (!m_vecObj[i][j]->enabled) continue;
			if (m_vecObj[i][j] != nullptr && !m_vecObj[i][j]->GetIsDead() && m_vecObj[i][j]->enabled)
				m_vecObj[i][j++]->Render(_hdc);
			else
				m_vecObj[i].erase(m_vecObj[i].begin() + j);
		}
	}

}

void Scene::Release()
{
	// 오브젝트 삭제.
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (UINT j = 0; j < m_vecObj[i].size(); ++j)
		{
			delete m_vecObj[i][j];
		}
		m_vecObj[i].clear();
	}
	GET_SINGLE(CollisionManager)->CheckReset();
}

Object* Scene::FindObjectByName(wstring name)
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (Object* object : m_vecObj[i])
		{
			if (object->GetName() == name)
			{
				return object;
			}
		}
	}
	std::wcout << L"Can't Found Object By Name. name:[" << name << L"]";
	return nullptr;
}

void Scene::StartObjects()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (UINT j = 0; j < m_vecObj[i].size(); ++j)
		{
			m_vecObj[i][j]->Start();
		}
	}
}
