// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorResistance.h"

// DO NOT USE THIS FILE!

AMinorResistance::AMinorResistance() {}

int AMinorResistance::applyEffect(ASpell& s) const {
	switch (AResource::applyEffect(s)) {
		// Proper resource application -- add effects to spell
	case 0:
	{
		//s.accuracy += boost;

		//std::string msg = "The next time you cast " + s.name + ", it will have an accuracy of " + std::to_string(s.accuracy) + "%!";
		//FString msgF(msg.c_str());
		//FText header = FText::FromString("SPELLCRAFT SUCCESSFUL");
		//FMessageDialog::Debugf(FText::FromString(msgF), &header);
		break;
	}
	// Improper application -- Do nothing
	case 1:
		return 1;
		break;
	}

	return 0;
}


