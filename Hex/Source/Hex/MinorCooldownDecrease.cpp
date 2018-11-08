// Fill out your copyright notice in the Description page of Project Settings.

#include "MinorCooldownDecrease.h"
#include "GameManager.h"
#include "HexGridTile.h"
#include "Wizard.h"
#include "EngineUtils.h"
#include "Engine/World.h"

AMinorCooldownDecrease::AMinorCooldownDecrease() : ASpell(Element::Earth, SpellType::Terrain, "Chill", 0, 0, 50, 2, 1) {
	description = "Element: Earth, Decrease the selected tile's cooldown by 1 turn, Accuracy: 50%, Range: 2";
}

SpellResult AMinorCooldownDecrease::cast() {
	SpellResult result(0, 0, 0, 0);
	switch (std::get<0>(ASpell::cast())) {
	case 0:
	{
		for (TActorIterator<AGameManager> actorIter(GetWorld()); actorIter; ++actorIter) {
			AHexGridTile* currentTile = (*actorIter)->turnPlayer->currentTile;
			currentTile->hexGridTileEffect->AdvanceCooldown();
		}
		break;
	}
	}

	return result;
}



