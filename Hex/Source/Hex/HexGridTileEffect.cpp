// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridTileEffect.h"
#include "MinorDamageBoost.h"
#include "MajorDamageBoost.h"
#include "MajorAccuracyIncrease.h"
#include "MinorAccuracyIncrease.h"
#include "EngineGlobals.h"
#include "Engine/World.h"
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

void UHexGridTileEffect::SetResource(int type, int rarity) {
    switch (type) {
    case 0:
        switch (rarity) {
        case 0:
        {
            TSubclassOf<class AMinorDamageBoost> dmgClass;
            resource = GetWorld()->SpawnActor<AMinorDamageBoost>(dmgClass, FVector(0, 0, 0), FRotator(0.0f));
            break;
        }
        case 1:
            break;
        case 2:
        {
            TSubclassOf<class AMajorDamageBoost> dmgClass;
            resource = GetWorld()->SpawnActor<AMajorDamageBoost>(dmgClass, FVector(0, 0, 0), FRotator(0.0f));
            break;
        }
        case 3:
            break;
        }
        break;
    case 1:
        switch (rarity) {
        case 0:
        {
            TSubclassOf<class AMinorAccuracyIncrease> accClass;
            resource = GetWorld()->SpawnActor<AMinorAccuracyIncrease>(accClass, FVector(0, 0, 0), FRotator(0.0f));
            break;
        }
        case 1:
            break;
        case 2:
        {
            TSubclassOf<class AMajorAccuracyIncrease> accClass;
            resource = GetWorld()->SpawnActor<AMajorAccuracyIncrease>(accClass, FVector(0, 0, 0), FRotator(0.0f));
            break;
        }
        case 3:
            break;
        }
        break;
    case 2:
        switch (rarity) {
        case 0:
            //resource = new thingy;
            break;
        case 1:
            break;
        case 2:
            //resource = new thingy;
            break;
        case 3:
            break;
        }
        break;
    }
}
