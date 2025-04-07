#pragma once

#include <vector>
#include <project.hpp>
#include <ostream>
#include <boost/serialization/vector.hpp>

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
         * @brief Creates a new project.
         * 
         * @param project - The project to add.
         */
        void addProject(Project* project)
        {
            this->projects.push_back(project);
        }

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

        /**
         * @brief Saves the projects to a file.
         * 
         * @param filename - The name of the file to save to.
         */
        void saveProjects();

        /**
         * @brief Loads the projects from a file.
         * 
         * @param filename - The name of the file to load from.
         */
        void loadProjects();

        /**
         * @brief Gets the project at the given index.
         * 
         * @param index - The index of the project to get.
         * @return Project* - The project at the given index.
         */
        Project* getProject(int index) const
        {
            if (index < 0 || index >= static_cast<int>(projects.size())) {
                return nullptr;
            }
            return projects[index];
        }

        /**
         * @brief Gets the number of projects.
         * 
         * @return int - The number of projects.
         */
        const int getProjectCount() const
        {
            return static_cast<int>(projects.size());
        }

        /**
         * @brief Sets the manager to know there is unsaved changes.
         * 
         */
        void markChanges()
        {
            this->unsavedChanges = true;
        }

        /**
         * @brief Checks if there are unsaved changes.
         * 
         * @return true 
         * @return false 
         */
        bool hasUnsavedChanges() const
        {
            return this->unsavedChanges;
        }
        
    private:
        std::vector<Project*> projects;
        friend class boost::serialization::access;
        std::string saveDir;
        std::string fileName;
        bool unsavedChanges;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar & projects;
        }
};