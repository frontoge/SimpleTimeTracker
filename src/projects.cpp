#include <project.hpp>
#include <chrono>

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
    color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
}

Project::~Project()
{
    // Check if thread needs to be deleted
    if (thread == nullptr || !thread->joinable()) {
        return;
    }
    
    thread->join();

    delete thread;
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

void Project::updateTimer()
{
    const std::chrono::seconds startSeconds = seconds;
    while (status) 
    {
        auto currentTime = std::chrono::system_clock::now();
        const auto diff = currentTime - startTime;
        this->seconds = std::chrono::duration_cast<std::chrono::seconds>(startSeconds + diff);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


void Project::startTimer()
{
    if (this->status) {
        return;
    }
    this->status = true;
    startTime = std::chrono::system_clock::now();
    thread = new std::thread(&Project::updateTimer, this);
}

void Project::stopTimer()
{
    if (!this->status) {
        return;
    }

    this->status = false;
    this->thread->join();

    if (thread == nullptr) {
        return;
    }
    delete thread;
    thread = nullptr;
}
