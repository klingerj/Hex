// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorDecreaseOutgoingDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorDecreaseOutgoingDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorDecreaseOutgoingDamage();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
