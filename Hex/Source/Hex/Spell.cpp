// Fill out your copyright notice in the Description page of Project Settings.

#include "Spell.h"
#include <ctime>

int ASpell::currId = 0;

// Sets default values
ASpell::ASpell() : ASpell(Element::Water, SpellType::Damage, "Default", 0, 0, 0, 0, 0) {}

ASpell::ASpell(Element e, SpellType t, std::string name, int baseDamageMin, int baseDamageMax, int baseAcc, int baseRange, int baseAOE) : 
	id(currId++), element(e), type(t), name(name), originalMin(baseDamageMin), originalMax(baseDamageMax), originalAccuracy(baseAcc), originalRange(baseRange),
	damageMin(baseDamageMin), damageMax(baseDamageMax), accuracy(baseAcc), range(baseRange), areaOfEffect(baseAOE), cooldownTurnsRemaining(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
	// Seed RNG with system time
	srand(time(nullptr));
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

SpellResult ASpell::cast() {
	int randCast = rand() % 100; // 0 to 99
	if (randCast >= accuracy) {
		// Failed to cast the spell
		FMessageDialog::Debugf(FText::FromString("Failed to cast spell!"));
		return std::make_tuple(1, 1, 1, 1);
	}

	return std::make_tuple(0, 0, 0, 0);
	// Further implemented in subclasses
}

std::string ASpell::elementToString() {
	switch (element) {
		case Water:
			return "Water";
			break;

		case Earth:
			return "Earth";
			break;

		case Fire:
			return "Fire";
			break;

		case Electricity:
			return "Electricity";
			break;
	}

	return "";
}

int ASpell::getSpellID() {
	return -1;
}

FString ASpell::GetDescription() const {
    return FString(description.c_str());
}
