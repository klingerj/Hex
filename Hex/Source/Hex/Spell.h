// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <ctime>
#include "MessageDialog.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

UCLASS()
class HEX_API ASpell : public AActor
{
	GENERATED_BODY()

public:	
	enum Element { Water = 0, Earth = 1, Fire = 2, Electricity = 3 };
	enum SpellType { Damage = 0, BuffDebuff = 1, Terrain = 2, AOE = 3 };
	// Sets default values for this actor's properties
	ASpell();
	ASpell(Element e, SpellType t, std::string name, int baseDamageMin, int baseDamageMax, int baseAcc, int baseRange, int baseAOE);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// PROPERTIES OF ALL SPELLS
	// Must be unique
	int id;
	static int currId;

	// Spell names should probably be unique too
	std::string name;
	
	Element element;
	SpellType type;

	// Member of (0, 100]
	int originalAccuracy;
	int accuracy;
	// Number of tiles representing how far from the player the spell can be cast/will reach
	int originalRange;
	int range;

	/// PROPERTIES OF SOME SPELLS -- All spells will have these fields, but they will be accessed based on the "type" variable
	// How much damage this does on hit (range)
	int originalMin, originalMax;
	int damageMin, damageMax;
	// Number of tiles affected when this spell hits (i.e. - its area of effect)
	int areaOfEffect;

	/// SPELL FUNCTIONS
	virtual int cast();

	/// UTILITY FUNCTIONS
	std::string elementToString();
};