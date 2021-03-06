// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorAccuracyIncrease.h"

AMinorAccuracyIncrease::AMinorAccuracyIncrease() : AResource(EffectType::Accuracy, Rarity::Common) {}

int AMinorAccuracyIncrease::applyEffect(ASpell& s) const {
	switch (AResource::applyEffect(s)) {
		// Proper resource application -- add effects to spell
	case 0:
	{
		s.accuracy += boost;

		std::string msg = s.name + " now has an accuracy of " + std::to_string(s.accuracy) + "%!";
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

const int AMinorAccuracyIncrease::getID() const {
    return id;
}
