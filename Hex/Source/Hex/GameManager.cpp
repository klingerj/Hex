#include "GameManager.h"
#include "Wizard.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include <ctime>
#include <iostream>
#include <string>

// Sets default values
AGameManager::AGameManager() : playerOne(nullptr), playerTwo(nullptr), turnPlayer(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint>Wiz(TEXT("Blueprint'/Game/Blueprints/WizardBP.WizardBP'"));
	if (Wiz.Object) {
		WizClass = (UClass*)Wiz.Object->GeneratedClass;
	}
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

	// Spawn two wizards
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		FVector spawn(rand() % 500, rand() % 500, 0.0f);

		playerOne = World->SpawnActor<AWizard>(WizClass, spawn, FRotator(0.0f));

		spawn = FVector(rand() % 100, rand() % 100, 0.0f);
		playerTwo = World->SpawnActor<AWizard>(WizClass, spawn, FRotator(0.0f));
	}

	playerOne->other = playerTwo;
	playerTwo->other = playerOne;

	playerOne->gm = this;
	playerTwo->gm = this;

	turnPlayer = (turn) ? (playerTwo) : (playerOne);
	otherPlayer = (!turn) ? (playerTwo) : (playerOne);


	//turnPlayer->AutoPossessPlayer = EAutoReceiveInput::Player0;
	//otherPlayer->AutoPossessPlayer = EAutoReceiveInput::Player1;

	turnPlayer->applyTileEffects();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	turnPlayer = (turn) ? (playerTwo) : (playerOne);
	otherPlayer = (!turn) ? (playerTwo) : (playerOne);

	//turnPlayer->AutoPossessPlayer = EAutoReceiveInput::Player0;
	//otherPlayer->AutoPossessPlayer = EAutoReceiveInput::Player1;

	UE_LOG(LogClass, Log, TEXT("Player One: %d ; PlayerTwo: %d ; TurnPlayer is %d"), playerOne->currentStage, playerTwo->currentStage, int(turn) + 1);

	// Only call the event stages once
	switch (turnPlayer->currentStage) {
		case TurnStage::ApplyEffects:
			UE_LOG(LogClass, Log, TEXT("Applied effects for Player %d"), int(turn) + 1);
			turnPlayer->currentStage = TurnStage::Listening;
			break;

		case TurnStage::Cast:
			UE_LOG(LogClass, Log, TEXT("Player %d cast a spell"), int(turn) + 1);
			turnPlayer->currentStage = TurnStage::Listening;
			break;

		case TurnStage::Craft:
			UE_LOG(LogClass, Log, TEXT("Player %d crafted a spell"), int(turn) + 1);
			turnPlayer->currentStage = TurnStage::Listening;
			break;

		case TurnStage::Move:
			UE_LOG(LogClass, Log, TEXT("Player %d moved"), int(turn) + 1);
			turnPlayer->currentStage = TurnStage::Listening;
			break;

		case TurnStage::End:
			UE_LOG(LogClass, Log, TEXT("Ending turn for Player %d"), int(turn) + 1);

			turn = !turn;

			turnPlayer = (turn) ? (playerTwo) : (playerOne);
			otherPlayer = (!turn) ? (playerTwo) : (playerOne);

			//turnPlayer->AutoPossessPlayer = EAutoReceiveInput::Player0;
			//otherPlayer->AutoPossessPlayer = EAutoReceiveInput::Player1;

			UE_LOG(LogClass, Log, TEXT("Beginning turn for Player %d"), int(turn) + 1);

			turnPlayer->currentStage = TurnStage::ApplyEffects;
			break;

		case TurnStage::Listening:
			UE_LOG(LogClass, Log, TEXT("Listening for input from Player %d"), int(turn) + 1);
			break;
	}
}
