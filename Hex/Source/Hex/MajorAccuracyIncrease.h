// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "MajorAccuracyIncrease.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorAccuracyIncrease : public AResource
{
	GENERATED_BODY()
	
public:
	AMajorAccuracyIncrease();

public:
	const int boost = 15;

	virtual int applyEffect(ASpell& s) const override;
};
