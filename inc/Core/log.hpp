// There must be a log folder for this to work!
#pragma once

#include <cstdint>
#include <ctime>
#include <fstream>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
namespace Core
{
    class Log
    {
      public:
        enum Level : uint8_t
        {
            Trace,
            Debug,
            Info,
            Warn,
            Error,
            Fatal
        } level;

      private:
        const std::string path = "../../log/";
        std::ofstream fout;
        const std::time_t m_startTime;
        sf::Clock clock;

      public:
        // @brief Deafult constructer
        // @param Logging detail level (Default Info)
        Log(Level level = Info)
            : level(level), m_startTime(std::time(nullptr))
        {
            char title[sizeof("yyyy-mm-dd hh:mm:ss")];
            std::strftime(title, sizeof(title), "%F %T", std::localtime(&m_startTime));
            fout.open(path + title + ".txt");
        }

        ~Log()
        {
            fout.close();
        }

        void trace(const std::string& s)
        {
            if (level <= Trace) fout << time_stamp() << " [Trace]: " << s << '\n';
            fout.flush();
        }

        void debug(const std::string& s)
        {
            if (level <= Debug) fout << time_stamp() << " [Debug]: " << s << '\n';
            fout.flush();
        }

        void info(const std::string& s)
        {
            if (level <= Info) fout << time_stamp() << " [Info]: " << s << '\n';
            fout.flush();
        }

        void warn(const std::string& s)
        {
            if (level <= Warn) fout << time_stamp() << " [Warn]: " << s << '\n';
            fout.flush();
        }

        void error(const std::string& s)
        {
            if (level <= Error) fout << time_stamp() << " [Error]: " << s << '\n';
            fout.flush();
        }

        void fatal(const std::string& s)
        {
            if (level <= Fatal) fout << time_stamp() << " [Fatal]: " << s << '\n';
            fout.flush();
        }

      private:
        // @brief Gives the elapsed time from the instantiation of log with "mm-ss" format
        std::string time_stamp()
        {
            sf::Time time = clock.getElapsedTime();
            float s = time.asSeconds();
            int32_t ms = time.asMilliseconds();
            int64_t us = time.asMicroseconds();

            std::string string = std::to_string((int)s) + ":" +
                                 std::to_string(ms % 1000) + ":" +
                                 std::to_string(us % 1000);
            // const std::time_t currentTime = std::time(nullptr);
            // char s[sizeof("mm:ss")];
            // auto diff = currentTime - m_startTime;
            // std::strftime(s, sizeof(s), "%M:%S", std::localtime(&diff));

            return string;
        }
    } logger;
} // namespace Core