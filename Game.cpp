#include "pch.h"
#include "Game.h"

#include <iostream>

//Basic game functions
#pragma region gameFunctions											
void Start()
{
	// initialize game resources here
}

void Draw()
{
	ClearBackground(0,0,0);

	DrawPlayerLines();
	DrawBall();	 	
	DrawPlayers();	
}

void Update(float elapsedSec)
{
	// process input, do physics

	//Speler 1 snelheid
	float playerOneXSpeed{ g_PlayerSpeed * elapsedSec };
	float playerOneYSpeed{ g_PlayerSpeed * elapsedSec };

	//Speler 2 snelheid
	float playerTwoXSpeed{ g_PlayerSpeed * elapsedSec };
	float playerTwoYSpeed{ g_PlayerSpeed * elapsedSec };

	CheckForLineDrawing();	

	HitLine(g_PlayerOnePointOne, g_PlayerOnePointTwo, g_Bal, g_BallWidth / 2, g_BallWidth / 2);
	HitLine(g_PlayerTwoPointOne, g_PlayerTwoPointTwo, g_Bal, g_BallWidth / 2, g_BallWidth / 2);

	CalculateBallSpeed( elapsedSec );	

	//De beweging van de speler
	UpdatePlayerLocation(playerOneXSpeed, PlayerOneX, g_PlayerOnePos.x);
	UpdatePlayerLocation(playerOneYSpeed, PlayerOneY, g_PlayerOnePos.y);
	UpdatePlayerLocation(playerTwoXSpeed, PlayerTwoX, g_PlayerTwoPos.x);
	UpdatePlayerLocation(playerTwoYSpeed, PlayerTwoY, g_PlayerTwoPos.y);
	
	HitGoal();
}

void End()
{
	// free game resources here
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
	//Speler input
	switch (key)
	{
	case SDLK_LEFT:
		PlayerOneX = PlayerMovement::left;
		break;
	case SDLK_RIGHT:
		PlayerOneX = PlayerMovement::right;
		break;
	case SDLK_UP:
		PlayerOneY = PlayerMovement::up;
		break;
	case SDLK_DOWN:
		PlayerOneY = PlayerMovement::down;
		break;
	case SDLK_q:
	case SDLK_a:
		PlayerTwoX = PlayerMovement::left;
		break;
	case SDLK_d:
		PlayerTwoX = PlayerMovement::right;
		break;
	case SDLK_z:
	case SDLK_w:
		PlayerTwoY = PlayerMovement::up;
		break;
	case SDLK_s:
		PlayerTwoY = PlayerMovement::down;
		break;
	case SDLK_KP_0:
		g_PlayerOneIsDrawing = true;
		g_PlayerOnePointOne.x = g_PlayerOnePos.x;
		g_PlayerOnePointOne.y = g_PlayerOnePos.y;
		g_PlayerOnePointTwo = g_PlayerOnePointOne;
		break;
	case SDLK_e:
		g_PlayerTwoIsDrawing = true;
		g_PlayerTwoPointOne.x = g_PlayerTwoPos.x;
		g_PlayerTwoPointOne.y = g_PlayerTwoPos.y;
		g_PlayerTwoPointTwo = g_PlayerTwoPointOne;
		break;
	}
}

void OnKeyUpEvent(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_LEFT:
		if (PlayerOneX == PlayerMovement::left)
		{
			PlayerOneX = PlayerMovement::idle;
		}
		break;
	case SDLK_RIGHT:
		if (PlayerOneX == PlayerMovement::right)
		{
			PlayerOneX = PlayerMovement::idle;
		}
		break;
	case SDLK_UP:
		if (PlayerOneY == PlayerMovement::up)
		{
			PlayerOneY = PlayerMovement::idle;
		}
		break;
	case SDLK_DOWN:
		if (PlayerOneY == PlayerMovement::down)
		{
			PlayerOneY = PlayerMovement::idle;
		}
		break;
	case SDLK_q:
	case SDLK_a:
		if (PlayerTwoX == PlayerMovement::left)
		{
			PlayerTwoX = PlayerMovement::idle;
		}
		break;
	case SDLK_d:
		if (PlayerTwoX == PlayerMovement::right)
		{
			PlayerTwoX = PlayerMovement::idle;
		}
		break;
	case SDLK_z:
	case SDLK_w:
		if (PlayerTwoY == PlayerMovement::up)
		{
			PlayerTwoY = PlayerMovement::idle;
		}
		break;
	case SDLK_s:
		if (PlayerTwoY == PlayerMovement::down)
		{
			PlayerTwoY = PlayerMovement::idle;
		}
		break;
	case SDLK_KP_0:
		g_PlayerOneIsDrawing = false;
		g_PlayerOnePointTwo.x = g_PlayerOnePos.x;
		g_PlayerOnePointTwo.y = g_PlayerOnePos.y;
		break;
	case SDLK_e:
		g_PlayerTwoIsDrawing = false;
		g_PlayerTwoPointTwo.x = g_PlayerTwoPos.x;
		g_PlayerTwoPointTwo.y = g_PlayerTwoPos.y;
		break;
	}	
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	/*if (g_IsDrawing == true)
	{
		PointTwo.x = float(e.x);
		PointTwo.y = float(g_WindowHeight - e.y);
	}*/
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	/*g_IsDrawing = true;
	PointOne.x = float(e.x);
	PointOne.y = float(g_WindowHeight - e.y);
	PointTwo = PointOne;*/
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	/*g_IsDrawing = false;
	PointTwo.x = float(e.x);
	PointTwo.y = float(g_WindowHeight - e.y);*/
}
#pragma endregion inputHandling

