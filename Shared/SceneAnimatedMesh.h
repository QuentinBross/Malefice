#pragma once

#include <BitStream.h>
#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneAnimatedMesh : public AScene
	{
	public:
		SceneAnimatedMesh();
		SceneAnimatedMesh(irr::IrrlichtDevice* device, irr::scene::ISceneNode* parent, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable, const bool lighting, const irr::u32 level);
		SceneAnimatedMesh(const SceneAnimatedMesh& cpy);
		virtual ~SceneAnimatedMesh();

		virtual AComponent&	affect(const AComponent& rhs);

		virtual void	init(irr::IrrlichtDevice* device, irr::scene::ISceneNode* parent, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, const bool isCollisionable, const bool lighting, const irr::u32 level);

		virtual irr::scene::ISceneNode*	getNode()	const;
		virtual void						setPosition(const ecs::Position& newPosition);
		void								setAnimation(irr::scene::EMD2_ANIMATION_TYPE newAnimationType);
		void								setTexture(const std::string& nameTexture);
		irr::scene::IAnimatedMeshSceneNode*	getScene()				const;

		Position							getPosition()	const;

		void								setCollision(bool gratity);

		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);

		virtual AComponent*	createCopy(const AComponent* rhs) const;

		void				deleteTexture();
	private:
		irr::scene::IAnimatedMeshSceneNode*					m_node;
		bool												m_lighting;
		irr::u32											m_level;
	};
}
