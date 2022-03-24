#ifndef P_EXCEPTION
#define P_EXCEPTION

#include <string>
#include <exception>
#include <sstream>

namespace punkyoi::common::exceptions {

    class GameException : public std::exception {
    public:
        GameException() : m_error_message("Game Exception") {}
        virtual ~GameException() = default;

        virtual const char* what() const throw () {
            return m_error_message.c_str();
        }

    protected:
        std::string m_error_message;
    };

    #define CLASS_BASIC_EXCEPTION(NAME, TEXT)                                   \
    class NAME : public GameException {                                         \
        public: template<typename...Args>                                       \
        NAME (Args...args) {                                                    \
            m_error_message = TEXT;                                             \
            fill(args...);                                                      \
        }                                                                       \
        virtual ~NAME() = default;                                              \
    private:                                                                    \
        template <typename S, typename...Args>                                  \
        void fill(S first, Args... args) {                                      \
            static_assert(std::is_convertible<S, std::string>::value,           \
                "GameException constructor args must convert to std::string");  \
            replace(first);                                                     \
            fill(args...);                                                      \
        }                                                                       \
        inline void fill() {}                                                   \
        inline void replace(const std::string& text) {                          \
            m_error_message.replace(m_error_message.find("%"), 1, text);        \
        }                                                                       \
    };                                                                          \

    CLASS_BASIC_EXCEPTION(NoAssetException, "Asset with name <%> does not exist!")
    CLASS_BASIC_EXCEPTION(RuntimeException, "%")
    CLASS_BASIC_EXCEPTION(BadAssetFormatException, "Bad asset format! %")
    CLASS_BASIC_EXCEPTION(DuplicateAssetException, "Duplicate asset <%>")
    CLASS_BASIC_EXCEPTION(MissingAssetFileException, "Missing asset file for <%>")
}

#endif