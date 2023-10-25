#include "ecs.h"
#include <array>
#include <cstddef>
#include <unordered_map>

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
  private:
    std::array<T, MAX_ENTT> m_ComponentArray;

    std::unordered_map<entity, size_t> m_EnttToIndexMap;
    std::unordered_map<size_t, entity> m_IndexToEnttMap;
};
} // namespace ecs