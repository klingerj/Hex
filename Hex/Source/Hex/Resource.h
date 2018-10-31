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
	// Sets default values for this actor's properties
	AResource();

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
	enum EffectType { Damage = 0, Accuracy = 1, Range = 2, AreaOfEffect = 3 };
	EffectType affectedStat;

	// How rare is this resource? Higher rarity => appears less frequently but is more powerful
	enum Rarity {Common = 0, Uncommon = 1, Rare = 2, Epic = 3};
	Rarity rarity;

	// Total number of unique resources is at least (num of EffectTypes) * (num of Rarities)

	// Virtual function of the actual effect; to be specified in the individual resource subclasses
	virtual void applyEffect(ASpell& s) const;

	/// GETTERS
	int getID() const;
};
