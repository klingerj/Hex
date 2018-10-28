// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridTileEffect.h"
#include "EngineGlobals.h"
#include <algorithm>

// Sets default values for this component's properties
UHexGridTileEffect::UHexGridTileEffect() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

  element = Element_Fire;
  maxCooldownTurns = 3;
  remainingCooldownTurns = 0;
}


// Called when the game starts
void UHexGridTileEffect::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UHexGridTileEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHexGridTileEffect::ResetCooldown() {
    remainingCooldownTurns = maxCooldownTurns;
}

bool UHexGridTileEffect::IsOnCooldown() const {
    return remainingCooldownTurns > 0;
}

void UHexGridTileEffect::AdvanceCooldown() {
    remainingCooldownTurns = remainingCooldownTurns == 0 ? 0 : remainingCooldownTurns - 1;
}

TileYield UHexGridTileEffect::Yield() {
    ResetCooldown();
    return { element, yield, yieldQuantity };
}
