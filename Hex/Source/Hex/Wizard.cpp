#include "Wizard.h"

// Default constructor required; if nothing chosen for some reason, choose All-Around build
AWizard::AWizard() : AWizard(0) {}

// Sets default values
AWizard::AWizard(int className)
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

}

/// GAMEPLAY FUNCTIONS
void AWizard::applyTileEffects() {

}

void AWizard::castSpell(int spell) {

}

void AWizard::craftSpell(int resource1, int resource2, int resource3) {

}

void AWizard::move(int tile) {

}

AGameManager::TurnStage AWizard::readInput() {
	return AGameManager::TurnStage::Listening;
}
