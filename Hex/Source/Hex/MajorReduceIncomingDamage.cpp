// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorReduceIncomingDamage.h"

AMajorReduceIncomingDamage::AMajorReduceIncomingDamage() : ASpell(Element::Water, SpellType::BuffDebuff, "Aegis", 0, 0, 100, 1, 1) {
	description = "Element: Water, Incoming Damage Reduction: 25%, Accuracy: 100%, Range: 1";
}

SpellResult AMajorReduceIncomingDamage::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<2>(result) = -25;
		break;
	case 1:
		// Failed to cast spell
		std::get<2>(result) = 0;
		break;
	}

	return result;
}


