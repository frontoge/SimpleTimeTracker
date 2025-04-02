#include <project.hpp>
#include <chrono>

#include <iostream>

// using namespace std::chrono_literals;

Project::Project()
:Project("New Project")
{
    this->status = false;
    this->minutes = std::chrono::minutes(0);
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
    return this->minutes.count();
}

std::string Project::getName() const
{
    return this->name;
}

bool Project::getStatus()
{
    return this->status;
}

void Project::startTimer()
{
    if (this->status) {
        return;
    }
    std::cout << "Starting Timer\n";
    this->status = true;
    startTime = std::chrono::system_clock::now();
}

void Project::stopTimer()
{
    if (!this->status) {
        return;
    }

    std::cout << "Stopping Timer\n";

    auto stopTime = std::chrono::system_clock::now();
    const auto difference =  stopTime - startTime;
    this->minutes = std::chrono::duration_cast<std::chrono::minutes>(difference + this->minutes);
    this->status = false;
}