#pragma region ownDefinitions
// Define your own functions here


void CheckCollisionX(float CollisionPointX, float CollisionPointY, float CollisionWidth, float CollisionHeight, Point2f MovingObject, float MovingObjectWidth, float MovingObjectHeight)
{
	Point2f CollisionPointFloat{ CollisionPointX,  CollisionPointY };
}

void CheckCollisionX(Point2f CollisionPoint, float CollisionWidth, float CollisionHeight, Point2f MovingObject, float MovingObjectWidth, float MovingObjectHeight)
{
	if (MovingObject.y + MovingObjectHeight > CollisionPoint.y && MovingObject.y < CollisionPoint.y + CollisionHeight)
	{
		if (MovingObject.x + MovingObjectWidth > CollisionPoint.x && MovingObject.x < CollisionPoint.x)
		{
			std::cout << "POINT for left" << std::endl;
		}
		else if (MovingObject.x < CollisionPoint.x + CollisionWidth && MovingObject.x + MovingObjectWidth > CollisionPoint.x + CollisionWidth)
		{
			std::cout << "POINT for right" << std::endl;
		}
	}
}

void CheckCollisionY(float CollisionPointX, float CollisionPointY, float CollisionWidth, float CollisionHeight, Point2f MovingObject, float MovingObjectWidth, float MovingObjectHeight)
{
	Point2f CollisionPointFloat{ CollisionPointX,  CollisionPointY };
}

