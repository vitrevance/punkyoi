#ifndef P_SOUNDENGINE
#define P_SOUNDENGINE

#include <game/core.h>
#include <map>
#include <api/isoundengine.h>
#include <game/common/exception.h>
#include <game/common/assetmanager.h>
#include <miniaudio.h>

namespace punkyoi::common {

    class SoundEngine : public punkyoi_api::ISoundEngine {
    public:
        SoundEngine(AssetManager& manager);

        virtual ~SoundEngine();

        virtual void playSound(punkyoi_api::ISound& sound, float volume) override;
        virtual void playSound(const std::string& name, float volume);

    protected:
        AssetManager& m_assetManager;
        ma_engine m_engine;
        std::map<uint32_t, ma_sound> m_library;
        std::vector<ma_sound> m_waste;
    };
}

#endif