// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorElectricDamage.h"

AMinorElectricDamage::AMinorElectricDamage() : ASpell(Element::Electricity, SpellType::Damage, "Minor Shock", 20, 30, 55, 5, 1) {
    description = "Element: Electricity, Damage: 20 - 30, Accuracy: 55%, Range: 5";
}

// Returns the amount of damage done to the opponent
SpellResult AMinorElectricDamage::cast() {
	SpellResult result(0, 0, 0, 0);
	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<0>(result) = rand() % (damageMax - damageMin) + damageMin;
		break;
	case 1:
		// Failed to cast spell
		std::get<0>(result) = 0;
		break;
	}

	// Remove resource-based bonuses
	accuracy = originalAccuracy;
	damageMin = originalMin;
	damageMax = originalMax;
	range = originalRange;

	return result;
}


