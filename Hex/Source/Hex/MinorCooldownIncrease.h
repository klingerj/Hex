// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorCooldownIncrease.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorCooldownIncrease : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorCooldownIncrease();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
