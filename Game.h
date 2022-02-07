#pragma once
using namespace utils;
#pragma region gameInformation
// Set your name and group in the title here
std::string g_WindowTitle{ "Better pong - Samyn Jonas - 1DAE23" };

// Change the window dimensions here
float g_WindowWidth{ 750 };
float g_WindowHeight{ 500 };
#pragma endregion gameInformation



#pragma region ownDeclarations
// Declare your own global variables here

//Bal locatie
Point2f g_Bal( g_WindowWidth / 2, g_WindowHeight / 2 );

//Lijn locatie speler 1
Point2f g_PlayerOnePointOne{};
Point2f g_PlayerOnePointTwo{};

//Lijn locatie speler 2
Point2f g_PlayerTwoPointOne{};
Point2f g_PlayerTwoPointTwo{};

Point2f RandomObject{};

//Controle of de spelers aan het tekenen zijn
bool g_PlayerOneIsDrawing{ false };
bool g_PlayerTwoIsDrawing{ false };

//De radius van de bal
const float g_BallWidth{ 10 };

//De verschillende snelheden
float g_BasicSpeed{ 1 };
float g_SpeedMultiply{ 0.025f };
float g_XSpeed{ g_BasicSpeed };
float g_YSpeed{ g_BasicSpeed };

float g_TestObjectWidth{ 40 };
float g_TestObjectHeight{ 60 };

//De beweging
enum class MoveTo { left, right, up, down };
MoveTo MoveToY{ MoveTo::down };
MoveTo MoveToX{ MoveTo::right };

//De terugsturendekracht van de line
Point2f g_WallForceX{};
Point2f g_WallForceY{};
float WallForceX{};
float WallForceY{};
bool g_IsLeaningLeft{};

//Controle of de bal het gehit heeft
bool g_Hit{ false };

//De speler locatie
Point2f g_PlayerOnePos{ 10, g_WindowHeight / 2 };
Point2f g_PlayerTwoPos{ g_WindowWidth - 10, g_WindowHeight / 2 };

//De speler beweging
enum class PlayerMovement {left = -1, right = 1, up = 1, down = -1, idle = 0};
PlayerMovement PlayerOneX{ PlayerMovement::idle };
PlayerMovement PlayerOneY{ PlayerMovement::idle };

PlayerMovement PlayerTwoX{ PlayerMovement::idle };
PlayerMovement PlayerTwoY{ PlayerMovement::idle };

//De speler snelheid
float g_PlayerSpeed{ 250 };


// Declare your own functions here
void CheckCollisionX(Point2f CollisionPoint, float CollisionWidth, float CollisionHeight, Point2f MovingObject, float MovingObjectWidth = 1, float MovingObjectHeight = 1);
void CheckCollisionY(Point2f CollisionPoint, float CollisionWidth, float CollisionHeight, Point2f MovingObject, float MovingObjectWidth = 1, float MovingObjectHeight = 1);

void CheckCollisionX(float CollisionPointX, float CollisionPointY, float CollisionWidth, float CollisionHeight, Point2f MovingObject, float MovingObjectWidth, float MovingObjectHeight);
void CheckCollisionY(float CollisionPointX, float CollisionPointY, float CollisionWidth, float CollisionHeight, Point2f MovingObject, float MovingObjectWidth, float MovingObjectHeight);

void HitLine(Point2f ColllisionPointOne, Point2f ColllisionPointTwo, Point2f MovingObject, float MovingObjectWidth, float MovingObjectHeight);

void CalculateForce(Point2f ColllisionPointOne, Point2f ColllisionPointTwo, float MovingXSpeed, float MovingYSpeed);

void DrawPlayerLines();
void DrawBall();
void DrawPlayers();

void CheckForLineDrawing();
void CalculateBallSpeed( float elapsedSec );
void UpdatePlayerLocation( float& PlayerSpeed, PlayerMovement movement, float& playerLocation );
void HitGoal();

#pragma endregion ownDeclarations

#pragma region gameFunctions											
void Start();
void Draw();
void Update(float elapsedSec);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
