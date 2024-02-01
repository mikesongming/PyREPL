#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "animal.h"

template<typename AnimalBase = Animal>
class PyAnimal: public AnimalBase {
public:
    using AnimalBase::AnimalBase;
    void show() const override {
        PYBIND11_OVERRIDE_PURE(void, AnimalBase, show);
    }
};

template<typename BarkBase>
class PyBark: public PyAnimal<BarkBase> {
public:
    using PyAnimal<BarkBase>::PyAnimal;
    void show() const override {
        PYBIND11_OVERRIDE(void, BarkBase, show);
    }
    std::string bark() const override {
        PYBIND11_OVERRIDE(std::string, BarkBase, bark);
    }
};


PYBIND11_MODULE(py_animal, m) {
    m.doc() = "Demo module for animals";

    /*
     * Animal, Dog, Cat, and Elephant are set with shared_ptr holder type to be compatible with World::add_animal()
    */
    py::class_<Animal, PyAnimal<>, std::shared_ptr<Animal>> animal(m, "Animal");
    animal.def(py::init<>())
        .def("show", &Animal::show)
        .def_readwrite("n_times", &Animal::n_times);

    py::class_<Dog, Animal, PyBark<Dog>, std::shared_ptr<Dog>> dog(m, "Dog");
    py::class_<Cat, Animal, PyBark<Cat>, std::shared_ptr<Cat>> cat(m, "Cat");
    py::class_<Elephant, Animal, PyBark<Elephant>, std::shared_ptr<Elephant>> elephant(m, "Elephant");

    dog.def(py::init<>())
        .def("bark", &Dog::bark);

    cat.def(py::init<>())
        .def("bark", &Cat::bark);

    elephant.def(py::init<>())
        .def("bark", &Elephant::bark);
}