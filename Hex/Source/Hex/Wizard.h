#pragma once

#include "GameManager.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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
	void applyTileEffects();
	void castSpell(int spell);
	void craftSpell(int resource1, int resource2, int resource3);
	void move(int tile);
	AGameManager::TurnStage readInput();

	/// STATE VARIABLES
	enum WizardClass { AllAround = 0, Tank = 1, Scout = 2, BuffDebuff = 3, GlassCannon = 4 };
	// Current stats (modified by spells)
	int health, speed;
	// Max stats
	int maxHealth, originalSpeed;
};