#include <manager.hpp>
#include <iostream>

Manager::Manager()
{
    
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
    std::cout << index << "\n";
    auto& proj = this->projects.at(index);
    if (proj->getStatus()) {
        proj->stopTimer();
    } else {
        proj->startTimer();
    }
}

void Manager::addProject(const std::string& name)
{
    this->projects.push_back(new Project(name));
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
