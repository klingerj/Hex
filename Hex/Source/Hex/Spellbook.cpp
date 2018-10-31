// Fill out your copyright notice in the Description page of Project Settings.

#include "Spellbook.h"


// Sets default values
ASpellbook::ASpellbook() : numSlotsFilled(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpellbook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpellbook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpellbook::addCraftedSpell(int spellID) {
	if (numSlotsFilled < capacity) {
		readiedSpells.at(numSlotsFilled) = spellID;
		numSlotsFilled++;
	}
}

void ASpellbook::modifyExistingSpell(AInventory* inv, const std::vector<AResource>& resources, ASpell& s) {
	// Change spell stats based on resources passed in
	for (const AResource& r : resources) {
		if (inv->removeResources(r.getID())) {
			r.applyEffect(s);
		}
		else {
			// Resource removal didn't work -- add them back to the inventory to undo
			inv->addResources(r.getID());
		}
	}
}

