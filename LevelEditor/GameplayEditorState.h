#pragma once
#include "EditorState.h"

namespace projectz {
    namespace editor {

        struct Point;

        class GameplayEditorState : public EditorState
        {
            static constexpr int kCanvasWidth = 110;
            // static constexpr int kCanvasHeight = 29;

            static constexpr int kLevelWidth = 100;
            // static constexpr int klevelHeight = 25;

            // key codes
            static constexpr int kArrowInput = 224;
            static constexpr int kLeftArrow = 75;
            static constexpr int kRightArrow = 77;
            static constexpr int kUpArrow = 72;
            static constexpr int kDownArrow = 80;

            static constexpr int kEscape = 27;
            static constexpr int kBackspace = 8;

            // blueprint editor chars
            static constexpr char kDoor = 'D';
            static constexpr char kWindow = 'W';
            static constexpr char kWall1 = '-';
            static constexpr char kWall2 = '|';
            static constexpr char kWall3 = '+';
            

            // chars for gameplay editing  

            // weapons
            static constexpr char kGun = '1';
            static constexpr char kGunAmmo = '.';
            static constexpr char kShotgun = '2';
            static constexpr char kShotgunAmmo = '*';

            // items
            static constexpr char kLife = 'l';
            static constexpr char kWood = 'w';
            static constexpr char kSerum = 'x';

            // keys
            static constexpr char kBrownKey = 'a';
            static constexpr char kBlueKey = 'b';
            static constexpr char kCyanKey = 'c';
            static constexpr char kGreenKey = 'd';
            static constexpr char kMagentaKey = 'e';
            static constexpr char kRedKey = 'f';
            static constexpr char kYellowKey = 'g';

            // doors
            static constexpr char kHorizontalBrownDoor = 'A';
            static constexpr char kVerticalBrownDoor = 'Z';
            static constexpr char kHorizontalBlueDoor = 'B';
            static constexpr char kVerticalBlueDoor = 'Y';
            static constexpr char kHorizontalCyanDoor = 'C';
            static constexpr char kVerticalCyanDoor = 'X';
            static constexpr char kHorizontalGreenDoor = 'D';
            static constexpr char kVerticalGreenDoor = 'W';
            static constexpr char kHorizontalMagentaDoor = 'E';
            static constexpr char kVerticalMagentaDoor = 'V';
            static constexpr char kHorizontalRedDoor = 'F';
            static constexpr char kVerticalRedDoor = 'U';
            static constexpr char kHorizontalYellowDoor = 'G';
            static constexpr char kVerticalYellowDoor = 'T';

            // windows
            static constexpr char kVerticalWindow = 'M';
            static constexpr char kHorizontalWindow = 'N';

            // enemies
            static constexpr char kZombie = 'z';
            static constexpr char kLeftShootingCreature = '<';
            static constexpr char kRightShootingCreature = '>';

            static constexpr char kPlayerStart = '@';

            // cabinet
            static constexpr char kCabinet = 'P';

            // border canvas chars
            static constexpr char kTopRightBorder = 187;
            static constexpr char kTopLeftBorder = 201;
            static constexpr char kMiddleRightBorder = 185;
            static constexpr char kMiddleLeftBorder = 204;
            static constexpr char kBottomRightBorder = 188;
            static constexpr char kBottomLeftBorder = 200;
            static constexpr char kHorizontalBorder = 205;
            static constexpr char kVerticalBorder = 186;

            static constexpr char kCursor = '_';
            static constexpr char kEmpty = ' ';

            Point* m_pCursor;
        public:
            GameplayEditorState(LevelEditorStateMachine* stateMachine);
            virtual ~GameplayEditorState() = default;

            virtual void Enter() override;
            virtual bool Update() override;
            virtual void Draw() override;
            virtual void Exit() override;

        private:
            void UpdateCursor();

            void DrawEditorTitle();
            void DrawCanvasTopBorder();
            void DrawCanvasMiddleBorder();
            void DrawCanvasLeftBorder();
            void DrawCanvasRightBorder();
            void DrawCanvasBottomBorder();

            void DrawCanvasHorizontalMargin();
            void DrawCanvasEmptyLine();

            void DrawLegend();
            void Save();
            bool IsValidChar(char input);
            bool IsDoor(char input);
            bool IsWindow(char input);
            bool IsWall(char input);
        };

    }
}