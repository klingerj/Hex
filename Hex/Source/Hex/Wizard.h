#pragma once

#include "GameManager.h"
#include "Inventory.h"
#include "Spellbook.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HexGridTile.h"
#include "Wizard.generated.h"

UCLASS()
class HEX_API AWizard : public APawn
{
	GENERATED_BODY()

public:
	AWizard();
	AWizard(int className);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// GAMEPLAY FUNCTIONS
	// Turn phases
	void applyTileEffects();
	void castSpell();
	void craftSpell();
	void move();
	void endTurn();
	// Hotkey spells
	void hotkeyOne();
	void hotkeyTwo();
	void hotkeyThree();
	void hotkeyFour();
	void hotkeyFive();

	/// STATE VARIABLES
	enum WizardClass { AllAround = 0, Tank = 1, Scout = 2, BuffDebuff = 3, GlassCannon = 4 };
	// Current stats (modified by spells)
	int health, speed;
	// Max stats
	int maxHealth, originalSpeed;
	// Track if certain actions have been taken and what stage of the turn we're in
	bool hasCast, hasCrafted, hasMoved;
	AGameManager::TurnStage currentStage;
	// Maintain an inventory of collected resources
	AInventory* inventory;
	TSubclassOf<class AInventory> InvClass;

	ASpellbook* spellbook;
	TSubclassOf<class ASpellbook> SBookClass;

	AWizard* other;
	AGameManager* gm;
  AHexGridTile* currentTile; // the tile that the wizard is currently standing on
};
