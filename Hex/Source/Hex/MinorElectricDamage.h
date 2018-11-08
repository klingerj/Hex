// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorElectricDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorElectricDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorElectricDamage();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
};
