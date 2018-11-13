// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MajorCooldownIncrease.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorCooldownIncrease : public ASpell
{
	GENERATED_BODY()
	
public:
	AMajorCooldownIncrease();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
