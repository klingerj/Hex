// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorIncreaseOutgoingDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorIncreaseOutgoingDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorIncreaseOutgoingDamage();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
