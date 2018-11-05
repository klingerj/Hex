// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorDecreaseOutgoingAccuracy.h"

AMajorDecreaseOutgoingAccuracy::AMajorDecreaseOutgoingAccuracy() : ASpell(Element::Water, SpellType::BuffDebuff, "Smog", 0, 0, 100, 3, 1) {
	description = "Element: Water, Outgoing Accuracy Reduction: 15%, Accuracy: 100%, Range: 3";
}

SpellResult AMajorDecreaseOutgoingAccuracy::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<1>(result) = -15;
		break;
	case 1:
		// Failed to cast spell
		std::get<1>(result) = 0;
		break;
	}

	// Remove resource-based bonuses
	accuracy = originalAccuracy;
	damageMin = originalMin;
	damageMax = originalMax;
	range = originalRange;

	return result;
}


