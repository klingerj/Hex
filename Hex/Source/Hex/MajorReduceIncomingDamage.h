// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MajorReduceIncomingDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorReduceIncomingDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMajorReduceIncomingDamage();

public:
	virtual SpellResult cast() override;
	
	
};
