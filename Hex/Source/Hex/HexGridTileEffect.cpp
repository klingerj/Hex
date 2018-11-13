// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridTileEffect.h"
#include "Resource.h"
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
  maxCooldownTurns = 4;
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
    if (remainingCooldownTurns > 0) {
        UE_LOG(LogClass, Log, TEXT("Remaining Turns: %d"), remainingCooldownTurns);
    }
}

TileYield UHexGridTileEffect::Yield() {
    ResetCooldown();
    return { element, yield, yieldQuantity };
}

void UHexGridTileEffect::SetResource() {
    switch (type) {
    case 0:
        switch (rarity) {
        case 0:
        {
            TSubclassOf<class AMinorDamageBoost> dmgClass;
            resource = GetWorld()->SpawnActor<AMinorDamageBoost>(AMinorDamageBoost::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
			      UE_LOG(LogClass, Log, TEXT("Created a minor damage boost"));
            break;
        }
        case 1:
            UE_LOG(LogClass, Log, TEXT("type 0 rarity 1, which is nothing"));
            break;
        case 2:
        {
            TSubclassOf<class AMajorDamageBoost> dmgClass;
            resource = GetWorld()->SpawnActor<AMajorDamageBoost>(AMajorDamageBoost::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
			      UE_LOG(LogClass, Log, TEXT("Created a major damage boost"));
            break;
        }
        case 3:
            UE_LOG(LogClass, Log, TEXT("type 0 rarity 3, which is nothing"));
            break;
        }
        break;
    case 1:
        switch (rarity) {
        case 0:
        {
            TSubclassOf<class AMinorAccuracyIncrease> accClass;
            resource = GetWorld()->SpawnActor<AMinorAccuracyIncrease>(AMinorAccuracyIncrease::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
			      UE_LOG(LogClass, Log, TEXT("Created a minor accuracy increase"));
            break;
        }
        case 1:
            UE_LOG(LogClass, Log, TEXT("type 1 rarity 1, which is nothing"));
            break;
        case 2:
        {
            TSubclassOf<class AMajorAccuracyIncrease> accClass;
            resource = GetWorld()->SpawnActor<AMajorAccuracyIncrease>(AMajorAccuracyIncrease::StaticClass(), FVector(0, 0, 0), FRotator(0.0f));
			      UE_LOG(LogClass, Log, TEXT("Created a major accuracy increase"));
            break;
        }
        case 3:
            UE_LOG(LogClass, Log, TEXT("type 1 rarity 3, which is nothing"));
            break;
        }
        break;
    case 2:
        switch (rarity) {
        case 0:
            UE_LOG(LogClass, Log, TEXT("type 2 rarity 0, which is nothing"));
            break;
        case 1:
            UE_LOG(LogClass, Log, TEXT("type 2 rarity 1, which is nothing"));
            break;
        case 2:
            UE_LOG(LogClass, Log, TEXT("type 2 rarity 2, which is nothing"));
            break;
        case 3:
            UE_LOG(LogClass, Log, TEXT("type 2 rarity 3, which is nothing"));
            break;
        }
        break;
    }
    resource->hexGridTileEffect = this;
    UE_LOG(LogClass, Log, TEXT("set tile effect ptr for resource"));
}

AResource* UHexGridTileEffect::GetResource() const {
    return resource;
}
