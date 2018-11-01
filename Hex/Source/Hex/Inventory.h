// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <map>
#include "Resource.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"

UCLASS()
class HEX_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// STATE VARIABLES
	// Current number of resources this player is carrying
	int numResources;
	// The inventory itself; a map from resource ID to how many of that resource we're currently carrying
	std::map<int, int> inventory;
	// Can only carry this many items *in total* (includes duplicates of the same resource)
	const int maxCapacity = 32;
	// Current number of items we're carrying
	int currentSize;

	// Number of unique resources in the game (can easily be changed as we think of more/pare down)
	const int numUniqueResources = 16;

	/// GAMEPLAY FUNCTIONS
	bool addResources(const std::vector<int>& resourceIDs); // Multiple at once
	bool addResources(int resourceID); // One at a time

	bool removeResources(const std::vector<int>& resourceIDs);
	bool removeResources(int resourceID);
	
};
