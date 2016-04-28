#pragma once

#include "StdInc.h"
#include "AComponent.h"

namespace ecs
{
	class Entity
	{
	public:
		const int								ID;
	private:
		std::map<ComponentType, AComponent*>	m_mComponents;

	public:
		Entity();
		~Entity();
		Entity(const Entity&) = delete;
		Entity(Entity &&) = default;
		
		Entity& operator=(const Entity&) = delete;
		Entity& operator=(Entity &&) = default;

		AComponent*&	operator[](ComponentType type);
		bool			has(ComponentType type);

		void	dump() const;
	};
}