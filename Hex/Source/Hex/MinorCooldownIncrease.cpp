// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorCooldownIncrease.h"
#include "GameManager.h"
#include "HexGridTile.h"
#include "Wizard.h"
#include "EngineUtils.h"
#include "Engine/World.h"

AMinorCooldownIncrease::AMinorCooldownIncrease() : ASpell(Element::Earth, SpellType::Terrain, "Warm", 0, 0, 50, 2, 1) {
	description = "Element: Earth, Increase the selected tile's cooldown by 1 turn,\n Accuracy: 50%, Range: 2";
}

SpellResult AMinorCooldownIncrease::cast() {
	SpellResult result(0, 0, 0, 0);
	switch (std::get<0>(ASpell::cast())) {
	case 0:
	{
		// Get selected tile
		// Add 1 turn to tile's cooldown
		for (TActorIterator<AGameManager> actorIter(GetWorld()); actorIter; ++actorIter) {
			AHexGridTile* currentTile = (*actorIter)->turnPlayer->currentTile;
			currentTile->hexGridTileEffect->remainingCooldownTurns = std::min((uint32) currentTile->hexGridTileEffect->maxCooldownTurns, (uint32) currentTile->hexGridTileEffect->remainingCooldownTurns + 1);
		}
		break;
	}
	}
	cooldownTurnsRemaining = 2;
	return result;
}

int AMinorCooldownIncrease::getSpellID() {
	return 9;
}
