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
        for (ma_sound& sound : m_waste) {
            ma_sound_uninit(&sound);
        }
        ma_engine_uninit(&m_engine);
    }

    void SoundEngine::playSound(punkyoi_api::ISound& isound, float volume) {
        ma_sound sound;
        ma_result result;
        result = ma_sound_init_from_file(&m_engine, isound.source().c_str(), 0, NULL, NULL, &sound);
        if (result != MA_SUCCESS) {
            throw exceptions::RuntimeException("Failed to load sound!");
        }
        ma_sound_set_volume(&sound, volume);
        ma_sound_start(&sound);
        m_waste.push_back(sound);
    }

    void SoundEngine::playSound(const std::string& name, float volume) {
        ma_sound sound;
        SoundAsset& asset = m_assetManager.getSound(name);
        if (!m_library.count(asset.uid)) {
            ma_result result;
            log::console() << asset.source().c_str() << log::endl;
            result = ma_sound_init_from_file(&m_engine, asset.source().c_str(), MA_SOUND_FLAG_DECODE, NULL, NULL, &sound);
            if (result != MA_SUCCESS) {
                throw exceptions::RuntimeException("Failed to load sound!");
            }
            m_waste.push_back(sound);
        }
        else {
            sound = m_library[asset.uid];
            ma_sound_seek_to_pcm_frame(&sound, 0);
        }
        
        ma_sound_set_volume(&sound, volume);
        ma_sound_start(&sound);
    }
}