// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorCooldownIncrease.h"
#include "GameManager.h"
#include "HexGridTile.h"
#include "Wizard.h"
#include "EngineUtils.h"
#include "Engine/World.h"

AMajorCooldownIncrease::AMajorCooldownIncrease() : ASpell(Element::Earth, SpellType::Terrain, "Overheat", 0, 0, 40, 2, 1) {
	description = "Element: Earth, Increase the selected tile's cooldown by up to 4 turns,\n Accuracy: 40%, Range: 2";
}

SpellResult AMajorCooldownIncrease::cast() {
	SpellResult result(0, 0, 0, 0);
	switch (std::get<0>(ASpell::cast())) {
	case 0:
	{
		for (TActorIterator<AGameManager> actorIter(GetWorld()); actorIter; ++actorIter) {
			AHexGridTile* currentTile = (*actorIter)->turnPlayer->currentTile;
			currentTile->hexGridTileEffect->ResetCooldown();
		}
		break;
	}
	}
	cooldownTurnsRemaining = 4;
	return result;
}

int AMajorCooldownIncrease::getSpellID() {
	return 12;
}
