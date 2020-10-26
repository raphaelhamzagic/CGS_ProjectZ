#pragma once
#include "EditorState.h"

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

    // chars for gameplay editing  

    // chars for blueprint editing
    static constexpr char kWall1 = '-';
    static constexpr char kWall2 = '|';
    static constexpr char kWall3 = '+';

    // weapons
    static constexpr char kGun = '1';
    static constexpr char kGunAmmo = '.';
    static constexpr char kShotgun = '2';
    static constexpr char kShotgunAmmo = '*';

    // items
    static constexpr char kLife = 'l';
    static constexpr char kWood = 'w';
    static constexpr char kSerum = 'x';

    // keys and doors
    static constexpr char kDoor = 'D';
    static constexpr char kBlueKey = 'b';
    static constexpr char kBlueDoor = 'B';
    static constexpr char kGreenKey = 'g';
    static constexpr char kGreenDoor = 'G';
    static constexpr char kCyanKey = 'c';
    static constexpr char kCyanDoor = 'C';
    static constexpr char kRedKey = 'r';
    static constexpr char kRedDoor = 'R';
    static constexpr char kMagentaKey = 'm';
    static constexpr char kMagentaDoor = 'M';
    static constexpr char kBrownKey = 'a';
    static constexpr char kBrownDoor = 'A';
    static constexpr char kYellowKey = 'y';
    static constexpr char kYellowDoor = 'Y';

    // enemies
    static constexpr char kZombie = 'z';
    static constexpr char kLeftShootingCreature = '<';
    static constexpr char kRightShootingCreature = '>';

    // cabinet
    static constexpr char kCabinet = '^';

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
    bool IsWall(char input);
    bool IsDoor(char input);
};
