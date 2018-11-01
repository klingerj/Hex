#include "Wizard.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"

// Default constructor required; if nothing chosen for some reason, choose All-Around build
AWizard::AWizard() : AWizard(0) {}

// Sets default values
AWizard::AWizard(int className) : hasCast(false), hasCrafted(false), hasMoved(false), currentStage(AGameManager::ApplyEffects), other(nullptr), displayControls(false)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// This is getting set to true for some reason?
	this->SetActorHiddenInGame(false);

	// Possession (not sure how this works with multiplayer?)
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set stats according to character class (can obviously change these as we develop combat)
	//switch (className) {
	//	case WizardClass::AllAround:
	//		maxHealth = 1000;
	//		originalSpeed = 2;
	//		break;

	//	case WizardClass::Tank:
	//		maxHealth = 1500;
	//		originalSpeed = 1;
	//		break;

	//	case WizardClass::Scout:
	//		maxHealth = 700;
	//		originalSpeed = 3;
	//		break;

	//	case WizardClass::BuffDebuff:
	//		maxHealth = 800;
	//		originalSpeed = 2;
	//		break;

	//	case WizardClass::GlassCannon:
	//		maxHealth = 500;
	//		originalSpeed = 2;
	//		break;
	//}

	health = maxHealth;
	speed = originalSpeed;
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the inventory and spellbook
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		FVector spawn(0, 0, 0);

		inventory = World->SpawnActor<AInventory>(InvClass, spawn, FRotator(0.0f));
		spellbook = World->SpawnActor<ASpellbook>(SBookClass, spawn, FRotator(0.0f));
	}
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	this->SetActorHiddenInGame(false);
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Turn phase hotkeys
	PlayerInputComponent->BindAction("Cast", EInputEvent::IE_Pressed, this, &AWizard::castSpell);
	PlayerInputComponent->BindAction("Craft", EInputEvent::IE_Pressed, this, &AWizard::craftSpell);
	PlayerInputComponent->BindAction("Move", EInputEvent::IE_Pressed, this, &AWizard::move);
    PlayerInputComponent->BindAction("EndTurn", EInputEvent::IE_Pressed, this, &AWizard::endTurn);
    PlayerInputComponent->BindAction("DisplayControls", EInputEvent::IE_Pressed, this, &AWizard::ToggleControlDisplay);
	PlayerInputComponent->BindAction("EndTurn", EInputEvent::IE_Pressed, this, &AWizard::endTurn);

	// Spellcasting hotkeys
	// TODO: Uncomment the following 5 lines once input is appropriately set up
	//PlayerInputComponent->BindAction("Spell1", EInputEvent::IE_Pressed, this, &AWizard::hotkeyOne);
	//PlayerInputComponent->BindAction("Spell2", EInputEvent::IE_Pressed, this, &AWizard::hotkeyTwo);
	//PlayerInputComponent->BindAction("Spell3", EInputEvent::IE_Pressed, this, &AWizard::hotkeyThree);
	//PlayerInputComponent->BindAction("Spell4", EInputEvent::IE_Pressed, this, &AWizard::hotkeyFour);
	//PlayerInputComponent->BindAction("Spell5", EInputEvent::IE_Pressed, this, &AWizard::hotkeyFive);
}

/// GAMEPLAY FUNCTIONS
void AWizard::applyTileEffects() {
	// Only apply effects of the tile you start on
	if (hasMoved) {
		return;
	}

	// TODO: Implement the following
	// Tile currentTile = getCurrentTile();
	// if (!currentTile.isOnCooldown) {
		// std::vector<Resources> res = currentTile.collectResources();
		// inventory->addResources(res); // This call could also be in Tile::collectResources(), but this ensures we add to the proper wizard's inventory
	// }

	UE_LOG(LogClass, Log, TEXT("EFFECTS"));

	// Apply current tile's effects and collect resources
	currentStage = AGameManager::TurnStage::ApplyEffects;
}

void AWizard::castSpell() {
	if (this != gm->turnPlayer) {
		gm->turnPlayer->castSpell();
		return;
	}

	// Can't cast if you craft; can only cast once per turn
	if (hasCrafted || hasCast) {
		return;
	}

	UE_LOG(LogClass, Log, TEXT("CAST"));

	// Cast something
	// TODO: Read hotkey input, get appropriate spell from spellbook, check range vs. numTiles from opponent, cast spell

	hasCast = true;
	currentStage = AGameManager::TurnStage::Cast;
}

void AWizard::craftSpell() {
	if (this != gm->turnPlayer) {
		gm->turnPlayer->craftSpell();
		return;
	}
	// Can't craft if you casted; can only craft once per turn
	if (hasCast || hasCrafted) {
		return;
	}

	UE_LOG(LogClass, Log, TEXT("CRAFT"));

	// Craft something
	// TODO: spellbook->modifyExistingSpell(inventory, selectedResource, selectedSpell); need to prompt for selectedResource and selectedSpell

	hasCrafted = true;
	currentStage = AGameManager::TurnStage::Craft;
}

void AWizard::move() {
	if (this != gm->turnPlayer) {
		gm->turnPlayer->move();
		return;
	}
	// Can only move once per turn
	if (hasMoved) {
		return;
	}

	UE_LOG(LogClass, Log, TEXT("MOVE"));

	// Move to selected tile

	hasMoved = true;
	currentStage = AGameManager::TurnStage::Move;
}

void AWizard::endTurn() {
	if (this != gm->turnPlayer) {
		gm->turnPlayer->endTurn();
		return;
	}
	// Reset all turn-dependent state variables
	hasCast = false;
	hasCrafted = false;
	hasMoved = false;

	UE_LOG(LogClass, Log, TEXT("END"));

	currentStage = AGameManager::TurnStage::End;
}

int AWizard::GetHealth() const {
    return health;
}

void AWizard::ToggleControlDisplay() {
    if (this == gm->turnPlayer) {
        displayControls = !displayControls;
    } else {
        other->ToggleControlDisplay();
    }
}

bool AWizard::GetDisplayControls() {
    return displayControls;
}

void AWizard::hotkeyOne() {
	if (currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	spellbook->readiedSpells.at(0)->cast();
}

void AWizard::hotkeyTwo() {
	if (currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	spellbook->readiedSpells.at(1)->cast();
}

void AWizard::hotkeyThree() {
	if (currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	spellbook->readiedSpells.at(2)->cast();
}

void AWizard::hotkeyFour() {
	if (currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	spellbook->readiedSpells.at(3)->cast();
}

void AWizard::hotkeyFive() {
	if (currentStage != AGameManager::TurnStage::Cast) {
		return;
	}

	spellbook->readiedSpells.at(4)->cast();
}