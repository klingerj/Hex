// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorDecreaseOutgoingDamage.h"

AMajorDecreaseOutgoingDamage::AMajorDecreaseOutgoingDamage() : ASpell(Element::Water, SpellType::BuffDebuff, "Quell", 0, 0, 100, 3, 1) {
	description = "Element: Water, Outgoing Damage Reduction: 25%, Accuracy: 100%, Range: 3";
}

SpellResult AMajorDecreaseOutgoingDamage::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<3>(result) = -25;
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


