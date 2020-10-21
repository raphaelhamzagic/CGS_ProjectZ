#pragma once
#include <Windows.h>

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
    void PlayKeyPickupSound();
    void PlayKeyDropSound();
    void PlayMoneySound();
    void PlayLoseLivesSound();
    void PlayLoseSound();
    void PlayWinSound();
};