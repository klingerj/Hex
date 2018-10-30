#pragma once

class AWizard;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class HEX_API AGameManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TSubclassOf<class AWizard> WizClass;

	// Players in the battle
	AWizard *playerOne, *playerTwo;
	// Set this as turns go on to apply effects to the AWizard whose turn it is
	AWizard *turnPlayer, *otherPlayer;

	bool turn;
	enum TurnStage { ApplyEffects = 0, Cast = 1, Craft = 2, Move = 3, End = 4, Listening = 5 };

};