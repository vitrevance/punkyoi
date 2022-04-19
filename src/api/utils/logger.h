#ifndef P_LOGGER
#define P_LOGGER

#include <iostream>
#include <sstream>

namespace punkyoi_api::utils {

    struct LoggerFlush{};

    class Logger {
    public:
        inline Logger& operator<<(const LoggerFlush& value) {
            std::cout << m_stream.str() << std::endl;
            m_stream.str("");
            return *this;
        }
        
        template<typename T>
        inline Logger& operator<<(const T& value) {
            m_stream << value;
            return *this;
        }

        static Logger console() {
            return Logger();
        }

        static LoggerFlush constexpr endl = LoggerFlush();

    private:
        std::stringstream m_stream;
    };
}

namespace punkyoi_api {
    using log = punkyoi_api::utils::Logger;
}

#endif
