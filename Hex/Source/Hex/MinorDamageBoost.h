// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "MinorDamageBoost.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMinorDamageBoost : public AResource
{
	GENERATED_BODY()

public:
	AMinorDamageBoost();
	
public:
	const int boost = 5;

  const static int id = 2;

	virtual int applyEffect(ASpell& s) const override;
  virtual const int getID() const override;
};
