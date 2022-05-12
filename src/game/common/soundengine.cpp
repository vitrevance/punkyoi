#define MINIAUDIO_IMPLEMENTATION
#include "soundengine.h"

namespace punkyoi::common {

    SoundEngine::SoundEngine(AssetManager& manager) : m_assetManager(manager) {
        m_engine = ma_engine();
        ma_result result;

        result = ma_engine_init(NULL, &m_engine);
        if (result != MA_SUCCESS) {
            throw exceptions::RuntimeException("Failed to initisize sound engine!");
        }
    }

    SoundEngine::~SoundEngine() {
        for (auto& sound : m_waste) {
            ma_sound_uninit(sound.get());
        }
        ma_engine_uninit(&m_engine);
    }

    void SoundEngine::playSound(punkyoi_api::ISound& isound, float volume) {
        std::shared_ptr<ma_sound> sound = std::make_shared<ma_sound>();
        ma_result result;
        result = ma_sound_init_from_file(&m_engine, isound.source().c_str(), 0, NULL, NULL, sound.get());
        if (result != MA_SUCCESS) {
            throw exceptions::RuntimeException("Failed to load sound!");
        }
        ma_sound_set_volume(sound.get(), volume);
        ma_sound_start(sound.get());
        m_waste.push_back(sound);
    }

    void SoundEngine::playSound(const std::string& name, float volume, bool loop) {
        std::shared_ptr<ma_sound> sound;
        SoundAsset& asset = m_assetManager.getSound(name);
        if (!m_library.count(asset.uid)) {
            sound = sound = std::make_shared<ma_sound>();
            ma_result result;
            result = ma_sound_init_from_file(&m_engine, asset.source().c_str(), MA_SOUND_FLAG_DECODE, NULL, NULL, sound.get());
            if (result != MA_SUCCESS) {
                throw exceptions::RuntimeException("Failed to load sound!");
            }
            m_waste.push_back(sound);
            m_library[asset.uid] = sound;
        }
        else {
            sound = m_library[asset.uid];
            ma_sound_seek_to_pcm_frame(sound.get(), 0);
        }
        ma_sound_set_volume(sound.get(), volume);
        ma_sound_set_looping(sound.get(), loop);
        ma_sound_start(sound.get());
    }

    bool SoundEngine::isSoundPlaying(const std::string& name) {
        SoundAsset& asset = m_assetManager.getSound(name);
        if (!m_library.count(asset.uid)) {
            return false;
        }
        return ma_sound_is_playing(m_library[asset.uid].get());
    }

    void SoundEngine::stopSound(const std::string& name) {
        SoundAsset& asset = m_assetManager.getSound(name);
        if (m_library.count(asset.uid)) {
            ma_sound_stop(m_library[asset.uid].get());
        }
    }
}