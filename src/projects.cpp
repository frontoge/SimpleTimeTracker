#include <project.hpp>
#include <chrono>

#include <iostream>

// using namespace std::chrono_literals;

Project::Project()
:Project("New Project")
{

}

Project::Project(const std::string& name)
:name(name)
{
    minutes = std::chrono::minutes(0);
}

void Project::setName(const std::string& value)
{
    this->name = value;
}

float Project::getMinutes() const
{
    return this->minutes.count() / 60.0f;
}

std::string Project::getName() const
{
    return this->name;
}

void Project::startTimer()
{
    std::cout << "Starting Timer\n";
    if (this->status) {
        return;
    }
    this->status = true;
    startTime = std::chrono::system_clock::now();
}

void Project::stopTimer()
{
    if (!this->status) {
        return;
    }

    auto stopTime = std::chrono::system_clock::now();
    const auto difference =  stopTime - startTime;
    this->minutes = std::chrono::duration_cast<std::chrono::minutes>(difference + this->minutes);
    std::cout << minutes.count() << "\n";
    this->status = false;
}
