#pragma once
//#include <queue>
#include <unordered_map>
#include <type_traits> // std::is_base_of
#include "SceneManager.h"
#include "Scene.h"
#include "IPoolable.h"
#include "Projectile.h"


class PoolManager
{
	~PoolManager();
private:
	static std::unordered_map<PoolingType, std::queue<IPoolable*>> pool;
	static std::unordered_map<int, IPoolable*> enabledPool;

public:
	

	static void Initialize();

	static void AddPool(PoolingType type, IPoolable* poolable)
	{
		if (pool.find(type) == pool.end())
		{ // 만들어진 풀링이 있음
			pool[type] = std::queue<IPoolable*>();
		}
		pool[type].push(poolable);
		GET_SINGLE(SceneManager)->GetCurrentScene().get()->AddObject(poolable->GetPoolObject(), LAYER::PROJECTILE);
		cout << "ID : " << poolable->GetPoolObject()->GetId() << "| Added In Pool" << endl;
	}


	static IPoolable* Pop(PoolingType type);

	static void Push(IPoolable* poolable);


};