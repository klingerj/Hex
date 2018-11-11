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
  AHexGridTile* targetMoveTile;

  int turnCounter;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
  bool turnSwapped;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  int GetTurnCounter() const;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  bool GetTurn() const;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  AWizard* GetTurnPlayer() const;

	bool turn;
	enum TurnStage { ApplyEffects = 0, Cast = 1, Craft = 2, Move = 3, End = 4, Listening = 5, MoveEnd = 6, SpellSelected = 7 };

  UFUNCTION(BlueprintCallable, Category = "Game State")
  void Setup();

  UFUNCTION(BlueprintCallable, Category = "Game State")
  int32 GetStage() const;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  AHexGridTile* GetTurnPlayerTile() const;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  void SetTurnPlayerTile(AHexGridTile* targetMoveTile);

  UFUNCTION(BlueprintCallable, Category = "Game State")
  void SetStage(int32 s);

  UFUNCTION(BlueprintCallable, Category = "Player State")
  ASpell* GetCurrentlySelectedSpell() const;

  UFUNCTION(BlueprintCallable, Category = "Player State")
  int GetCurrentlySelectedSpellIndex() const;

  UFUNCTION(BlueprintCallable, Category = "Player State")
  void CastSpell(int i);

  UFUNCTION(BlueprintCallable, Category = "Player State")
  void AddSpellIDToSpellbook(int id);

  void RecomputeDjikstra();
};
