// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorFireDamage.h"

AMinorFireDamage::AMinorFireDamage() : ASpell(Element::Fire, SpellType::Damage, "Minor Fireball", 10, 20, 70, 5, 1) {}

// Returns the amount of damage done to the opponent
int AMinorFireDamage::cast() {
	int damage = 0;
	switch (ASpell::cast()) {
	case 0:
		srand(time(nullptr));
		damage = rand() % (damageMax - damageMin) + damageMin;
		break;
	case 1:
		// Failed to cast spell
		damage = 0;
		break;
	}

	// Remove resource-based bonuses
	accuracy = originalAccuracy;
	damageMin = originalMin;
	damageMax = originalMax;
	range = originalRange;

	return damage;
}
