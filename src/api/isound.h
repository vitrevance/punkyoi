#ifndef P_ISOUND
#define P_ISOUND

#include <string>

namespace punkyoi_api {

    class ISound {
    public:
        virtual ~ISound() = default;
        virtual const std::string& source() const = 0;
        virtual void* getBuffer() = 0;
    };
}

#endif