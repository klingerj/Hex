// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorFireDamage.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorFireDamage : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorFireDamage();

public:
	virtual int cast() override;
};
