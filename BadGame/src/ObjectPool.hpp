#ifndef OBJECT_POOL_HPP
#define OBJECT_POOL_HPP

#include "GameVariable.h"
#include "GameWindow.h"
#include "SingleplayerManager.h"
#include "NetworkManager.h"

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

	void init(std::unique_ptr<GameVariable>& gv, std::unique_ptr<GameWindow>& gw, std::unique_ptr<SingleplayerManager>& sm, std::unique_ptr<NetworkManager>& nm, std::vector<std::unique_ptr<T>>& vec, size_t capacity)
	{
		pool.reserve(std::move(capacity));
		for (size_t i = 0; i < pool.capacity(); ++i) { pool.emplace_back(std::make_unique<T>(gv, gw, sm, nm)); }

		std::cout << "init ";
		checkSize(vec);
	}

	void clear() { pool.clear(); }

	bool getFromPool(std::vector<std::unique_ptr<T>>& vec)
	{
		if (pool.size() > 0)
		{
			vec.emplace_back(std::move(pool.back()));
			pool.pop_back();
			return true;
		}
		else { std::cout << typeid(T).name() << " bool getFromPool(): pool size < count!\n"; return false; }
	}

	bool returnEverythingToPool(std::vector<std::unique_ptr<T>>& vec)
	{
		if (!vec.empty())
		{
			while (vec.size() != 0)
			{
				pool.emplace_back(std::move(vec.back()));
				vec.pop_back();
			}
			return true;
		}
		else { std::cout << typeid(T).name() << " returnEverythingToPool(): vec is empty!\n"; return false; }
	}

	bool returnToPool(std::vector<std::unique_ptr<T>>& vec, std::unique_ptr<T>& el)
	{
		if (el.get() != nullptr)
		{
			pool.emplace_back(std::move(el));
			vec.erase(std::remove(vec.begin(), vec.end(), el));
			return true;
		}
		else { std::cout << typeid(T).name() << " returnToPool(): unique_ptr is nullptr!\n"; return false; }
	}
};

#endif
