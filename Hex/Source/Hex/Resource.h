// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Resource.generated.h"

UCLASS()
class HEX_API AResource : public AActor
{
	GENERATED_BODY()
	
public:
	enum EffectType { Damage = 0, Accuracy = 1, Range = 2 };
	enum Rarity { Common = 0, Uncommon = 1, Rare = 2, Epic = 3 };

	// Sets default values for this actor's properties
	AResource();
	AResource(EffectType e, Rarity r);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Each resource will have a unique identifier
	int id;
	static int currId;

	// What aspect of a spell does this resource affect?
	
	EffectType affectedStat;

	// How rare is this resource? Higher rarity => appears less frequently but is more powerful
	Rarity rarity;

	// Total number of unique resources is at least (num of EffectTypes) * (num of Rarities)

	// Virtual function of the actual effect; to be specified in the individual resource subclasses
	virtual int applyEffect(ASpell& s) const;

	/// GETTERS
	int getID() const;
};
