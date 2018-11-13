// Fill out your copyright notice in the Description page of Project Settings.

#include "MajorCooldownDecrease.h"
#include "GameManager.h"
#include "HexGridTile.h"
#include "Wizard.h"
#include "EngineUtils.h"
#include "Engine/World.h"

AMajorCooldownDecrease::AMajorCooldownDecrease() : ASpell(Element::Earth, SpellType::Terrain, "Soothe", 0, 0, 50, 2, 1) {
	description = "Element: Earth, Decrease the selected tile's cooldown by up to 3 turns,\n Accuracy: 50%, Range: 2";
}

SpellResult AMajorCooldownDecrease::cast() {
	SpellResult result(0, 0, 0, 0);
	switch (std::get<0>(ASpell::cast())) {
	case 0:
	{
		for (TActorIterator<AGameManager> actorIter(GetWorld()); actorIter; ++actorIter) {
			AHexGridTile* currentTile = (*actorIter)->turnPlayer->currentTile;
			for (int i = 0; i < 3 && currentTile->hexGridTileEffect->remainingCooldownTurns > 0 ; ++i) {
				currentTile->hexGridTileEffect->AdvanceCooldown();
			}
		}
		break;
	}
	}
	cooldownTurnsRemaining = 4;
	return result;
}

int AMajorCooldownDecrease::getSpellID() {
	return 11;
}

