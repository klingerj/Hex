#include "GameManager.h"
#include "Wizard.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "HexGridGraphManager.h"
#include <ctime>
#include <iostream>
#include <string>

// Sets default values
AGameManager::AGameManager() : playerOne(nullptr), playerTwo(nullptr), turnPlayer(nullptr), turnCounter(0), turnSwapped(false)
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

        FVector spawn(500, 500, 40000.0f);

        playerOne = World->SpawnActor<AWizard>(WizClass, spawn, FRotator(0.0f));
		UE_LOG(LogClass, Log, TEXT("Tried to spawn a wizard"));
		playerOne->spawnInvAndSpellbook();
    
        spawn = FVector(100, 100, 40000.0f);
        playerTwo = World->SpawnActor<AWizard>(WizClass, spawn, FRotator(0.0f, 180.0f, 0.0f));
		UE_LOG(LogClass, Log, TEXT("Tried to spawn a wizard"));
		playerTwo->spawnInvAndSpellbook();

        uint32 playerOneGridIndexX = 0;
        uint32 playerOneGridIndexY = 0;
        uint32 playerTwoGridIndexX = 4;
        uint32 playerTwoGridIndexY = 4;

        for (TActorIterator<AHexGridTile> actorIter(World); actorIter; ++actorIter) {
            if ((*actorIter)->gridIndexX == playerOneGridIndexX && (*actorIter)->gridIndexY == playerOneGridIndexY) {
                playerOne->currentTile = *actorIter;
            }
            else if ((*actorIter)->gridIndexX == playerTwoGridIndexX && (*actorIter)->gridIndexY == playerTwoGridIndexY) {
                playerTwo->currentTile = *actorIter;
            }
        }

		

        playerOne->SetActorLocation(FVector(playerOne->currentTile->GetActorLocation() + FVector(0, 0, 0)));
        playerTwo->SetActorLocation(FVector(playerTwo->currentTile->GetActorLocation() + FVector(0, 0, 0)));
		
		
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

    //turnPlayer->applyTileEffects();
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
        case DoCooldowns:
        {
            UE_LOG(LogClass, Log, TEXT("Advancing Cooldowns!"));

            for (TActorIterator<AHexGridTile> actorIter(GetWorld()); actorIter; ++actorIter) {
                AHexGridTile* currentTile = *actorIter;
                if (currentTile->hexGridTileEffect->remainingCooldownTurns > 0) {
                    UE_LOG(LogClass, Log, TEXT("About to advance cooldown for tile with ID %d, remaining turns = %d"), currentTile->ID, currentTile->hexGridTileEffect->remainingCooldownTurns);
                }
                currentTile->hexGridTileEffect->AdvanceCooldown();
                if (currentTile->hexGridTileEffect->remainingCooldownTurns > 0) {
                    UE_LOG(LogClass, Log, TEXT("Advanced cooldown for tile with ID %d, remaining turns = %d"), currentTile->ID, currentTile->hexGridTileEffect->remainingCooldownTurns);
                }
            }

            for (int i = 0; i < 5; ++i) {
                ASpell* s = turnPlayer->spellbook->readiedSpells.at(i);
                if (s != nullptr && s->cooldownTurnsRemaining > 0) {
                    turnPlayer->spellbook->readiedSpells.at(i)->cooldownTurnsRemaining--;
                }
            }
            turnPlayer->currentStage = TurnStage::Move;
            break;
        }
		case TurnStage::ApplyEffects:
		{
		turnPlayer->currentStage = TurnStage::Listening;
		break;
		}
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
            // Advance the cooldown for all tiles
			break;
    
		case TurnStage::MoveEnd:
		  UE_LOG(LogClass, Log, TEXT("Player %d moved"), int(turn) + 1);
          if (!turnPlayer->currentTile->hexGridTileEffect->IsOnCooldown()) { // if the tile is not on cooldown
            turnPlayer->currentTile->hexGridTileEffect->ResetCooldown(); // pretend we collected a resource
            }
		  turnPlayer->currentStage = TurnStage::ApplyEffects;
		  break;

		case TurnStage::SpellSelected:
			//UE_LOG(LogClass, Log, TEXT("Player %d has selected spell %d"), int(turn) + 1, turnPlayer->selectedSpell);
			break;

		case TurnStage::End:
			// TODO: Fix!
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
			turnSwapped = true;

			turnPlayer = (turn) ? (playerTwo) : (playerOne);
			otherPlayer = (!turn) ? (playerTwo) : (playerOne);

			RecomputeDjikstra();
			turnPlayer->currentStage = TurnStage::DoCooldowns;
			break;

		case TurnStage::Listening:
			//UE_LOG(LogClass, Log, TEXT("Listening for input from Player %d"), int(turn) + 1);
			break;

		case TurnStage::StartGame:
			
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
    turnPlayer->SetActorLocation(turnPlayer->currentTile->GetActorLocation());
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

