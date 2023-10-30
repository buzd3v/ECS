#pragma once

#include "global.h"
#include <memory>
#include <set>
#include <unordered_map>

namespace ecs
{
class System
{
  public:
    std::set<entity> m_Entities;
};

class SystemManager
{
  public:
    template <typename T> std::shared_ptr<T> RegisterSystem()
    {
        const char *typeName = typeid(T).name();

        assert(m_Systems.find(typeName) == m_Systems.end() && "registering system more than once");

        std::shared_ptr<T> system = std::make_shared<T>();
        m_Systems.insert({typeName, system});
        return system;
    }

    template <typename T> void SetSignature(signature s)
    {
        auto typeName = typeid(T).name();

        assert(m_Systems.find(typeName) != m_Systems.end() && "System is being used before registered");

        m_Signatures[typeName] = s;
    }

    void EntityDestroyed(entity id)
    {
        for (auto const &pair : m_Systems)
        {
            auto const &system = pair.second;
            system->m_Entities.erase(id);
        }
    }

    void ChangeEntitySignature(entity id, const signature &ett_sign)
    {

        // this must be iterate all system ->
        for (auto const &pair : m_Systems)
        {
            auto const &type = pair.first;
            auto const &system = pair.second;
            auto const &sign = m_Signatures[type];

            // check if entity match to system requirement
            // true -> added entity to system entity set
            // false -> this mean if the new sign do not match any system signature -> entity is no longer being
            // controlled by system -> remove entity from system entity set

            if ((ett_sign & sign) == sign)
            {
                system->m_Entities.insert(id);
            }
            //
            else
            {
                system->m_Entities.erase(id);
            }
        }
    }

  private:
    std::unordered_map<const char *, signature> m_Signatures;
    std::unordered_map<const char *, std::shared_ptr<System>> m_Systems;
};

} // namespace ecs