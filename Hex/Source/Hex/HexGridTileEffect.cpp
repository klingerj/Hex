// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridTileEffect.h"
#include "EngineGlobals.h"


// Sets default values for this component's properties
UHexGridTileEffect::UHexGridTileEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHexGridTileEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
  /*if (GEngine) {
      GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hello world!"));
  }*/
}


// Called every frame
void UHexGridTileEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

