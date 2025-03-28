#include <manager.hpp>

Manager::Manager()
{
    this->projects.push_back(Project("Project 1"));
    this->projects.push_back(Project("Project 2"));
    this->projects.push_back(Project("Project 3"));
    this->projects.push_back(Project("Project 4"));
    this->projects.push_back(Project("Project 5"));
}

void Manager::listProjects(std::ostream& out)
{
    for (const Project& proj : this->projects)
    {
        out << proj.getName() << " - " << proj.getMinutes() << " minutes\n";
    }
}