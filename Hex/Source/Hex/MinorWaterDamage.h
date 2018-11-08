// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorWaterDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorWaterDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorWaterDamage();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
