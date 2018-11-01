// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorDamageBoost.h"

AMajorDamageBoost::AMajorDamageBoost() : AResource(EffectType::Damage, Rarity::Rare) {}

int AMajorDamageBoost::applyEffect(ASpell& s) const {
	switch (AResource::applyEffect(s)) {
		// Proper resource application -- add effects to spell
	case 0:
	{
		s.damageMin += boost;
		s.damageMax += boost;

		std::string msg = "The next time you cast " + s.name + ", it will deal " + std::to_string(s.damageMin) + " - " + std::to_string(s.damageMax) + " " + s.elementToString() + " damage!";
		FString msgF(msg.c_str());
		FText header = FText::FromString("SPELLCRAFT SUCCESSFUL");
		FMessageDialog::Debugf(FText::FromString(msgF), &header);
		break;
	}
	// Improper application -- Do nothing
	case 1:
		return 1;
		break;
	}

	return 0;
}

const int AMajorDamageBoost::getID() const {
    return id;
}

