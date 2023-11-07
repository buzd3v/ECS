#include "ECS/ecs.h"
#include "Testing/test.h"
#include <algorithm>
#include <chrono>
#include <ostream>
#include <random>
#include <stdio.h>

struct Vec3
{
    float x, y, z;
};

struct Gravity
{
    Vec3 force;
};

struct RigidBody
{
    float x, y;
};

struct Transform
{
    float x, y, z;
};

ecs::Ecs g_Ecs;

class PhysicSystem : public ecs::System
{
  public:
    void Update(float deltaTime)
    {
        for (auto id : m_Entities)
        {
            auto &[x, y] = g_Ecs.GetComponent<RigidBody>(id);
            x += 1;
            y += 1;
            std::cout << id << ": "
                      << "velocity: " << x << " acceleration: " << y << std::endl;
        }
    }
};

class RenderSystem : public ecs::System
{
  public:
    void Update(float deltaTime)
    {
        for (auto id : m_Entities)
        {
            auto &[x, y, z] = g_Ecs.GetComponent<Transform>(id);
            auto &[vec, acc] = g_Ecs.GetComponent<RigidBody>(id);
            printf("id:%d x:%f y:%f z:%f\n", id, x, y, z);
        }
    }
};

void passSomething(int &&x)
{
    std::cout << " Do something \n";
    x += 1;
}

int main()
{
    // g_Ecs.Init();
    // g_Ecs.RegisterComponent<RigidBody>();
    // g_Ecs.RegisterComponent<Transform>();

    // auto renderSys = g_Ecs.RegisterSystem<RenderSystem>();

    // ecs::signature sign;
    // sign.set(g_Ecs.GetComponentType<RigidBody>());
    // sign.set(g_Ecs.GetComponentType<Transform>());

    // g_Ecs.SetSystemSignature<RenderSystem>(sign);

    // std::vector<ecs::entity> v(10);

    // std::default_random_engine generator;
    // std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
    // std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
    // std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
    // std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

    // for (auto &id : v)
    // {
    //     id = g_Ecs.CreateEntity();
    //     g_Ecs.AddComponentToEntity<RigidBody>(id, {randGravity(generator), randPosition(generator)});
    //     g_Ecs.AddComponentToEntity<Transform>(id, {1, 2, 3});
    // }
    // float dt = 0;

    // while (true)
    // {
    //     auto startTime = std::chrono::high_resolution_clock::now();

    //     renderSys->Update(dt);

    //     auto stopTime = std::chrono::high_resolution_clock::now();

    //     dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    // }
}