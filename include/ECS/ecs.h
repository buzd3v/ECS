#pragma once

#include "ComponentManager.h"
#include "EnttManager.h"
#include "SystemManager.h"
#include "ecs.h"
#include <memory>

namespace ecs
{
class Ecs
{
  public:
    void Init()
    {
        m_ComponentManager = std::make_unique<ComponentManager>();
        m_EntityManager = std::make_unique<EnttManager>();
        m_SystemManager = std::make_unique<SystemManager>();
    }

    entity CreateEntity()
    {
        return m_EntityManager->CreateEntity();
    }

    void DestroyEntity(entity id)
    {
        m_ComponentManager->EntityDestroyed(id);
        m_EntityManager->DestroyEntity(id);
        m_SystemManager->EntityDestroyed(id);
    }

    template <typename T> void RegisterComponent()
    {
        m_ComponentManager->RegisterComponent<T>();
    }
    template <typename T> void AddComponentToEntity(entity id, T component)
    {
        m_ComponentManager->AddComponent<T>(id, component);

        // change entity signature
        auto sign = m_EntityManager->GetSignature(id);
        sign.set(m_ComponentManager.get()->GetComponentType<T>(), true);

        // set entity signature, checking for new system can be applied
        m_EntityManager->SetSignature(id, sign);

        // check if entity is match system-> added to system entity set
        m_SystemManager->ChangeEntitySignature(id, sign);
    }

    template <typename T> void RemoveComponentFromEntity(entity id)
    {
        m_ComponentManager->RemoveComponent<T>(id);

        auto sign = m_EntityManager->GetSignature(id);
        sign.set(m_ComponentManager->GetComponentType<T>(), false);

        m_EntityManager->SetSignature(id, sign);
        m_SystemManager->ChangeEntitySignature(id, sign);
    }
    template <typename T> T &GetComponent(entity id)
    {
        return m_ComponentManager->GetComponent<T>(id);
    }

    template <typename T> componentType GetComponentType()
    {
        return m_ComponentManager->GetComponentType<T>();
    }

    template <typename T> std::shared_ptr<T> RegisterSystem()
    {
        return m_SystemManager->RegisterSystem<T>();
    }

    template <typename T> void SetSystemSignature(signature signature)
    {
        m_SystemManager->SetSignature<T>(signature);
    }

  private:
    std::unique_ptr<ComponentManager> m_ComponentManager;
    std::unique_ptr<EnttManager> m_EntityManager;
    std::unique_ptr<SystemManager> m_SystemManager;
};

} // namespace ecs
