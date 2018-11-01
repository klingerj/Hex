// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "MinorAccuracyIncrease.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorAccuracyIncrease : public AResource
{
	GENERATED_BODY()
	
public:
	AMinorAccuracyIncrease();

public:
	const int boost = 5;

	virtual int applyEffect(ASpell& s) const override;
};