void AGameManager::AddSpellIDToSpellbook(int id) {
    switch (id) { // TODO: clean this up a lot
    case 0:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorFireDamage>(AMinorFireDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor fire damage spell"));
        break;
    }
    case 1:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorWaterDamage>(AMinorWaterDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor water damage spell"));
        break;
    }
    case 2:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorIncreaseOutgoingDamage>(AMinorIncreaseOutgoingDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor increase outgoing damage spell"));
        break;
    }
    case 3:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorCooldownDecrease>(AMinorCooldownDecrease::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor cooldown decrease spell"));
        break;
    }
    case 4:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorDecreaseOutgoingDamage>(AMinorDecreaseOutgoingDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor decrease outgoing damage spell"));
        break;
    }
    case 5:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorElectricDamage>(AMinorElectricDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor electric damage spell"));
        break;
    }
    case 6:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorIncreaseOutgoingAccuracy>(AMinorIncreaseOutgoingAccuracy::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor increase outgoing accuracy spell"));
        break;
    }
    case 7:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorReduceIncomingDamage>(AMinorReduceIncomingDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor reduce incoming damage spell"));
        break;
    }
    case 8:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorCooldownIncrease>(AMinorCooldownIncrease::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor cooldown increase spell"));
        break;
    }
    case 9:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorEarthDamage>(AMinorEarthDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor earth damage spell"));
        break;
    }
    case 10:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMajorCooldownDecrease>(AMajorCooldownDecrease::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a major cooldown decrease spell"));
        break;
    }
    case 11:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMajorCooldownIncrease>(AMajorCooldownIncrease::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a major cooldown increase spell"));
        break;
    }
    case 12:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMajorDecreaseOutgoingAccuracy>(AMajorDecreaseOutgoingAccuracy::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a major decrease outgoing accuracy spell"));
        break;
    }
    case 13:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMajorDecreaseOutgoingDamage>(AMajorDecreaseOutgoingDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a major decrease outgoing damage spell"));
        break;
    }
    case 14:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMajorIncreaseOutgoingAccuracy>(AMajorIncreaseOutgoingAccuracy::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a major increase outgoing accuracy spell"));
        break;
    }
    case 15:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMajorIncreaseOutgoingDamage>(AMajorIncreaseOutgoingDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a major increase outgoing damage spell"));
        break;
    }
    case 16:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMajorReduceIncomingDamage>(AMajorReduceIncomingDamage::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a major reduce incoming damage spell"));
        break;
    }
    case 17:
    {
        ASpell* craftedSpell = GetWorld()->SpawnActor<AMinorDecreaseOutgoingAccuracy>(AMinorDecreaseOutgoingAccuracy::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
        turnPlayer->spellbook->addCraftedSpell(craftedSpell);
        UE_LOG(LogClass, Log, TEXT("Created a minor decrease outgoing accuracy spell"));
        break;
    }
    }
}
