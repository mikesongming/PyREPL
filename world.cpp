#include "world.h"

std::shared_ptr<World> Context::addWorld(const std::string &name)
{
    if (_worlds.find(name) == _worlds.end())
    {
        _worlds[name] = World::create(name);
    }
    return _worlds[name];
}

void Context::removeWorld(const std::string &name) {
    _worlds.erase(name);
}

std::shared_ptr<World> Context::getWorld(const std::string &name) const
{
    auto it = _worlds.find(name);
    if (it == _worlds.end())
    {
        return nullptr;
    }
    return it->second;
}

std::shared_ptr<World> Context::getCurrentWorld() const
{
    if (_worlds.find(_current_name) == _worlds.end())
    {
        return nullptr;
    } else {
        return getWorld(_current_name);
    }
}

bool Context::setCurrentWorld(const std::string &name)
{
    if (_worlds.find(name) == _worlds.end())
    {
        return false;
    } else {
        _current_name = name;
        return true;
    }
}

void World::removeAnimal(std::shared_ptr<Animal> animal)
{
    auto it = std::find(animals.begin(), animals.end(), animal);
    if (it != animals.end())
    {
        animals.erase(it);
    }
}

void World::showAnimals(const std::string &stage) const
{
    std::cout << "Stage: " << stage << ", "
              << "Animals in " << name << ":\n";
    for (const auto &animal : animals)
    {
        animal->show();
    }
}
