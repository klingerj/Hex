// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"

// Initialize static variable
int AResource::currId = 0;

// Sets default values
AResource::AResource() : AResource(EffectType::Damage, Rarity::Common) {}

AResource::AResource(EffectType e, Rarity r) : id(currId++), affectedStat(e), rarity(r) {

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

int AResource::applyEffect(ASpell& s) const {
	// If we're using an AOE or Damage resource, we need to make sure the spell we're modifying is appropriate
	switch (affectedStat) {
		case EffectType::Damage:
			if (s.type != ASpell::SpellType::Damage) {
				FText header = FText::FromString("IMPROPER CRAFTING");
				FMessageDialog::Debugf(FText::FromString("Cannot modify non-Damage spell with Damage resource"), &header);
				return 1;
			}
			break;
	}

	return 0;

	// Implement the rest in subclasses (specific resources)
}

int AResource::getID() const {
	return id;
}