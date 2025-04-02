#pragma once

#include <vector>
#include <project.hpp>
#include <ostream>

class Manager 
{
    public:
        Manager();
        ~Manager();

        /**
         * @brief Displays a list of projects and time spent to a given output stream.
         * 
         * @param out The output stream to use.
         */
        void listProjects(std::ostream& out);

        /**
         * @brief Starts a project timer.
         * 
         * @param index The index of the project to start.
         */
        void toggleProject(int index);

        /**
         * @brief Creates a new project with name.
         * 
         * @param name - The name of the project.
         */
        void addProject(const std::string& name);

        /**
         * @brief Deletes a project.
         * 
         * @param index - The index of the project to delete.
         */
        void deleteProject(int index);

        /**
         * @brief Stops all timers that are currently running.
         * 
         */
        void stopAll();

        /**
         * @brief Checks if an index is a valid project.
         * 
         * @param index - The index to check.
         * @return true The index is valid.
         * @return false The index is invalid.
         */
        bool isValidIndex(int index) const;
        
    private:
        std::vector<Project*> projects;
};