// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorDecreaseOutgoingDamage.h"

AMinorDecreaseOutgoingDamage::AMinorDecreaseOutgoingDamage() : ASpell(Element::Water, SpellType::BuffDebuff, "Soften", 0, 0, 100, 3, 1) {
	description = "Element: Water, Outgoing Damage Reduction: 10%, Accuracy: 100%, Range: 3";
}

SpellResult AMinorDecreaseOutgoingDamage::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<3>(result) = -10;
		break;
	case 1:
		// Failed to cast spell
		std::get<3>(result) = 0;
		break;
	}
	cooldownTurnsRemaining = 2;
	return result;
}

int AMinorDecreaseOutgoingDamage::getSpellID() {
	return 4;
}