//Checken van collision op de Y
void CheckCollisionY(Point2f CollisionPoint, float CollisionWidth, float CollisionHeight, Point2f MovingObject, float MovingObjectWidth, float MovingObjectHeight)
{
	if (MovingObject.x + MovingObjectWidth > CollisionPoint.x && MovingObject.x < CollisionPoint.x + CollisionWidth)
	{
		if (MovingObject.y < CollisionPoint.y + CollisionHeight && MovingObject.y + MovingObjectHeight > CollisionPoint.y)
		{
			//std::cout << MovingObject.y + MovingObjectHeight << " > " << CollisionPoint.y << std::endl;
			//std::cout << "Down Collision" << std::endl;
			MoveToY = MoveTo::up;
			g_BasicSpeed += g_SpeedMultiply;
		}
		else if (MovingObject.y + MovingObjectHeight > CollisionPoint.y && MovingObject.y < CollisionPoint.y)
		{
			//std::cout << MovingObject.y << " < " << CollisionPoint.y + CollisionHeight << std::endl;
			//std::cout << "Up Collision" << std::endl;
			MoveToY = MoveTo::down;
			g_BasicSpeed += g_SpeedMultiply;
		}
	}
}
//Controle of de lijn geraakt wordt
void HitLine(Point2f ColllisionPointOne, Point2f ColllisionPointTwo, Point2f MovingObject, float MovingObjectWidth, float MovingObjectHeight)
{
	float totalLength = ColllisionPointOne.x - ColllisionPointTwo.x; //X lengte van de lijn
	float totalHeight = ColllisionPointOne.y - ColllisionPointTwo.y; //Y lengte van de lijn
	float Schuinezijde = float(sqrt((totalLength * totalLength) + (totalHeight * totalHeight))); //Stelling van ded pythagoras om de schuine zijde te berekenen

	float CurrentLenght = MovingObject.x - ColllisionPointOne.x; //De lengte tussen het eerste x-punt van de lijn en de x van de bal
	float CurrentHeight = MovingObject.y - ColllisionPointOne.y; //De lengte tussen het eerste y-punt van de lijn en de y van de bal
	float CurrentPlace = float(sqrt((CurrentLenght * CurrentLenght) + (CurrentHeight * CurrentHeight))); //stelling van pythagoras om de schuine zijde te berekenen

	float verhouding{ CurrentPlace / Schuinezijde }; //Verhouding tussen de lengte van de getekende lijn en de schuine lijn tussen de bal en de lijn

	float NewLength{ totalLength * verhouding }; //Nieuwe lengte aan de hand van de totale X lengte van de schuine lijn en de verhouding
	float NewHeighth{ totalHeight * verhouding }; //Nieuwe hoogte aan de hand van de totale y lengte van de schuine lijn en de verhouding

	RandomObject.x = ColllisionPointOne.x - NewLength; //X punt van een collider punt op de schuine lijn projecteren
	RandomObject.y = ColllisionPointOne.y - NewHeighth; //Y punt van een collider punt op de schuine lijn projecteren

	float ImpactOffset{ abs(g_XSpeed * 4.f) }; //De grote van de collider zodat de bal niet te snel beweegt en de collider zou skippen


	if (ColllisionPointOne.x > ColllisionPointTwo.x) //Controle of de X van het eerste punt van de lijn groter is dan het 2de punt van de lijn
	{
		// X1 Bigger
		if (ColllisionPointOne.y > ColllisionPointTwo.y) //Controle of de Y van het eerste punt van de lijn groter is dan het 2de punt van de lijn
		{
			g_IsLeaningLeft = false; //In dit geval zal de lijn niet naar link leunen
			if (RandomObject.y > ColllisionPointTwo.y && RandomObject.y < ColllisionPointOne.y) //Controle of de y van het colliderPunt tussen de Y van de lijn zit
			{
				if (MovingObject.x <= RandomObject.x + ImpactOffset && MovingObject.x >= RandomObject.x - ImpactOffset && g_Hit == false) //Controle of de X van de bal in de collider zit en hij niet al eerder gehit heeft
				{
					if (MovingObject.y <= RandomObject.y + ImpactOffset && MovingObject.y >= RandomObject.y - ImpactOffset) //Controle of de Y binnen de collider zit
					{
						std::cout << "HIT" << std::endl; //output geven dat de lijn geraakt is
						g_Hit = true; //De lijn wordt geraakt
						g_BasicSpeed += g_SpeedMultiply; //Nieuwe snelheid berekenen aan de hand van de hoek

						CalculateForce(ColllisionPointOne, ColllisionPointTwo, g_XSpeed, g_YSpeed); //De kracht van de impact berekenen
						if (MoveToX == MoveTo::left)
						{
							MoveToX = MoveTo::right;
						}
						else
						{
							MoveToX = MoveTo::left;
						}
					}
				}
			}
		}
		else if (ColllisionPointOne.y < ColllisionPointTwo.y)
		{
			g_IsLeaningLeft = true;
			//std::cout << "Is leaning left" << std::endl;
			//std::cout << "Check HIT" << std::endl;
			if (RandomObject.y < ColllisionPointTwo.y && RandomObject.y > ColllisionPointOne.y)
			{
				if (MovingObject.x <= RandomObject.x + ImpactOffset && MovingObject.x >= RandomObject.x - ImpactOffset && g_Hit == false)
				{
					if (MovingObject.y <= RandomObject.y + ImpactOffset && MovingObject.y >= RandomObject.y - ImpactOffset)
					{
						std::cout << "HIT" << std::endl;
						g_Hit = true;
						g_BasicSpeed += g_SpeedMultiply;
						CalculateForce(ColllisionPointOne, ColllisionPointTwo, g_XSpeed, g_YSpeed);
						if (MoveToX == MoveTo::left)
						{
							MoveToX = MoveTo::right;
						}
						else
						{
							MoveToX = MoveTo::left;
						}
					}
				}
				if (MovingObject.x >= RandomObject.x + ImpactOffset || MovingObject.x <= RandomObject.x - ImpactOffset)
				{
					if (MovingObject.y >= RandomObject.y + ImpactOffset || MovingObject.y <= RandomObject.y - ImpactOffset)
					{
						g_Hit = false;
					}
				}
			}

		}
		else if (ColllisionPointOne.y == ColllisionPointTwo.y)
		{
			//std::cout << "Check HIT" << std::endl;			
		}
	}
	else if (ColllisionPointOne.x < ColllisionPointTwo.x)
	{
		//std::cout << "X1 < X2" << std::endl;
		if (ColllisionPointOne.y > ColllisionPointTwo.y)
		{
			g_IsLeaningLeft = true;
			//std::cout << "Is leaning left" << std::endl;
			//std::cout << "Check HIT" << std::endl;
			if (RandomObject.y > ColllisionPointTwo.y && RandomObject.y < ColllisionPointOne.y)
			{
				if (MovingObject.x <= RandomObject.x + ImpactOffset && MovingObject.x >= RandomObject.x - ImpactOffset && g_Hit == false)
				{
					if (MovingObject.y <= RandomObject.y + ImpactOffset && MovingObject.y >= RandomObject.y - ImpactOffset)
					{
						std::cout << "HIT" << std::endl;
						g_Hit = true;
						g_BasicSpeed += g_SpeedMultiply;
						CalculateForce(ColllisionPointOne, ColllisionPointTwo, g_XSpeed, g_YSpeed);
						if (MoveToX == MoveTo::left)
						{
							MoveToX = MoveTo::right;
						}
						else
						{
							MoveToX = MoveTo::left;
						}
					}
				}
				if (MovingObject.x >= RandomObject.x + ImpactOffset || MovingObject.x <= RandomObject.x - ImpactOffset)
				{
					if (MovingObject.y >= RandomObject.y + ImpactOffset || MovingObject.y <= RandomObject.y - ImpactOffset)
					{
						g_Hit = false;
					}
				}
			}
		}
		else if (ColllisionPointOne.y < ColllisionPointTwo.y)
		{
			//std::cout << "Check HIT" << std::endl;
			g_IsLeaningLeft = false;
			//std::cout << "Is leaning right" << std::endl;
			if (RandomObject.y < ColllisionPointTwo.y && RandomObject.y > ColllisionPointOne.y)
			{
				if (MovingObject.x <= RandomObject.x + ImpactOffset && MovingObject.x >= RandomObject.x - ImpactOffset && g_Hit == false)
				{
					if (MovingObject.y <= RandomObject.y + ImpactOffset && MovingObject.y >= RandomObject.y - ImpactOffset)
					{
						std::cout << "HIT" << std::endl;
						g_Hit = true;
						g_BasicSpeed += g_SpeedMultiply;
						CalculateForce(ColllisionPointOne, ColllisionPointTwo, g_XSpeed, g_YSpeed);
						if (MoveToX == MoveTo::left)
						{
							MoveToX = MoveTo::right;
						}
						else
						{
							MoveToX = MoveTo::left;
						}
					}
				}
				if (MovingObject.x >= RandomObject.x + ImpactOffset || MovingObject.x <= RandomObject.x - ImpactOffset)
				{
					if (MovingObject.y >= RandomObject.y + ImpactOffset || MovingObject.y <= RandomObject.y - ImpactOffset)
					{
						g_Hit = false;
					}
				}
			}

		}
		else if (ColllisionPointOne.y == ColllisionPointTwo.y)
		{
			//std::cout << "Check HIT" << std::endl;

		}
	}
	else if (ColllisionPointOne.x == ColllisionPointTwo.x)
	{
		//std::cout << "X1 = X2" << std::endl;
		if (ColllisionPointOne.y > ColllisionPointTwo.y)
		{
			//std::cout << "Check HIT" << std::endl;
			if (RandomObject.y > ColllisionPointTwo.y && RandomObject.y < ColllisionPointOne.y)
			{
				if (MovingObject.x <= RandomObject.x + ImpactOffset && MovingObject.x >= RandomObject.x - ImpactOffset && g_Hit == false)
				{
					if (MovingObject.y <= RandomObject.y + ImpactOffset && MovingObject.y >= RandomObject.y - ImpactOffset)
					{
						std::cout << "HIT" << std::endl;
						g_Hit = true;
						g_BasicSpeed += g_SpeedMultiply;
						CalculateForce(ColllisionPointOne, ColllisionPointTwo, g_XSpeed, g_YSpeed);
						if (MoveToX == MoveTo::left)
						{
							MoveToX = MoveTo::right;
						}
						else
						{
							MoveToX = MoveTo::left;
						}
					}
				}
				if (MovingObject.x >= RandomObject.x + ImpactOffset || MovingObject.x <= RandomObject.x - ImpactOffset)
				{
					if (MovingObject.y >= RandomObject.y + ImpactOffset || MovingObject.y <= RandomObject.y - ImpactOffset)
					{
						g_Hit = false;
					}
				}
			}
		}
		else if (ColllisionPointOne.y < ColllisionPointTwo.y)
		{
			//std::cout << "Check HIT" << std::endl;
			if (RandomObject.y < ColllisionPointTwo.y && RandomObject.y > ColllisionPointOne.y)
			{
				if (MovingObject.x <= RandomObject.x + ImpactOffset && MovingObject.x >= RandomObject.x - ImpactOffset && g_Hit == false)
				{
					if (MovingObject.y <= RandomObject.y + ImpactOffset && MovingObject.y >= RandomObject.y - ImpactOffset)
					{
						std::cout << "HIT" << std::endl;
						g_Hit = true;
						g_BasicSpeed += g_SpeedMultiply;
						CalculateForce(ColllisionPointOne, ColllisionPointTwo, g_XSpeed, g_YSpeed);
						if (MoveToX == MoveTo::left)
						{
							MoveToX = MoveTo::right;
						}
						else
						{
							MoveToX = MoveTo::left;
						}
					}
				}
				if (MovingObject.x >= RandomObject.x + ImpactOffset || MovingObject.x <= RandomObject.x - ImpactOffset)
				{
					if (MovingObject.y >= RandomObject.y + ImpactOffset || MovingObject.y <= RandomObject.y - ImpactOffset)
					{
						g_Hit = false;
					}
				}
			}

		}
		else if (ColllisionPointOne.y == ColllisionPointTwo.y)
		{
			//std::cout << "Check HIT" << std::endl;			
		}
	}
	if (MovingObject.x >= RandomObject.x + ImpactOffset || MovingObject.x <= RandomObject.x - ImpactOffset)
	{
		if (MovingObject.y >= RandomObject.y + ImpactOffset || MovingObject.y <= RandomObject.y - ImpactOffset)
		{
			g_Hit = false;
		}
	}	
}

