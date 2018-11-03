#include "GameManager.h"
#include "Wizard.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "HexGridGraphManager.h"
#include <ctime>
#include <iostream>
#include <string>

// Sets default values
AGameManager::AGameManager() : playerOne(nullptr), playerTwo(nullptr), turnPlayer(nullptr), turnCounter(0)
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
}

void AGameManager::Setup() {
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

        FVector spawn(500, 500, 400.0f);

        playerOne = World->SpawnActor<AWizard>(WizClass, spawn, FRotator(0.0f));
		UE_LOG(LogClass, Log, TEXT("Tried to spawn a wizard"));
		playerOne->spawnInvAndSpellbook();
    
        spawn = FVector(100, 100, 400.0f);
        playerTwo = World->SpawnActor<AWizard>(WizClass, spawn, FRotator(0.0f));
		UE_LOG(LogClass, Log, TEXT("Tried to spawn a wizard"));
		playerTwo->spawnInvAndSpellbook();

        uint32 playerOneGridIndexX = 0;
        uint32 playerOneGridIndexY = 0;
        uint32 playerTwoGridIndexX = 10;
        uint32 playerTwoGridIndexY = 10;

        for (TActorIterator<AHexGridTile> actorIter(World); actorIter; ++actorIter) {
            if ((*actorIter)->gridIndexX == playerOneGridIndexX && (*actorIter)->gridIndexY == playerOneGridIndexY) {
                playerOne->currentTile = *actorIter;
            }
            else if ((*actorIter)->gridIndexX == playerTwoGridIndexX && (*actorIter)->gridIndexY == playerTwoGridIndexY) {
                playerTwo->currentTile = *actorIter;
            }
        }
        playerOne->SetActorLocation(FVector(playerOne->currentTile->GetActorLocation() + FVector(0, 0, 400)));
        playerTwo->SetActorLocation(FVector(playerTwo->currentTile->GetActorLocation() + FVector(0, 0, 400)));
    }

    playerOne->Tags.Add(FName("Player One"));
    playerTwo->Tags.Add(FName("Player Two"));
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
  playerTwo->SetActorHiddenInGame(false); // idk why we have to do this
	turnPlayer = (turn) ? (playerTwo) : (playerOne);
	otherPlayer = (!turn) ? (playerTwo) : (playerOne);

	//turnPlayer->AutoPossessPlayer = EAutoReceiveInput::Player0;
	//otherPlayer->AutoPossessPlayer = EAutoReceiveInput::Player1;

	//UE_LOG(LogClass, Log, TEXT("Player One: %d ; PlayerTwo: %d ; TurnPlayer is %d"), playerOne->currentStage, playerTwo->currentStage, int(turn) + 1);

	// Only call the event stages once
	switch (turnPlayer->currentStage) {
		case TurnStage::ApplyEffects:
			//UE_LOG(LogClass, Log, TEXT("Applied effects for Player %d"), int(turn) + 1);
			turnPlayer->currentStage = TurnStage::Listening;
			break;

		case TurnStage::Cast:
			//UE_LOG(LogClass, Log, TEXT("Player %d cast a spell"), int(turn) + 1);
			//turnPlayer->currentStage = TurnStage::Listening;
			break;

		case TurnStage::Craft:
			//UE_LOG(LogClass, Log, TEXT("Player %d crafted a spell"), int(turn) + 1);
			//turnPlayer->currentStage = TurnStage::Listening;
			break;

		case TurnStage::Move:
		  //UE_LOG(LogClass, Log, TEXT("Player %d moved"), int(turn) + 1);
			break;
    
    case TurnStage::MoveEnd:
      UE_LOG(LogClass, Log, TEXT("Player %d moved"), int(turn) + 1);
      turnPlayer->currentStage = TurnStage::Listening;
      break;
    case TurnStage::SpellSelected:
        UE_LOG(LogClass, Log, TEXT("Player %d has selected spell %d"), int(turn) + 1, turnPlayer->selectedSpell);
        break;
		case TurnStage::End:
			// TODO: Check that this works as intended
			if (turnPlayer->health <= 0 || otherPlayer->health <= 0) {
				FText header = FText::FromString("GAME OVER");
				std::string msg = "Player " + std::to_string(turn + 1) + " wins!";
				FString fMsg = msg.c_str();
				FMessageDialog::Debugf(FText::FromString(fMsg), &header);

				// TODO: Return to start menu; temporary fix is to just quit the application
				exit(0);
			}
			UE_LOG(LogClass, Log, TEXT("Ending turn for Player %d"), int(turn) + 1);

			turn = !turn;
			turnCounter++;

			turnPlayer = (turn) ? (playerTwo) : (playerOne);
			otherPlayer = (!turn) ? (playerTwo) : (playerOne);

			RecomputeDjikstra();

			//turnPlayer->AutoPossessPlayer = EAutoReceiveInput::Player0;
			//otherPlayer->AutoPossessPlayer = EAutoReceiveInput::Player1;

			//UE_LOG(LogClass, Log, TEXT("Beginning turn for Player %d"), int(turn) + 1);

			turnPlayer->currentStage = TurnStage::ApplyEffects;
			break;

		case TurnStage::Listening:
			//UE_LOG(LogClass, Log, TEXT("Listening for input from Player %d"), int(turn) + 1);
			break;
	}
}

int32 AGameManager::GetStage() const {
    return turnPlayer->currentStage;
}

void AGameManager::SetStage(int32 s) {
    turnPlayer->currentStage = (TurnStage)s;
}

AHexGridTile* AGameManager::GetTurnPlayerTile() const {
    return turnPlayer->currentTile;
}

void AGameManager::SetTurnPlayerTile(AHexGridTile* targetMoveTile) {
    turnPlayer->currentTile = targetMoveTile;
    turnPlayer->SetActorLocation(turnPlayer->currentTile->GetActorLocation() + FVector(0.f, 0.f, 20.f));
    turnPlayer->currentStage = TurnStage::MoveEnd;
}

void AGameManager::RecomputeDjikstra() {
    for (TActorIterator<AHexGridGraphManager> actorIter(GetWorld()); actorIter; ++actorIter) {
        for (TActorIterator<AHexGridTile> actorIter(GetWorld()); actorIter; ++actorIter) {
            (*actorIter)->ClearPrevNodes();
        }
        (*actorIter)->SetSourceTileID(turnPlayer->currentTile->ID);
        (*actorIter)->ResetShortestPath();
        (*actorIter)->DjikstraLoop();
        (*actorIter)->SetShortestPath_Backwards(turnPlayer->currentTile);
    }
}

int AGameManager::GetTurnCounter() const {
    return turnCounter;
}

bool AGameManager::GetTurn() const {
    return turn;
}

AWizard* AGameManager::GetTurnPlayer() const {
    return turnPlayer;
}

ASpell* AGameManager::GetCurrentlySelectedSpell() const {
    return turnPlayer->spellbook->readiedSpells[turnPlayer->selectedSpell];
}

int AGameManager::GetCurrentlySelectedSpellIndex() const {
    return turnPlayer->selectedSpell;
}

void AGameManager::CastSpell(int i) {
    switch (i) {
    case 0:
        turnPlayer->spellOne();
        break;
    case 1:
        turnPlayer->spellTwo();
        break;
    case 2:
        turnPlayer->spellThree();
        break;
    case 3:
        turnPlayer->spellFour();
        break;
    case 4:
        turnPlayer->spellFive();
        break;
    }
}
