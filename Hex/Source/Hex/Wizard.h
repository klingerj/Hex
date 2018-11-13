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
	enum WizardClass { AllAround = 0, Tank = 1, Scout = 2, BuffDebuff = 3, GlassCannon = 4 };

	AWizard();
	AWizard(WizardClass className);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void spawnInvAndSpellbook();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// GAMEPLAY FUNCTIONS
	// Turn phases
	void applyTileEffects();

	UFUNCTION(BlueprintCallable, Category = "Game State")
	void castSpell();

	void craftSpell();

	UFUNCTION(BlueprintCallable, Category = "Game State")
	void move();

	void startGame();

    UFUNCTION(BlueprintCallable, Category = "Game State")
	void endTurn();

	// Hotkey spells
	void hotkeyOne();
	void hotkeyTwo();
	void hotkeyThree();
	void hotkeyFour();
	void hotkeyFive();
	// Extra functions that correspond to hotkeys; blueprint callable
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void spellOne();
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void spellTwo();
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void spellThree();
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void spellFour();
	UFUNCTION(BlueprintCallable, Category = "Game State")
	void spellFive();

	/// STATE VARIABLES
	WizardClass charClass;
	// Current stats (modified by spells)
	int health, speed, outgoingDamageBuff, incomingDamageBuff, outgoingAccuracyBuff;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  int GetHealth() const;

  bool displayControls;
  void ToggleControlDisplay();

  UFUNCTION(BlueprintCallable, Category = "Setup")
  bool GetDisplayControls();

	// Max stats
	int maxHealth, originalSpeed;
	// Track if certain actions have been taken and what stage of the turn we're in
	bool hasCast, hasCrafted, hasMoved, gameNotStarted;
	AGameManager::TurnStage currentStage;
	// Maintain an inventory of collected resources
	AInventory* inventory;
	void showInventory();

	// Maintain a list of spells the player is able to cast
	ASpellbook* spellbook;
	TSubclassOf<class ASpellbook> SBookClass;
  void showSpellbook();
  int selectedSpell;

	AWizard* other;
	AGameManager* gm;
	AHexGridTile* currentTile; // the tile that the wizard is currently standing on
};
