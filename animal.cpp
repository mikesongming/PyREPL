#include "animal.h"

#include <iostream>

void Dog::show() const
{
    std::string bark_str;
    for (size_t i = 0; i < n_times; i++)
    {
        bark_str += bark();
    }

    std::cout << "\t" << "I am a dog, " << std::endl;
    std::cout << "\t\t" << bark_str << std::endl;
}

std::string Dog::bark() const
{
    return "Woof!";
}

void Cat::show() const
{
    std::string bark_str;
    for (size_t i = 0; i < n_times; i++)
    {
        bark_str += bark();
    }

    std::cout << "\t" << "I am a cat, " << std::endl;
    std::cout << "\t\t" << bark_str << std::endl;
}

std::string Cat::bark() const
{
    return "Meow!";
}

void Elephant::show() const
{
    std::string bark_str;
    for (size_t i = 0; i < n_times; i++)
    {
        bark_str += bark();
    }

    std::cout << "\t" <<"I am an elephant, " << std::endl;
    std::cout << "\t\t" << bark_str << std::endl;
}

std::string Elephant::bark() const
{
    return "Trumpet!";
}