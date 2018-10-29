#include "GameManager.h"
#include "Wizard.h"
#include <ctime>
#include <iostream>

// Sets default values
AGameManager::AGameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	// Seed RNG with current time
	srand(time(nullptr));
	// Randomize who goes first
	// turn == 0 => Player0 goes first
	turn = (rand() / RAND_MAX) > 0.5;
	turnPlayer = (turn) ? (playerTwo) : (playerOne);
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	turnPlayer = (turn) ? (playerTwo) : (playerOne);
	// Only call the event stages once
	switch (currentStage) {
	case TurnStage::ApplyEffects:
		std::cout << "Applying effects for Player " << turn << std::endl;

		turnPlayer->applyTileEffects();

		currentStage = TurnStage::Listening;
		break;
	case TurnStage::Cast:
		std::cout << "Player " << turn << " is casting a spell" << std::endl;

		turnPlayer->castSpell(-1);

		currentStage = TurnStage::Listening;
		break;
	case TurnStage::Craft:
		std::cout << "Player " << turn << " is crafting a spell" << std::endl;

		turnPlayer->craftSpell(-1, -1, -1);

		currentStage = TurnStage::Listening;
		break;
	case TurnStage::Move:
		std::cout << "Player " << turn << " is moving" << std::endl;

		turnPlayer->move(-1);

		currentStage = TurnStage::Listening;
		break;
	case TurnStage::End:
		std::cout << "Ending turn for Player " << turn << std::endl;

		turn = !turn;
		turnPlayer = (turn) ? (playerTwo) : (playerOne);

		std::cout << "Beginning turn for Player " << turn << std::endl;

		currentStage = TurnStage::ApplyEffects;
		break;
	case TurnStage::Listening:
		std::cout << "Listening for input from Player " << turn << std::endl;

		currentStage = turnPlayer->readInput();
		break;
	}
}
