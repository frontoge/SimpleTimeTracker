#include <iostream>
#include <project.hpp>
#include <unistd.h>

int main()
{
    Project* test = new Project("Test");
    std::cout << test->getName() << ": " << test->getMinutes() << "\n";
    test->startLogging();
    sleep(60);
    test->stopLogging();
    return 0;
}