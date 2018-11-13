// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorDecreaseOutgoingAccuracy.h"

AMinorDecreaseOutgoingAccuracy::AMinorDecreaseOutgoingAccuracy() : ASpell(Element::Water, SpellType::BuffDebuff, "Fog", 0, 0, 100, 3, 1) {
	description = "Element: Water, Outgoing Accuracy Reduction: 5%, Accuracy: 100%, Range: 3";
}

SpellResult AMinorDecreaseOutgoingAccuracy::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<1>(result) = -5;
		break;
	case 1:
		// Failed to cast spell
		std::get<1>(result) = 0;
		break;
	}
	cooldownTurnsRemaining = 2;
	return result;
}

int AMinorDecreaseOutgoingAccuracy::getSpellID() {
	return 17;
}
