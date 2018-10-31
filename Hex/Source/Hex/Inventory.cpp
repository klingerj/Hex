// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory.h"
#include <algorithm>

// Sets default values
AInventory::AInventory() : currentSize(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize each entry in the inventory with a frequency of 0
	for (int i = 0; i < numUniqueResources; ++i) {
		inventory.insert(std::pair<int, int>(i, 0));
	}

	// Hide the actor and make sure it doesn't collide with anything
	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void AInventory::BeginPlay()
{
	Super::BeginPlay();

	// Just in case
	this->SetActorEnableCollision(false);
	this->SetActorHiddenInGame(true);
	
}

// Called every frame
void AInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Returns true if all desired resources were added
bool AInventory::addResources(const std::vector<int>& resourceIDs) {
	// Assumptions: Size of resources will never be larger than maxCapacity
	for (auto& id : resourceIDs) {
		// If collecting all resources would overflow the inventory, only pick up the first few entries
		if (currentSize >= maxCapacity) {
			// Could also modify the vec that was passed in and return that to tell the player which weren't added
			// or prompt them that only some can be picked up and ask them to choose?
			// Could look like:
				// if (!inv.addResources(resVec)) {
				//  Prompt player to choose and remove associated entries from resVec
				//  resVec.erase() entries chosen
				//  inv.addResources(resVec);
				// }
			return false;
		}

		// Increment the frequency of the resource with this ID
		inventory.at(id)++;
		currentSize++;
	}

	return true;
}

bool AInventory::addResources(int resourceID) {
	if (currentSize >= maxCapacity) {
		return false;
	}

	inventory.at(resourceID)++;
	currentSize++;
	return true;
}

// Returns true if all desired resources were removed
bool AInventory::removeResources(const std::vector<int>& resourceIDs) {
	// Assumptions: Size of resources will never be larger than maxCapacity
	for (auto& id : resourceIDs) {
		// This shouldn't be encountered since we will only be removing resources the player has, but just in case
		if (currentSize <= 0 || inventory.at(id) <= 0) {
			return false;
		}

		// Clamp minimum frequency of a resource to 0
		inventory.at(id) = std::max(inventory.at(id) - 1, 0);
		currentSize--;
	}

	return true;
}

bool AInventory::removeResources(int resourceID) {
	if (currentSize <= 0 || inventory.at(resourceID) <= 0) {
		return false;
	}

	inventory.at(resourceID) = std::max(inventory.at(resourceID) - 1, 0);
	currentSize--;
	return true;
}
