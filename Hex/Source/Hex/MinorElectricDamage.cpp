// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorElectricDamage.h"

AMinorElectricDamage::AMinorElectricDamage() : ASpell(Element::Electricity, SpellType::Damage, "Shock", 20, 30, 55, 2, 1) {
    description = "Element: Electricity, Damage: 20 - 30, Accuracy: 55%, Range: 2";
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
	// TODO: Delete these lines if we want resource boosts to be permanent
	accuracy = originalAccuracy;
	damageMin = originalMin;
	damageMax = originalMax;
	range = originalRange;

	return result;
}


