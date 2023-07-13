#ifndef OBJECTPOOL_HPP
#define OBJECTPOOL_HPP

#include "pch.h"
#include "Box.h"
#include "Bullet.h"
#include "Item.h"
#include "Wall.h"
#include "Enemy.h"
#include "Client.h"
#include "Player.h"

inline std::mutex entities_mtx;
inline std::mutex box_mtx;
inline std::mutex client_mtx;
inline std::mutex bullet_mtx;
inline std::mutex item_mtx;
inline std::mutex wall_mtx;

template <typename T>
class ObjectPool
{
private:
	std::vector<std::unique_ptr<T>> pool;
public:
	void checkSize(std::vector<std::unique_ptr<T>>& vec)
	{
		std::cout << typeid(T).name() << " pool capacity: " << pool.capacity() << " pool size: " << pool.size() << " vec size: " << vec.size() << "\n";
	}

	void init(std::unique_ptr<GameVariable>& gv, std::vector<std::unique_ptr<T>>& vec, size_t capacity)
	{
		//	std::lock_guard<std::mutex> lock(entities_mtx);
		pool.reserve(std::move(capacity));
		for (size_t i = 0; i < pool.capacity(); ++i) { pool.emplace_back(std::make_unique<T>(gv)); }

		std::cout << "init ";
		checkSize(vec);
	}

	bool getFromPool(std::vector<std::unique_ptr<T>>& vec)
	{
		//	std::lock_guard<std::mutex> lock(entities_mtx);
		if (pool.size() > 0)
		{
			vec.emplace_back(std::move(pool.back()));
			pool.pop_back();

			/*		std::cout << "bool getFromPool() ";
					checkSize(vec);*/
			return true;
		}
		else { std::cout << typeid(T).name() << " bool getFromPool(): pool size < count!\n"; return false; }
	}

	bool returnEverythingToPool(std::vector<std::unique_ptr<T>>& vec)
	{
		//std::lock_guard<std::mutex> lock(entities_mtx);
		if (!vec.empty())
		{
			size_t vecSize = vec.size();
			for (size_t i = 0; i < vecSize; ++i)
			{
				pool.emplace_back(std::move(vec.back()));
				vec.pop_back();
			}
			//std::cout << "bool returnEverythingToPool() ";
			//checkSize(vec);
			return true;
		}
		else { std::cout << typeid(T).name() << " returnEverythingToPool(): vec is empty!\n"; return false; }
	}

	bool returnToPool(std::vector<std::unique_ptr<T>>& vec, std::unique_ptr<T>& el)
	{
		//std::lock_guard<std::mutex> lock(entities_mtx);
		if (el.get() != nullptr)
		{
			pool.emplace_back(std::move(el));
			//std::cout << "bool returnToPool() ";
			//checkSize(vec);
			return true;
		}
		else { std::cout << typeid(T).name() << " returnToPool(): unique_ptr is nullptr!\n"; return false; }
	}

	void eraseEmptyVecElements(std::vector<std::unique_ptr<T>>& vec)
	{
		//std::lock_guard<std::mutex> lock(entities_mtx);
		vec.erase(std::remove_if(vec.begin(), vec.end(), [](std::unique_ptr<T>& el) { return el == nullptr; }), vec.end());
	}
};

inline std::vector<std::unique_ptr<Box>> boxVec;
inline std::vector<std::unique_ptr<Bullet>> bulletVec;
inline std::vector<std::unique_ptr<Enemy>> enemyVec;
inline std::vector<std::unique_ptr<Wall>> wallVec;
inline std::vector<std::unique_ptr<Item>> itemVec;
inline std::vector<std::unique_ptr<Client>> clientVec;
inline std::unique_ptr<Player> playerPtr;

inline ObjectPool<Box> boxPool;
inline ObjectPool<Bullet> bulletPool;
inline ObjectPool<Enemy> enemyPool;
inline ObjectPool<Wall> wallPool;
inline ObjectPool<Item> itemPool;
inline ObjectPool<Client> clientPool;

#endif
