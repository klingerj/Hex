// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorEarthDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorEarthDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorEarthDamage();

public:
	virtual SpellResult cast() override;
	
	
};
