#pragma once

#include <vector>
#include <project.hpp>
#include <ostream>

class Manager 
{
    public:
        Manager();

        /**
         * @brief Displays a list of projects and time spent to a given output stream.
         * 
         * @param out The output stream to use.
         */
        void listProjects(std::ostream& out);

    private:
        std::vector<Project> projects;
};