// Fill out your copyright notice in the Description page of Project Settings.

#include "Spell.h"

int ASpell::currId = 0;

// Sets default values
ASpell::ASpell() : id(currId++)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpell::cast() {
	// Implement in subclasses
}