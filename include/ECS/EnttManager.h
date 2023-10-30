#include "global.h"
#include <array>
#include <cassert>
#include <cstdint>
#include <queue>

namespace ecs
{
class EnttManager
{
  public:
    EnttManager()
    {
        for (auto entity = 0; entity < MAX_ENTT; entity++)
        {
            m_AvailableEntities.push(entity);
        }
    }

    entity CreateEntity()
    {
        assert(m_LivingEntityCount < MAX_ENTT && "Too many entt exist");

        entity id = m_AvailableEntities.front();
        m_AvailableEntities.pop();
        ++m_LivingEntityCount;

        return id;
    }

    void DestroyEntity(entity id)
    {
    }

    void SetSignature(entity id, const signature &sign)
    {
        assert(id < MAX_ENTT && "Entity out of range");

        m_Signatures[id] = sign;
    }

    signature GetSignature(entity id)
    {
        assert(id < MAX_ENTT && "Entity out of range");
        return m_Signatures[id];
    }

  private:
    // count how many entity available to create
    std::queue<ecs::entity> m_AvailableEntities;

    std::array<ecs::signature, MAX_ENTT> m_Signatures;

    // with one entity created m_AvailableEntities minus one and mLivingEntityCount plus one
    uint32_t m_LivingEntityCount = 0;
};
} // namespace ecs