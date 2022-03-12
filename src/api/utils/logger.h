#pragma once

#include <iostream>
#include <sstream>

namespace punkyoi_api::utils {

    class Logger {
    public:
        template<typename T>
        Logger& operator<<(const T& value) {
            m_stream << value;
            return *this;
        }

        static Logger console() {
            return Logger();
        }

        static struct LoggerFlush{} constexpr endl = LoggerFlush();

    private:
        std::stringstream m_stream;
    };

    template<>
    Logger& Logger::operator<< <Logger::LoggerFlush>(const Logger::LoggerFlush&) {
        std::cout << m_stream.str() << std::endl;
        m_stream.str("");
        return *this;
    }
}

namespace punkyoi_api {
    using log = punkyoi_api::utils::Logger;
}