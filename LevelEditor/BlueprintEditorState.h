#pragma once
#include "EditorState.h"

namespace projectz {
    namespace editor {

        struct Point;

        class BlueprintEditorState : public EditorState
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

            static constexpr char kWall1 = '-';
            static constexpr char kWall2 = '|';
            static constexpr char kWall3 = '+';
   
            static constexpr char kDoor = 'D';
            static constexpr char kWindow = 'W';
   
            static constexpr char kRoomA = 'a';
            static constexpr char kRoomB = 'b';
            static constexpr char kRoomC = 'c';
            static constexpr char kRoomD = 'd';
            static constexpr char kRoomE = 'e';
            static constexpr char kRoomF = 'f';
            static constexpr char kRoomG = 'g';
            static constexpr char kRoomH = 'h';
            static constexpr char kRoomI = 'i';
            static constexpr char kRoomJ = 'j';
            static constexpr char kRoomK = 'k';
            static constexpr char kRoomL = 'l';
            static constexpr char kRoomM = 'm';
            static constexpr char kRoomN = 'n';

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
            BlueprintEditorState(LevelEditorStateMachine* stateMachine);
            virtual ~BlueprintEditorState() = default;

            virtual void Enter() override;
            virtual bool Update() override;
            virtual void Draw() override;
            virtual void Exit() override;

        private:
            void UpdateCursor();

            void DrawEditorTitle();
            void DrawCanvasTopBorder();
            void DrawCanvasLeftBorder();
            void DrawCanvasRightBorder();
            void DrawCanvasBottomBorder();
    
            void DrawCanvasHorizontalMargin();
            void DrawCanvasVerticalMargin();
            void DrawCanvasEmptyLine();

            void DrawLegend();
            void Save();
            bool IsWall(char input);
            bool IsDoor(char input);
            bool IsWindow(char input);
            bool IsRoom(char input);
            bool IsEmpty(char input);
        };
    }
}