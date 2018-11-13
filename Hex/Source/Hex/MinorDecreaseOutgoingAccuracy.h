// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MinorDecreaseOutgoingAccuracy.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorDecreaseOutgoingAccuracy : public ASpell
{
	GENERATED_BODY()
	
public:
	AMinorDecreaseOutgoingAccuracy();

public:
	virtual SpellResult cast() override;
	virtual int getSpellID() override;
	
};
