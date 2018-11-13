// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorEarthDamage.h"

AMinorEarthDamage::AMinorEarthDamage() : ASpell(Element::Earth, SpellType::Damage, "Mudball", 10, 15, 80, 2, 1) {
	description = "Element: Earth, Damage: 10 - 15,\n Accuracy: 80%, Range: 2";
}

// Returns the amount of damage done to the opponent
SpellResult AMinorEarthDamage::cast() {
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
	cooldownTurnsRemaining = 2;
	return result;
}

int AMinorEarthDamage::getSpellID() {
	return 10;
}
