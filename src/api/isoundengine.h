#ifndef P_ISOUNDENGINE
#define P_ISOUNDENGINE

#include <api/iassetmanager.h>

namespace punkyoi_api {

    class ISound {
    public:
        virtual ~ISound() = default;
        virtual const std::string& source() = 0;
        virtual void* getBuffer() = 0;
    };

    class ISoundEngine {
    public:
        virtual ~ISoundEngine() = default;
        virtual void playSound(ISound&, float volume) = 0;
    };
}

#endif