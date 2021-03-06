#include "Pickup.h"

#include "Core/Entity.h"
#include "Core/OmegaEngine.h"

Pickup::Pickup()
{
}

Pickup::~Pickup()
{
}

void Pickup::OnInitialized()
{
	_physics = GetEntity()->GetComponent<PhysicsComponent>();
	_rotator = GetEntity()->GetComponent<Rotator>();
}

void Pickup::Grab()
{
	_physics->SetEnabled(false);
	_rotator->SetEnabled(false);
	GetEntity()->transform.setLocalRotation(glm::vec3(0.0f));
}

void Pickup::Drop(glm::vec3 gPos)
{
	Vector2D gPosition = Vector2D(gPos.x, gPos.z);
	PhysicsManager::instance()->getGrid()->positionObject(gPosition);
	PhysicsManager::instance()->getGrid()->createObject(gPosition, _physics);
	_physics->SetEnabled(true);
	_rotator->SetEnabled(true);
	GetEntity()->transform.setLocalRotation(glm::vec3(0.42f, 0.0f, 0.0f));
	OmegaEngine::Instance().GetActiveScene()->root.AddChild(GetEntity());
	_physics->moveBody(&gPosition, 0);
	_physics->initPosition();
	
}

Component* Pickup::Create(json json)
{
	auto c = ComponentManager<Pickup>::Instance().Create<Pickup>();	
	c->type = json["type"].get<PICKUPS>();
	return c;
}

PrefabRegistrar Pickup::reg("Pickup", Pickup::Create);
