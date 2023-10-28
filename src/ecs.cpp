#include "ecs.h"
#include "Object.h"
#include <algorithm>
#include <ostream>

int main()
{
    IComponent *rr = new RigidBody();
    IComponent *rc = new Transform();

    std::vector<IComponent *> v(2);
    v[family::type<RigidBody>()] = rr;
    v[family::type<Transform>()] = rc;

    Object o;
    o.SetComponents(v);
    std::cout << o.isHasComponent<Rotate>() << std::endl;
    auto pos = o.get<Transform>();
}