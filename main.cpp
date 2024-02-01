#include <pybind11/embed.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;
using namespace py::literals;

#include "world.h"

// BINDING CODE

PYBIND11_MAKE_OPAQUE(std::vector<std::shared_ptr<Animal>>);

/*
 * PYBIND11_EMBEDDED_MODULE add the world module as built-in to the embedded interpreter.
 */
PYBIND11_EMBEDDED_MODULE(py_world, m) {
    m.doc() = "pybind11 example plugin, world of animals"; // optional module docstring

    pybind11::bind_vector<std::vector<std::shared_ptr<Animal>>>(m, "Animals");

    py::class_<World, std::shared_ptr<World>>(m, "World")
        .def(py::init<>())
        .def_readwrite("name", &World::name)
        .def_readonly("animals", &World::animals)
        .def_static("create", &World::create)
        .def("add_animal", &World::addAnimal)
        .def("remove_animal", &World::removeAnimal)
        .def("show_animals", &World::showAnimals, py::arg("stage")="Test")
        .def("get_raw_address",[](World &w){ return reinterpret_cast<uint64_t>(&w);});

    py::class_<Context, std::shared_ptr<Context>>(m, "Context")
        .def(py::init<>())
        .def("add_world", &Context::addWorld)
        .def("get_world", &Context::getWorld)
        .def("remove_world", &Context::removeWorld)
        .def_property("current_world", &Context::getCurrentWorld, &Context::setCurrentWorld);
}

class Application {
public:
    Application() {
        std::cout << "Creating Application..." << std::endl;

        context = std::make_shared<Context>();
    }

    void run() {
        std::cout << "Running Application..." << std::endl;

        auto world =context->addWorld("Example");
        context->setCurrentWorld("Example");
        assert(world != nullptr);

        auto dog = std::make_shared<Dog>();
        context->getCurrentWorld()->addAnimal(dog);
        context->getCurrentWorld()->showAnimals("before running Python REPL");

        {
            // call Python REPL here
            py::scoped_interpreter guard{};
            try {
                py::module_ repl = py::module_::import("repl");
                auto REPL = repl.attr("REPL");
                REPL.attr("run_with_context")("context"_a = context);
            } catch(const py::error_already_set& e) {
                std::cerr << '\n' << e.what() << '\n';
            }
        }

        context->getCurrentWorld()->showAnimals("after running Python REPL");
    }

    std::shared_ptr<Context> context;
};


int main() {
    Application app;
    app.run();
}