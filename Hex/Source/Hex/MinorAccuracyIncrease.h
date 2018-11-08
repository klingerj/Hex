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
	const int boost = 1;

  const static int id = 0;

	virtual int applyEffect(ASpell& s) const override;
  virtual const int getID() const override;
};
