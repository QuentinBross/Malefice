// CLIENT VERSION

#include "WeaponSystem.h"
#include "SceneAnimatedMesh.h"
#include "GraphicUtil.h"
#include "ClientCore.h"
#include "Target.h"
#include "Line3dWrapper.h"

namespace ecs
{
	void	WeaponSystem::shoot(Entity& entity)
	{
		WeaponManager*		weaponManager;

		if ((weaponManager = dynamic_cast<WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])) != nullptr)
		{
			Weapon&	weapon = weaponManager->getCurrentWeapon();
			Target::getInstance().refresh();
			LOG_DEBUG(ECS) << dynamic_cast<SceneAnimatedMesh*>((entity)[ecs::AComponent::ComponentType::SCENE])->getPosition();
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::WEAPON_SYSTEM_SHOOT, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::WeaponSystem), &entity, &Line3dWrapper(Target::getInstance().getRay()));
		}
	}
}
