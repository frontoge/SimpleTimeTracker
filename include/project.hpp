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
        /**
         * @brief Set the Name of the project
         * 
         * @param value - The string to set as the name.
         */
        void setName(const std::string& value);

        //Accessors
        /**
         * @brief Get the number of minutes spent on this project.
         * 
         * @return float The number of minutes spent on this project.
         */
        float getMinutes();

        /**
         * @brief Get the Name of the project
         * 
         * @return std::string - The name of the project
         */
        std::string getName();


        /**
         * @brief Get the status of the timer
         * 
         * @return true - The timer is running.
         * @return false - The timer is not running.
         */
        bool getStatus();

        /**
         * @brief Starts the timer for the given project.
         * 
         */
        void startTimer();

        /**
         * @brief Stops the timer for the given project.
         * 
         */
        void stopTimer();

    private:
        std::chrono::minutes minutes;
        std::string name;
        Timestamp startTime;
        bool status;

};
