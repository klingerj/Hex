// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "MajorDecreaseOutgoingAccuracy.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorDecreaseOutgoingAccuracy : public ASpell
{
	GENERATED_BODY()
	
public:
	AMajorDecreaseOutgoingAccuracy();

public:
	virtual SpellResult cast() override;
	
	
};
