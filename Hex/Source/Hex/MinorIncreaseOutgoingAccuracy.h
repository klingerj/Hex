// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorIncreaseOutgoingAccuracy.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorIncreaseOutgoingAccuracy : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorIncreaseOutgoingAccuracy();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
