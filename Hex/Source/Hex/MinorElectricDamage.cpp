// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorElectricDamage.h"

AMinorElectricDamage::AMinorElectricDamage() : ASpell(Element::Electricity, SpellType::Damage, "Minor Shock", 20, 30, 55, 5, 1) {
    description = "Element: Electricity, Damage: 20 - 30, Accuracy: 55%, Range: 5";
}

// Returns the amount of damage done to the opponent
int AMinorElectricDamage::cast() {
	int damage = 0;
	switch (ASpell::cast()) {
	case 0:
		srand(time(nullptr));
		damage = rand() % (damageMax - damageMin) + damageMin;
		break;
	case 1:
		// Failed to cast spell
		damage = 0;
		break;
	}

	// Remove resource-based bonuses
	accuracy = originalAccuracy;
	damageMin = originalMin;
	damageMax = originalMax;
	range = originalRange;

	return damage;
}


