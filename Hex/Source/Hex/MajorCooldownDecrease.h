// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MajorCooldownDecrease.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorCooldownDecrease : public ASpell
{
	GENERATED_BODY()
	
public:
	AMajorCooldownDecrease();

public:
	virtual SpellResult cast() override;
	
	
};