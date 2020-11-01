#include "AudioManager.h"

namespace projectz {
    namespace game {
        AudioManager* AudioManager::s_pInstance = nullptr;

        AudioManager::AudioManager()
            : m_soundOn(true)
        {}


        void AudioManager::ToggleSound()
        {
            m_soundOn = !m_soundOn;
        }

        bool AudioManager::IsSoundOn()
        {
            return m_soundOn;
        }

        AudioManager* AudioManager::GetInstance()
        {
            if (s_pInstance == nullptr)
            {
                s_pInstance = new AudioManager();
            }
            return s_pInstance;
        }

        void AudioManager::DestroyInstance()
        {
            delete s_pInstance;
            s_pInstance = nullptr;
        }

        void AudioManager::PlayDoorClosedSound()
        {
            // Beep(frequency, duration)
            if (m_soundOn)
            {
                Beep(500, 75);
                Beep(500, 75);
            }
        }

        void AudioManager::PlayDoorOpenSound()
        {
            if (m_soundOn)
            {
                Beep(1397, 200);
            }
        }

        void AudioManager::PlayKeyPickupSound()
        {
            if (m_soundOn)
            {
                Beep(1568, 50);
                Beep(1568, 200);
            }
        }

        void AudioManager::PlayKeyDropSound()
        {
            if (m_soundOn)
            {
                Beep(1568, 200);
                Beep(1568, 50);
            }
        }

        void AudioManager::PlayMoneySound()
        {
            if (m_soundOn)
            {
                Beep(1568, 50);
            }
        }

        void AudioManager::PlayLoseLivesSound()
        {
            if (m_soundOn)
            {
                Beep(200, 100);
            }
        }

        void AudioManager::PlayLoseSound()
        {
            if (m_soundOn)
            {
                Beep(500, 75);
                Beep(500, 75);
                Beep(500, 75);
                Beep(500, 75);
            }
        }

        void AudioManager::PlayWinSound()
        {
            if (m_soundOn)
            {
                Beep(1568, 200);
                Beep(1568, 200);
                Beep(1568, 200);
                Beep(1245, 1000);
                Beep(1397, 200);
                Beep(1397, 200);
                Beep(1397, 200);
                Beep(1175, 1000);
            }
        }
    }
}