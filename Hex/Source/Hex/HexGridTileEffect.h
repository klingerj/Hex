// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HexGridTileEffect.generated.h"

class AResource;

enum TileElementType  { Element_Fire, Element_Water, Element_Earth, Element_Air };
enum TileFunctionType { Function_ResourceYield, Function_PassiveEffect };
enum TileYieldType { Resource_One, Resource_Two, PassiveEffect_One, PassiveEffect_Two };

typedef struct tile_yield_t {
    TileElementType element;
    TileYieldType yield;
    uint32 quantity;
} TileYield;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEX_API UHexGridTileEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHexGridTileEffect();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  // Tile resource
  TileYield Yield();
  TileElementType element;
  TileYieldType yield;
  uint32 yieldQuantity;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
  int type;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
  int rarity;

  // Cooldown logic

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
  int maxCooldownTurns;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cooldown")
  int remainingCooldownTurns;

  UFUNCTION(BlueprintCallable, Category = "Cooldown")
  void ResetCooldown();

  UFUNCTION(BlueprintCallable, Category = "Cooldown")
  bool IsOnCooldown() const;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  void AdvanceCooldown();

  AResource* resource;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  void SetResource();

  UFUNCTION(BlueprintCallable, Category = "Game State")
  AResource* GetResource() const;

  // Usage (by some global class)
  /*
  for each tile
    yield = tile.yield
    switch(yield)
    if yield is a resource: add to the inventory
    if yield is a passive effect: add to the list of active effects
  */
};