//Berekenen van de kracht
void CalculateForce(Point2f ColllisionPointOne, Point2f ColllisionPointTwo, float MovingXSpeed, float MovingYSpeed)
{
	float BallForce{ float(sqrt((MovingXSpeed * MovingXSpeed) + (MovingYSpeed * MovingYSpeed))) }; //De snelheid van de bal berekenen aan de hand van de X en Y vector
	float WallForce = BallForce * 2; //De kracht van de muur is dubbel de kracht van de bal

	float totalLength = abs(ColllisionPointOne.x - ColllisionPointTwo.x); //De x-lengte van de lijn
	float totalHeight = abs(ColllisionPointOne.y - ColllisionPointTwo.y); //De y-lengte van de lijn
	float Schuinezijde = float(sqrt((totalLength * totalLength) + (totalHeight * totalHeight))); //De schuine lengte van de lijn

	float WallAngle{ asinf(totalHeight / Schuinezijde) }; //de hoek van de lijn berekenen

	WallForceX = (WallForce * sinf(WallAngle)) / sinf(float(M_PI) / 2.f); //De kracht van de muur berekenen op de X
	//std::cout << WallForceX << " X force" << std::endl; 
	WallForceY = (WallForce * sinf((float(M_PI) / 2.f) - WallAngle)) / sinf(float(M_PI) / 2.f); //De kracht van de muur berekenen op de y
	//std::cout << WallForce << std::endl;	

	if (g_XSpeed > 0) //Wanneer dat de snelheid over de X groter was dan 0
	{
		WallForceX = abs(WallForceX) * -1; //De snelheid omdraaien naar links
	}

	if (g_IsLeaningLeft == true) //Als de lijn naar links leant
	{
		if (WallForceX > 0) //Wanneer dat de kracht groter is dan 0
		{
			WallForceY = WallForceY; //De wallforce naar boven
		}
		else if (WallForceX < 0) //Wanneer dat het kleiner is dan 0
		{
			WallForceY = -1 * WallForceY; //De wallforce naar benenden
		}
	}
	else if (g_IsLeaningLeft == false) //Wanneer hij naar rechts leant
	{
		if (WallForceX > 0) //Wanneer dat de kracht groter is dan 0
		{
			WallForceY = -1 * WallForceY; //De wallforce naar beneden
		}
		else if (WallForceX < 0) //Wanneer dat het kleiner is dan 0
		{
			WallForceY = WallForceY; //De wallforce naar boven
		}
	}

	g_WallForceX.x = RandomObject.x + WallForceX;
	g_WallForceX.y = RandomObject.y;

	g_WallForceY.x = RandomObject.x;
	g_WallForceY.y = RandomObject.y + WallForceY;

	//std::cout << WallForceX << " = X " << WallForceY << " = Y" << std::endl;

	g_XSpeed = g_XSpeed + WallForceX;
	g_YSpeed = g_YSpeed + WallForceY;
}

