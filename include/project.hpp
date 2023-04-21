#pragma once

#include <string>
#include <chrono>

using Clock = std::chrono::system_clock;
using Timestamp = std::chrono::time_point<Clock>;


class Project 
{
    public:
        Project();
        Project(const std::string& name);

        //Mutators
        void setName(const std::string& value);

        //Accessors
        float getMinutes();
        std::string getName();
        bool getLogging();

        void startLogging();
        void stopLogging();

    private:
        std::chrono::minutes minutes;
        std::string name;
        Timestamp startTime;

};
