#include <iostream>
#include <manager.hpp>
#include <unistd.h>
#include <string>

int main()
{
    Manager* manager = new Manager();
    char input = '0';
    while (input != 'q')
    {
        system("clear");
        std::cout << "Simple Time Tracker\n";
        std::cout << "0. New Project\n";
        manager->listProjects(std::cout);
        std::cout << "q to quit\n";

        input = std::getchar();
        std::cin.ignore(100, '\n');

        if (input == '0') {
            std::cout << "Enter project name: \n";
            std::string name;
            std::getline(std::cin, name);

            manager->addProject(name);
            std::cout << "Added project: " << name << "\n";
            system("clear");
        }
        else if (input == 'q') {
            std::cout << "Quitting...\n";
            manager->stopAll();
            // TODO save state
            //manager->saveState();
            delete manager;
        } else {
            // Go back 49 to offset our menu (1 = 0, 2 = 1, etc)
            int index = static_cast<int>(input) - 49;
            if (manager->isValidIndex(index)) 
            {
                manager->toggleProject(index);
                std::cout << "Toggled project: " << index + 1 << "\n";
            } else {
                std::cout << "Invalid project index\n";
            }
            sleep(1);
        }
    }
    
    return 0;
}