void DrawPlayerLines()
{
	SetColor(1, 1, 1);
	DrawLine(g_PlayerOnePointOne, g_PlayerOnePointTwo, 10); //Lijn speler 1
	DrawLine(g_PlayerTwoPointOne, g_PlayerTwoPointTwo, 10); //Lijn speler 2

	//FillRect(PointOne, g_TestObjectWidth, g_TestObjectHeight);
	//SetColor(1, 0, 0);
	//FillEllipse(RandomObject, 10, 10);

	//DrawLine(g_WallForceX, RandomObject);
	//DrawLine(g_WallForceY, RandomObject);
	//DrawLine(g_WallForceX.x, g_WallForceY.y, RandomObject.x, RandomObject.y);
}
void DrawBall()
{
	SetColor(1, 1, 1);
	FillEllipse(g_Bal, g_BallWidth, g_BallWidth);
}
void DrawPlayers()
{
	//Speler 1
	SetColor(1, 0, 0);
	FillEllipse(g_PlayerOnePos, 10, 10);
	//Speler 1 goal
	FillRect(0, g_WindowHeight / 2 - 100, 10, 200);

	//Speler 2
	SetColor(0, 1, 1);
	FillEllipse(g_PlayerTwoPos, 10, 10);
	//speler 2 goal
	FillRect(g_WindowWidth - 10, g_WindowHeight / 2 - 100, 10, 200);
}

