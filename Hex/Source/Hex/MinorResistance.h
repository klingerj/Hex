// Fill out your copyright notice in the Description page of Project Settings.

// DO NOT USE THIS FILE!

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "MinorResistance.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorResistance : public AResource
{
	GENERATED_BODY()
	
public:
	AMinorResistance();

public:
	const int boost = 5;

	virtual int applyEffect(ASpell& s) const override;
};
