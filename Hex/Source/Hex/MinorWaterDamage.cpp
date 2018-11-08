// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorWaterDamage.h"

AMinorWaterDamage::AMinorWaterDamage() : ASpell(Element::Water, SpellType::Damage, "Splash", 5, 15, 85, 2, 1) {
	description = "Element: Water, Damage: 5 - 15, Accuracy: 85%, Range: 2";
}

SpellResult AMinorWaterDamage::cast() {
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

	return result;
}

int AMinorWaterDamage::getSpellID() {
	return 1;
}
