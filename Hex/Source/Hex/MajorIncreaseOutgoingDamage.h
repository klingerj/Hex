// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MajorIncreaseOutgoingDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorIncreaseOutgoingDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMajorIncreaseOutgoingDamage();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
