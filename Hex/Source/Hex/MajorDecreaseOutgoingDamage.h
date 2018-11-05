// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MajorDecreaseOutgoingDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorDecreaseOutgoingDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMajorDecreaseOutgoingDamage();

public:
	virtual SpellResult cast() override;
	
	
};
