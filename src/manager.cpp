#include <manager.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
using Path = fs::path;

bool isFilePresent(Path& filePath) {
    return fs::exists(filePath) && fs::is_regular_file(filePath);
}

Manager::Manager()
{
    saveDir = "data";
    fileName = "projects.dat";
    projects.push_back(new Project("New Project"));
    unsavedChanges = false;
}

Manager::~Manager()
{
    for (auto proj : this->projects) {
        delete proj;
    }
}

void Manager::listProjects(std::ostream& out)
{
    for (auto i = 0; i != this->projects.size(); i++)
    {
        auto& proj = this->projects[i];
        out << i + 1 << ". " << proj->getName() << " - " << proj->getMinutes() << " minutes\n";
    }
}

void Manager::toggleProject(int index)
{
    if (index < 0 || index >= this->projects.size()) {
        return;
    }
    
    auto& proj = this->projects.at(index);
    if (proj->getStatus()) {
        proj->stopTimer();
    } else {
        proj->startTimer();
    }
}

void Manager::deleteProject(int index)
{
    if (index < 0 || index >= this->projects.size()) {
        return;
    }

    // This might not be good idea.
    delete this->projects.at(index);
    this->projects.erase(this->projects.begin() + index);
}

void Manager::stopAll()
{
    for (auto& proj : this->projects) {
        proj->stopTimer();
    }
}

bool Manager::isValidIndex(int index) const
{
    return index >= 0 && index < this->projects.size();
}

void Manager::saveProjects()
{
    Path savePath = fs::current_path() / saveDir / fileName;

    // Create the save directory if it doesn't already exist
    if (!fs::exists(fs::current_path() / saveDir)) {
        fs::create_directory(saveDir);
    }

    std::ofstream ofs(savePath);
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
    ofs.close();

    this->unsavedChanges = false;
}

void Manager::loadProjects()
{
    Path savePath = fs::current_path() / saveDir / fileName;

    if (isFilePresent(savePath)) {
        std::ifstream ifs(savePath);
        boost::archive::text_iarchive ia(ifs);
        ia >> *this;
        ifs.close();
    }
}