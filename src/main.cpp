#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <ui_manager.hpp>

int main(int argc, char** argv)
{
    // Instantiate app manager
    Manager* manager = new Manager();
    // Instantiate UI manager
    UIManager* uiManager = new UIManager(manager);

    // Init UI
    if (!uiManager->init()) {
        std::cerr << "Failed to initialize UI manager\n";
        return -1;
    }

    manager->loadProjects();

    while (!uiManager->shouldWindowClose())
    {
        uiManager->render();
    }

    manager->stopAll();

    delete manager;
    delete uiManager;
    
    return 0;
}