// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>
#include <vector>
#include "Spell.h"
#include "Inventory.h"

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
	
	std::array<int, 5> readiedSpells; // Second argument needs to be hardcoded?

	/// GAMEPLAY FUNCTIONS
	void addCraftedSpell(int spellID);
	void modifyExistingSpell(AInventory* inv, const std::vector<AResource>& resources, ASpell& s);
};
