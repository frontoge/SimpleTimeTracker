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
    this->status = false;
    seconds = std::chrono::minutes(0);
}

void Project::setName(const std::string& value)
{
    this->name = value;
} 

int Project::getHours() const
{
    return this->seconds.count() / 3600;
}

int Project::getMinutes() const
{
    return this->seconds.count() / 60 - (this->getHours() * 60);
}

int Project::getSeconds() const
{
    return this->seconds.count() - (this->getMinutes() * 60);
}

std::string Project::getName() const
{
    return this->name;
}

bool Project::getStatus() const
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
    this->seconds = std::chrono::duration_cast<std::chrono::seconds>(difference + this->seconds);
    this->status = false;
}
