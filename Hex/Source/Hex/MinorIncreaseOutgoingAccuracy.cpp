// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorIncreaseOutgoingAccuracy.h"

AMinorIncreaseOutgoingAccuracy::AMinorIncreaseOutgoingAccuracy() : ASpell(Element::Water, SpellType::BuffDebuff, "Clarity", 0, 0, 100, 1, 1) {
	description = "Element: Water, Outgoing Accuracy Boost: 5%,\n Accuracy: 100%, Range: 1";
}

SpellResult AMinorIncreaseOutgoingAccuracy::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<1>(result) = 5;
		break;
	case 1:
		// Failed to cast spell
		std::get<1>(result) = 0;
		break;
	}
	cooldownTurnsRemaining = 2;
	return result;
}

int AMinorIncreaseOutgoingAccuracy::getSpellID() {
	return 7;
}
