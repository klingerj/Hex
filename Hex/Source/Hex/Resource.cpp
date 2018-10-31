// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"

// Initialize static variable
int AResource::currId = 0;

// Sets default values
AResource::AResource() : id(currId++), affectedStat(EffectType::Damage), rarity(Rarity::Common)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResource::applyEffect(ASpell& s) const {
	// If we're using an AOE or Damage resource, we need to make sure the spell we're modifying is appropriate
	switch (affectedStat) {
		case EffectType::AreaOfEffect:
			if (s.type != ASpell::SpellType::AOE) {
				UE_LOG(LogClass, Error, TEXT("Cannot modify non-AOE spell with AOE resource"));
			}
			return;
			break;

		case EffectType::Damage:
			if (s.type != ASpell::SpellType::Damage) {
				UE_LOG(LogClass, Error, TEXT("Cannot modify non-Damage spell with Damage resource"));
			}
			return;
			break;
	}

	// Implement the rest in subclasses (specific resources)
}

int AResource::getID() const {
	return id;
}
