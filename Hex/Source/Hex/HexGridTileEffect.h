// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Resource.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HexGridTileEffect.generated.h"

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

  int rarity;

  // Cooldown logic
  uint32 maxCooldownTurns;
  uint32 remainingCooldownTurns;
  void ResetCooldown();
  bool IsOnCooldown() const;
  void AdvanceCooldown();
  AResource* resource;

  UFUNCTION(BlueprintCallable, Category = "Game State")
  void SetResource();

  // Usage (by some global class)
  /*
  for each tile
    yield = tile.yield
    switch(yield)
    if yield is a resource: add to the inventory
    if yield is a passive effect: add to the list of active effects
  */
};
