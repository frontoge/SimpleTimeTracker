#include <iostream>
#include <manager.hpp>
#include <unistd.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace fs = std::filesystem;

using Path = fs::path;

bool isFilePresent(Path& filePath) {
    return fs::exists(filePath) && fs::is_regular_file(filePath);
}

int main()
{
    // Instantiate app manager
    Manager* manager = new Manager();

    // Create some path objects for our save files
    // Leaving this as non const because eventually user will be able to set save file name
    std::string saveDir = "data";
    std::string fileName = "projects.dat";
    Path savePath = fs::current_path() / saveDir / fileName;

    if (isFilePresent(savePath)) {
        std::ifstream ifs(savePath);
        boost::archive::text_iarchive ia(ifs);
        ia >> *manager;
        ifs.close();
    }

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

    manager->stopAll();

    // Create the save directory if it doesn't already exist
    if (!fs::exists(fs::current_path() / saveDir)) {
        fs::create_directory(saveDir);
    }

    std::ofstream ofs(savePath);
    boost::archive::text_oarchive oa(ofs);
    oa << *manager;
    ofs.close();

    delete manager;
    
    return 0;
}