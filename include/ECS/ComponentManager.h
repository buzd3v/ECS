#pragma once
#include "global.h"
#include <array>
#include <cassert>
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <vcruntime.h>

namespace ecs
{

class IComponentArray
{
  public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(entity id) = 0;
};

template <typename T> class ComponentArray : public IComponentArray
{
  public:
    void InsertData(entity ett, T component)
    {
        assert(m_EnttToIndexMap.find(ett) == m_EnttToIndexMap.end() && "Component already added to entity");

        size_t newIndex = m_Size;               // the last index is the size of component array
        m_EnttToIndexMap[ett] = newIndex;       // map entity to the last index
        m_IndexToEnttMap[newIndex] = ett;       // do the same so in the ett is mapping to an index,
        m_ComponentArray[newIndex] = component; //  that index is where to put component

        m_Size++;
    }
    void RemoveData(entity ett)
    {
        assert(m_EnttToIndexMap.find(ett) != m_EnttToIndexMap.end() && "Remove non-existen component");

        auto index_to_remove = m_EnttToIndexMap[ett];
        auto index_of_last_element = m_Size - 1;
        // change component data index
        m_ComponentArray[index_to_remove] = m_ComponentArray[index_of_last_element];

        auto last_entity = m_IndexToEnttMap[index_of_last_element];
        m_EnttToIndexMap[last_entity] = index_to_remove;
        m_IndexToEnttMap[index_to_remove] = last_entity;

        // remove data
        m_EnttToIndexMap.erase(ett);
        m_IndexToEnttMap.erase(index_of_last_element);

        --m_Size;
    }

    T &GetData(entity ett)
    {
        assert(m_EnttToIndexMap.find(ett) != m_EnttToIndexMap.end() && "The entity to get data iss not exist");

        auto index = m_EnttToIndexMap[ett];
        return m_ComponentArray[index];
    }

    void EntityDestroyed(entity id) override
    {
        if (m_EnttToIndexMap.find(id) != m_EnttToIndexMap.end())
        {
            RemoveData(id);
        }
    }

  private:
    std::array<T, MAX_ENTT> m_ComponentArray;
    std::unordered_map<entity, size_t> m_EnttToIndexMap;
    std::unordered_map<size_t, entity> m_IndexToEnttMap;

    size_t m_Size = 0;
};

class ComponentManager
{
  public:
    template <typename T> void RegisterComponent()
    {
        auto typeName = typeid(T).name();
        assert(m_ComponentTypes.find(typeName) == m_ComponentTypes.end() && "Registering exist component");

        m_ComponentTypes.insert({typeName, m_NextComponentType});
        m_ComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

        m_NextComponentType++;
    }

    template <typename T> componentType GetComponentType()
    {
        auto typeName = typeid(T).name();
        assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered");

        return m_ComponentTypes[typeName];
    }

    template <typename T> void AddComponent(entity id, T component)
    {
        GetComponentArray<T>()->InsertData(id, component);
    }
    template <typename T> void RemoveComponent(entity id)
    {
        GetComponentArray<T>()->RemoveData(id);
    }
    template <typename T> T &GetComponent(entity id)
    {
        return GetComponentArray<T>()->GetData(id);
    }

    void EntityDestroyed(entity id)
    {
        for (auto const &pair : m_ComponentArrays)
        {
            auto const &component = pair.second;
            component->EntityDestroyed(id);
        }
    }

  private:
    std::unordered_map<const char *, componentType> m_ComponentTypes;
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>> m_ComponentArrays;

    componentType m_NextComponentType{};

    template <typename T> std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        auto typeName = typeid(T).name();
        assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() &&
               "The components seem do not being registered before");

        return std::dynamic_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]); // using for RTTI
    }
};
} // namespace ecs