void CheckForLineDrawing()
{
	if (g_PlayerOneIsDrawing == true)
	{
		g_PlayerOnePointTwo.x = g_PlayerOnePos.x;
		g_PlayerOnePointTwo.y = g_PlayerOnePos.y;
	}
	if (g_PlayerTwoIsDrawing == true)
	{
		g_PlayerTwoPointTwo.x = g_PlayerTwoPos.x;
		g_PlayerTwoPointTwo.y = g_PlayerTwoPos.y;
	}
}
void CalculateBallSpeed( float elapsedSec )
{
	//Controle of de bal de rand raakt
	if (g_Bal.y > g_WindowHeight)
	{
		g_YSpeed = g_YSpeed * -1 * elapsedSec;
	}
	else if (g_Bal.y < 0)
	{
		g_YSpeed = g_YSpeed * -1 * elapsedSec;
	}

	if (g_Bal.x > g_WindowWidth)
	{
		g_XSpeed = g_XSpeed * -1 * elapsedSec;
	}
	else if (g_Bal.x < 0)
	{
		g_XSpeed = g_XSpeed * -1 * elapsedSec;
	}

	//Snelheid van de bal meesturen
	g_Bal.x += g_XSpeed;
	g_Bal.y += g_YSpeed;
}
void UpdatePlayerLocation( float& PlayerSpeed, PlayerMovement movement, float& playerLocation)
{
	PlayerSpeed = PlayerSpeed * int(movement);
	playerLocation += PlayerSpeed;
}
void HitGoal()
{
	//Controle of de bal de goal raakt
	if (g_Bal.x < 10 && g_Bal.y > g_WindowHeight / 2 - 100 && g_Bal.y < g_WindowHeight / 2 - 50 + 200)
	{
		std::cout << "Hit for right" << std::endl;
		g_Bal.x = g_WindowWidth / 2;
		g_Bal.y = g_WindowHeight / 2;
		g_XSpeed = g_BasicSpeed;
		g_YSpeed = g_BasicSpeed;
	}
	if (g_Bal.x > g_WindowWidth - 10 && g_Bal.y > g_WindowHeight / 2 - 100 && g_Bal.y < g_WindowHeight / 2 - 50 + 200)
	{
		std::cout << "Hit for left" << std::endl;
		g_Bal.x = g_WindowWidth / 2;
		g_Bal.y = g_WindowHeight / 2;
		g_XSpeed = -g_BasicSpeed;
		g_YSpeed = -g_BasicSpeed;

	}
}

#pragma endregion ownDefinitions