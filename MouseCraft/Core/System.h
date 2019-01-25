#pragma once

#include <vector>
#include <iterator>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include "Component.h"

class Game;	// circular dependencies


class System
{
	typedef std::unordered_map<std::type_index, std::vector<Component*>> ComponentMap;

public:
	System();
	System(std::vector<std::type_index> forComponents);
	~System();

	// set this to true if you only want the system to be updated once per frame.
	bool onlyReceiveFrameUpdates = false;
	
	virtual void update(float dt) = 0;

	virtual void addComponent(std::type_index t, Component* component)
	{
		auto type = std::type_index(typeid(component));
		if (_componentMap.count(t))
		{
			_componentMap[t].push_back(component);
		}
	}
	
	virtual void clearComponents()
	{
		for (ComponentMap::iterator it = _componentMap.begin(); it != _componentMap.end(); ++it)
		{
			it->second.clear();
		}
	}

	// retrieve an immutable list of the components. components can be mutated.
	// this function creates a copy so store the return results.
	template<class T>
	const std::vector<T*> GetComponents()
	{
		// gross but no other way is working.
		auto type = std::type_index(typeid(T));
		std::vector<T*> casted(_componentMap[type].size());
		for (int i = 0; i < _componentMap[type].size(); i++)
			casted[i] = static_cast<T*>(_componentMap[type][i]);
		return casted;
	}

protected:
	//virtual void onComponentCreated(std::type_index t, Component* c) = 0;
	//virtual void onComponentDestroyed(std::type_index t, Component* c) = 0;
	ComponentMap _componentMap;
};
