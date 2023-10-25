#include <bits/stdc++.h>
#include <bitset>
#include <cstdint>

namespace ecs
{

using entity = uint32_t;
const entity MAX_ENTT = 1000;
using componentId = uint32_t;

using componentType = std::uint8_t;
const componentType MAX_COMPONENTS = 32;

using signature = std::bitset<MAX_COMPONENTS>;

} // namespace ecs
