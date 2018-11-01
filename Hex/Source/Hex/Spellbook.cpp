// Fill out your copyright notice in the Description page of Project Settings.

#include "Spellbook.h"


// Sets default values
ASpellbook::ASpellbook() : numSlotsFilled(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);

}

// Called when the game starts or when spawned
void ASpellbook::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);
	
}

// Called every frame
void ASpellbook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpellbook::addCraftedSpell(ASpell* s) {
	if (numSlotsFilled < capacity) {
		readiedSpells.at(numSlotsFilled) = s;
		numSlotsFilled++;
	}
	else {
		FText header = FText::FromString("SPELLBOOK FULL");
		FMessageDialog::Debugf(FText::FromString("You cannot add any more spells to your spellbook! Try modifying the ones you already have!"), &header);
	}
}

void ASpellbook::modifyExistingSpell(AInventory* inv, const std::vector<AResource>& resources, ASpell& s) {
	// Change spell stats based on resources passed in
	for (const AResource& r : resources) {
		if (inv->removeResources(r.getID())) {
			r.applyEffect(s);
		}
		else {
			FText header = FText::FromString("CANNOT MODIFY");
			FMessageDialog::Debugf(FText::FromString("You do not have the resources to do this!"), &header);
			// Resource removal didn't work -- add back to the inventory to undo
			inv->addResources(r.getID());
		}
	}
}

void ASpellbook::modifyExistingSpell(AInventory* inv, const AResource& r, ASpell& s) {
	if (inv->removeResources(r.getID())) {
		r.applyEffect(s);
	}
	else {
		FText header = FText::FromString("CANNOT MODIFY");
		FMessageDialog::Debugf(FText::FromString("You do not have the resources to do this!"), &header);
		// Resource removal didn't work -- add back to the inventory to undo
		inv->addResources(r.getID());
	}
}

