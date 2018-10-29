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

	AWizard *playerOne, *playerTwo;
	AWizard* turnPlayer;

	bool turn;
	enum TurnStage { ApplyEffects = 0, Cast = 1, Craft = 2, Move = 3, End = 4, Listening = 5 };
	TurnStage currentStage;

};