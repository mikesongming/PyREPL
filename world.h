#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

#include "animal.h"

struct World;

class Context {
public:
    Context() = default;
    ~Context() = default;

    std::shared_ptr<World> addWorld(const std::string &name);

    void removeWorld(const std::string &name);

    std::shared_ptr<World> getWorld(const std::string &name) const;

    std::shared_ptr<World> getCurrentWorld() const;

    bool setCurrentWorld(const std::string &name);

private:
    std::map<std::string, std::shared_ptr<World>> _worlds;
    std::string _current_name;
};

struct World {
    explicit World(const std::string &name = "EARTH") : name(name) {};
    ~World() = default;

    static std::shared_ptr<World> create(const std::string &name) {
        return std::make_shared<World>(name);
    }

    void addAnimal(std::shared_ptr<Animal> animal) {
        animals.push_back(animal);
    }

    void removeAnimal(std::shared_ptr<Animal> animal);

    void showAnimals(const std::string &stage) const;

    std::string name;
    std::vector<std::shared_ptr<Animal>> animals;
};
