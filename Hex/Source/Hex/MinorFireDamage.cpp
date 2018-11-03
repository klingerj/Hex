// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorFireDamage.h"

AMinorFireDamage::AMinorFireDamage() : ASpell(Element::Fire, SpellType::Damage, "Minor Fireball", 10, 20, 70, 5, 1) {
    description = "Element: Fire, Damage: 10 - 20, Accuracy: 70%, Range: 5";
}

SpellResult AMinorFireDamage::cast() {
	SpellResult result(0,0,0,0);

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
