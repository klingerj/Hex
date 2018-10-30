// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridTileEffect.h"
#include "HexGridTile.generated.h"

UCLASS()
class HEX_API AHexGridTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexGridTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Components
  UHexGridTileEffect* hexGridTileEffect;
	
  // Blueprint variables
  uint32 gridIndexX, gridIndexY;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Djikstra")
  int distanceToMove;

  UFUNCTION(BlueprintCallable, Category = "Setup")
  void SetGridIndex();
};
