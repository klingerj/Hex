#include "Wizard.h"
#include "Components/InputComponent.h"

// Default constructor required; if nothing chosen for some reason, choose All-Around build
AWizard::AWizard() : AWizard(0) {}

// Sets default values
AWizard::AWizard(int className) : hasCast(false), hasCrafted(false), hasMoved(false), currentStage(AGameManager::ApplyEffects), other(nullptr), displayControls(false)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Possession (not sure how this works with multiplayer?)
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Set stats according to character class (can obviously change these as we develop combat)
	switch (className) {
		case WizardClass::AllAround:
			maxHealth = 1000;
			originalSpeed = 2;
			break;

		case WizardClass::Tank:
			maxHealth = 1500;
			originalSpeed = 1;
			break;

		case WizardClass::Scout:
			maxHealth = 700;
			originalSpeed = 3;
			break;

		case WizardClass::BuffDebuff:
			maxHealth = 800;
			originalSpeed = 2;
			break;

		case WizardClass::GlassCannon:
			maxHealth = 500;
			originalSpeed = 2;
			break;
	}

	health = maxHealth;
	speed = originalSpeed;
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Cast", EInputEvent::IE_Pressed, this, &AWizard::castSpell);
	PlayerInputComponent->BindAction("Craft", EInputEvent::IE_Pressed, this, &AWizard::craftSpell);
	PlayerInputComponent->BindAction("Move", EInputEvent::IE_Pressed, this, &AWizard::move);
  PlayerInputComponent->BindAction("EndTurn", EInputEvent::IE_Pressed, this, &AWizard::endTurn);
  PlayerInputComponent->BindAction("DisplayControls", EInputEvent::IE_Pressed, this, &AWizard::ToggleControlDisplay);
}

/// GAMEPLAY FUNCTIONS
void AWizard::applyTileEffects() {
	// Only apply effects of the tile you start on
	if (hasMoved) {
		return;
	}

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
