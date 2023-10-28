#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

class family
{
    static std::size_t identifier() noexcept
    {
        static std::size_t value = 0;
        return value++;
    }

  public:
    template <typename> static std::size_t type() noexcept
    {
        static const std::size_t value = identifier();
        return value;
    }
};

class IComponent
{
  public:
    IComponent(){};
    virtual size_t getTypeID()
    {
        return -1;
    };
    virtual ~IComponent(){};
};
class Rotate : public IComponent
{
  public:
    Rotate()
    {
        family::type<Rotate>();
    }
    size_t getTypeID() override
    {
        return family::type<Rotate>();
    }
};
class Transform : public IComponent
{
  public:
    Transform()
    {
        family::type<Transform>();
        std::cout << "Transform typeid = " << family::type<Transform>() << std::endl;
    }
    size_t getTypeID() override
    {
        return family::type<Transform>();
    }
    int a, b, c;
};

class RigidBody : public IComponent
{
  public:
    RigidBody()
    {
        family::type<RigidBody>();
        std::cout << "Rigidbody typeid = " << family::type<RigidBody>() << std::endl;
    }
    size_t getTypeID() override
    {
        return family::type<RigidBody>();
    }
    int a, b;
};

class Object
{
  public:
    Object(){};

    template <typename T> bool isHasComponent()
    {
        for (auto com : m_components)
        {
            auto t = dynamic_cast<T *>(com);
            if (t != nullptr)
            {
                if (family::type<T>() == t->getTypeID())
                {
                    return true;
                }
            }
        }
        return false;
    }

    void SetComponents(std::vector<IComponent *> &components)
    {
        for (auto &com : components)
        {
            m_components.push_back(com);
        }
    }
    template <typename T> T &get()
    {
        auto t = dynamic_cast<T *>(m_components[family::type<T>()]);

        if (t != nullptr)
        {
            return *t;
        }
        else
        {
            std::cout << "Cannot convert type" << std::endl;
        }
        return T();
    }
    std::vector<IComponent *> m_components;

  private:
};
