// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "MajorDamageBoost.generated.h"

/**
 * 
 */
UCLASS()
class HEX_API AMajorDamageBoost : public AResource
{
	GENERATED_BODY()

public:
	AMajorDamageBoost();

public:
	const int boost = 3;

  const static int id = 3;

	virtual int applyEffect(ASpell& s) const override;
  virtual const int getID() const override;
};
