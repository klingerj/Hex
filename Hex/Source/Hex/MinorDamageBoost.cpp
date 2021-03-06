// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorDamageBoost.h"

AMinorDamageBoost::AMinorDamageBoost() : AResource(EffectType::Damage, Rarity::Common) {}

int AMinorDamageBoost::applyEffect(ASpell& s) const {
	switch (AResource::applyEffect(s)) {
		// Proper resource application -- add effects to spell
		case 0:
		{
			s.damageMin += boost;
			s.damageMax += boost;

			std::string msg = s.name + " will now deal " + std::to_string(s.damageMin) + " - " + std::to_string(s.damageMax) + " " + s.elementToString() + " damage!";
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

const int AMinorDamageBoost::getID() const {
    return id;
}