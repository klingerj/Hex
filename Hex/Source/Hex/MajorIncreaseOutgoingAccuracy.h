// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MajorIncreaseOutgoingAccuracy.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorIncreaseOutgoingAccuracy : public ASpell
{
	GENERATED_BODY()
	
public:
	AMajorIncreaseOutgoingAccuracy();

public:
	virtual SpellResult cast() override;
	
	
};
