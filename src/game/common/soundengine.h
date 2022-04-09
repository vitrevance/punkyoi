#ifndef P_SOUNDENGINE
#define P_SOUNDENGINE

#include <game/core.h>
#include <api/isoundengine.h>

namespace punkyoi::common {

    class SoundEngine : public ISoundEngine {
    public:
        SoundEngine(IAssetManager& manager) : m_assetManager(manager) {
        }

        virtual ~SoundEngine() = default;

        virtual void play(ISound& sound, float volume) override;
        virtual void play(const std::string& name);

    protected:
        IAssetManager& m_assetManager;
    }
}

#endif