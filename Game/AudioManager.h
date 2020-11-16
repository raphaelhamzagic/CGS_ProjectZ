#pragma once
#include <Windows.h>

namespace projectz {
    namespace game {
        class AudioManager
        {
            static AudioManager* s_pInstance;
            bool m_soundOn;
            AudioManager();

        public:
            static AudioManager* GetInstance();
            static void DestroyInstance();

            void ToggleSound();
            bool IsSoundOn();
            void PlayDoorClosedSound();
            void PlayDoorOpenSound();
            void PlayGunPickupSound();
            void PlayGunAmmoPickupSound();
            void PlayKeyPickupSound();
            void PlayKeyDropSound();
            void PlayWallHitSound();
            void PlayLoseLivesSound();
            void PlayLoseSound();
            void PlayWinSound();
            void PlayGunShootingSound();
        };
    }
}