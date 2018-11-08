// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorReduceIncomingDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorReduceIncomingDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorReduceIncomingDamage();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
