#include <iostream>
#include <manager.hpp>
#include <unistd.h>

int main()
{
    Manager* manager = new Manager();
    manager->listProjects(std::cout);
    return 0;
}