// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorIncreaseOutgoingDamage.h"

AMajorIncreaseOutgoingDamage::AMajorIncreaseOutgoingDamage() : ASpell(Element::Water, SpellType::BuffDebuff, "Intensify", 0, 0, 100, 1, 1) {
	description = "Element: Water, Outgoing Damage Boost: 25%, Accuracy: 100%, Range: 1";
}

SpellResult AMajorIncreaseOutgoingDamage::cast() {
	SpellResult result(0, 0, 0, 0);

	switch (std::get<0>(ASpell::cast())) {
	case 0:
		srand(time(nullptr));
		std::get<3>(result) = 25;
		break;
	case 1:
		// Failed to cast spell
		std::get<3>(result) = 0;
		break;
	}

	return result;
}



