#ifndef P_ISOUNDENGINE
#define P_ISOUNDENGINE

#include <api/iassetmanager.h>
#include <api/isound.h>

namespace punkyoi_api {

    class ISoundEngine {
    public:
        virtual ~ISoundEngine() = default;
        virtual void playSound(ISound&, float volume) = 0;
    };
}

#endif