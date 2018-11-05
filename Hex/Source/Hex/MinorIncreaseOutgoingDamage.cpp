// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorIncreaseOutgoingDamage.h"

AMinorIncreaseOutgoingDamage::AMinorIncreaseOutgoingDamage() : ASpell(Element::Water, SpellType::BuffDebuff, "Minor Overcharge", 0, 0, 100, 1, 1) {
	description = "Element: Water, Outgoing Damage Boost: 10%, Accuracy: 100%, Range: 1";
}

SpellResult AMinorIncreaseOutgoingDamage::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<3>(result) = 10;
		break;
	case 1:
		// Failed to cast spell
		std::get<3>(result) = 0;
		break;
	}

	// Remove resource-based bonuses
	accuracy = originalAccuracy;
	damageMin = originalMin;
	damageMax = originalMax;
	range = originalRange;

	return result;
}


