#pragma once
namespace projectz
{
    namespace game
    {
        class MapChars
        {
        public:
            static constexpr char Wall = (char)219;
            static constexpr char Empty = ' ';
            static constexpr char Fog = (char)176;

            static constexpr char WeaponGun = '1';

            static constexpr char AmmoGun = '.';

            static constexpr char HealthKit = '+';

            static constexpr char EnemyZombie = 'z';
            static constexpr char EnemyGooSpittingLeft = (char)185;
            static constexpr char EnemyGooSpittingRight = (char)204;
            static constexpr char EnemyGooSpittingLeftProjectile = (char)174;
            static constexpr char EnemyGooSpittingRightProjectile = (char)175;

            static constexpr char WindowHorizontal = (char)196;
            static constexpr char WindowVertical = (char)179;

            static constexpr char DoorHorizontal = (char)205;
            static constexpr char DoorVertical = (char)186;

            static constexpr char Key = 'k';

            static constexpr char PlayerAlive = '@';
            static constexpr char PlayerDead = 'X';
            static constexpr char PlayerAliveRight = '>';
            static constexpr char PlayerAliveLeft = '<';
            static constexpr char PlayerAliveUp = '^';
            static constexpr char PlayerAliveDown = 'v';
        };
    }
}