// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorCooldownDecrease.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorCooldownDecrease : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorCooldownDecrease();

public:
	virtual SpellResult cast() override;
	
	
};
