// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorIncreaseOutgoingAccuracy.h"

AMajorIncreaseOutgoingAccuracy::AMajorIncreaseOutgoingAccuracy() : ASpell(Element::Water, SpellType::BuffDebuff, "Crystal Clarity", 0, 0, 100, 1, 1) {
	description = "Element: Water, Outgoing Accuracy Boost: 15%, Accuracy: 100%, Range: 1";
}

SpellResult AMajorIncreaseOutgoingAccuracy::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<1>(result) = 15;
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


