// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>
#include <vector>
#include "Spell.h"
#include "Inventory.h"

#include "MinorFireDamage.h"
#include "MinorElectricDamage.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spellbook.generated.h"

UCLASS()
class HEX_API ASpellbook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellbook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// STATE VARIABLES
	const int capacity = 5;
	int numSlotsFilled;
	
	// Needs to be an array of ASpell* instead of ASpell in order to get around a privacy error caused by GENERATED_BODY()
	std::array<ASpell*, 5> readiedSpells; // Second argument needs to be hardcoded?

	/// GAMEPLAY FUNCTIONS
	void addCraftedSpell(ASpell* s);
	void modifyExistingSpell(AInventory* inv, const std::vector<AResource>& resources, ASpell& s);
	void modifyExistingSpell(AInventory* inv, const AResource& r, ASpell& s);
};
