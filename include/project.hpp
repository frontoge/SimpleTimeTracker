#pragma once

#include <string>
#include <chrono>
// Serialization
// TODO rebuild the boost serialization lib and only build serialization (use --with-serialization)
// This will give all headers required internally, right now dependencies are all fucked up.
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp> 

#include <thread>

#include <imgui.h>

using Clock = std::chrono::system_clock;
using Timestamp = std::chrono::time_point<Clock>;

class Project 
{
    public:
        Project();
        Project(const std::string& name);
        ~Project();

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
        int getMinutes() const;

        /**
         * @brief Get the number of seconds spent on this project.
         * 
         * @return float The number of seconds spent on this project.
         */
        int getSeconds() const;

        /**
         * @brief Get the number of hours spent on this project.
         * 
         * @return float The number of hours spent on this project.
         */
        int getHours() const;

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
        bool getStatus() const;

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

        /**
         * @brief Get the color of the project
         * 
         * @return ImVec4 - The color of the project
         */
        const ImVec4& getColor() const
        {
            return color;
        }

        /**
         * @brief Set the color of the project
         * 
         * @param value - The color to set.
         */
        void setColor(const ImVec4& value)
        {
            color = value;
        }

    private:
        void updateTimer();

        // Serialization
        friend class boost::serialization::access; 

        template<class Archive>
        void save(Archive& ar, const unsigned int version) const
        {
            ar & name;
            ar & seconds.count();
            ar & color.x & color.y & color.z & color.w;
        }

        template<class Archive>
        void load(Archive& ar, const unsigned int version) 
        {
            int minutesCount;

            ar & name;
            ar & minutesCount;
            ar & color.x & color.y & color.z & color.w;
            seconds = std::chrono::seconds(static_cast<int>(minutesCount));
        }
        BOOST_SERIALIZATION_SPLIT_MEMBER()

        std::chrono::seconds seconds;
        std::string name;
        Timestamp startTime;
        std::thread* thread;
        bool status;
        ImVec4 color;

};

