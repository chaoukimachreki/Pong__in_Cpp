#include "Game.h"
#include <iostream>

const float thickness = 15.0;
const float paddlew = 80.0f;

Game::Game() :
	mIsRunning(true),
	mWindow(nullptr),
	mRenderer(nullptr),
	mTicksCount(0),
	mPaddleDir(0)
{};

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("SDL has failed to start %s", SDL_GetError());
	}
	mWindow = SDL_CreateWindow(
		"Pong Gamee for the thousands time",
		100,100,1500,800,0
	
	);
	if (!mWindow){
		SDL_Log("failed to create window %s", SDL_GetError());
	}
	
	mRenderer = SDL_CreateRenderer(
		mWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
	);

	mPaddlePos.x = 1130.0f/2;
	mPaddlePos.y = 800.0f - 2*thickness;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;


	return true;
	
};

void  Game::RunLoop() {
	while (mIsRunning){
		ProcessInput();
		UpdateGame();
		GenerateOutput();

	}

}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
	
};

void Game::ProcessInput() {

	SDL_Event event;
	while(SDL_PollEvent(&event)){

		switch (event.type) { 
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
		
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_Q]) {
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_D]){
		mPaddleDir += 1;
	}

};

void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float DeltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	if (DeltaTime > 0.05f) {
		DeltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();
	if (mPaddleDir != 0) {
		mPaddlePos.x += mPaddleDir * 300.0f * DeltaTime;
		// Check if the paddle is off the left side of the screen
		if (mPaddlePos.x < thickness) {
			mPaddlePos.x = thickness;
		}

		// Check if the paddle is off the right side of the screen
	    if (mPaddlePos.x > (1500-(thickness+paddlew))){
			mPaddlePos.x = 1500-(thickness + paddlew);
		}

	}
	mBallPos.x += mBallVel.x * DeltaTime;
	mBallPos.y += mBallVel.y * DeltaTime;

	// Collision detection
	if (mBallPos.y <= 0) { // Ball hits top wall
		mBallVel.y *= -1;
		mBallPos.y = 0 + thickness; // Add offset to ball's position
	}
	else if (mBallPos.y >= (800 - thickness - thickness) && // Ball is at paddle's height
		mBallPos.x >= mPaddlePos.x && mBallPos.x <= (mPaddlePos.x + paddlew)) { // Ball hits paddle
		mBallVel.y *= -1;
	}
	else if (mBallPos.y >= (800 - thickness)) { // Ball misses paddle and hits bottom wall
		mIsRunning = false; // End game
	}

	if (mBallPos.x <= 0 || mBallPos.x >= (1500 - thickness)) { // Ball hits left or right wall
		mBallVel.x *= -1;
		if (mBallPos.x <= 0) {
			mBallPos.x = 0 + thickness; // Add offset to ball's position
		}
		else {
			mBallPos.x = 1500 - thickness - thickness; // Add offset to ball's position
		}
	}

};

void Game::GenerateOutput() {

	// Set the color for the canvas and clear it
	SDL_SetRenderDrawColor(mRenderer, 101, 67, 33, 1); // Brown color
	SDL_RenderClear(mRenderer);

	// Create the walls
	SDL_Rect wallTop{ 0,0,1500,thickness };
	SDL_Rect wallBottom{ 0,800 - thickness,1500,thickness };
	SDL_Rect wallLeft{ 0,0,thickness,800 };
	SDL_Rect wallRight{ 1500 - thickness ,0,thickness,800 };

	// Set the color for the top wall (Modern Blue)
	SDL_SetRenderDrawColor(mRenderer, 0, 123, 167, 255);
	SDL_RenderFillRect(mRenderer, &wallTop);

	// Set the color for the bottom wall (Modern Green)
	SDL_SetRenderDrawColor(mRenderer, 0, 166, 81, 255);
	SDL_RenderFillRect(mRenderer, &wallBottom);

	// Set the color for the left wall (Modern Red)
	SDL_SetRenderDrawColor(mRenderer, 179, 27, 27, 255);
	SDL_RenderFillRect(mRenderer, &wallLeft);

	// Set the color for the right wall (Modern Purple)
	SDL_SetRenderDrawColor(mRenderer, 95, 75, 139, 255);
	SDL_RenderFillRect(mRenderer, &wallRight);

	//Draw paddle and ball
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y),
		static_cast<int>(paddlew),
		static_cast<int>(thickness)
	};
	SDL_SetRenderDrawColor(mRenderer, 57, 255, 20, 255); // Neon Green

	SDL_RenderFillRect(mRenderer, &paddle);

	// Draw ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x),
		static_cast<int>(mBallPos.y),
		thickness,
		thickness
	};
	SDL_SetRenderDrawColor(mRenderer, 57, 255, 20, 255); // Neon Green
	SDL_RenderFillRect(mRenderer, &ball);

	// Update the screen
	SDL_RenderPresent(mRenderer);

	

};

