#pragma once

#include <string>
#include <chrono>

// Serialization
// TODO rebuild the boost serialization lib and only build serialization (use --with-serialization)
// This will give all headers required internally, right now dependencies are all fucked up.
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp> 

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
        float getMinutes() const;

        /**
         * @brief Get the Name of the project
         * 
         * @return std::string - The name of the project
         */
        std::string getName() const;


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
        // Serialization
        friend class boost::serialization::access; 

        template<class Archive>
        void save(Archive& ar, const unsigned int version) const
        {
            ar & name;
            ar & minutes.count();
        }

        template<class Archive>
        void load(Archive& ar, const unsigned int version) 
        {
            ar & name;
            int minutesCount;
            ar & minutesCount;
            minutes = std::chrono::minutes(static_cast<int>(minutesCount));
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

        std::chrono::minutes minutes;
        std::string name;
        Timestamp startTime;
        bool status;

};

