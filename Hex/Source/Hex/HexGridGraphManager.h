// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridGraphManager.generated.h"

UCLASS()
class HEX_API AHexGridGraphManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexGridGraphManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  int* adjacencyMatrix;
  int* distances;

  UFUNCTION(BlueprintCallable, Category = "Adjacency Matrix")
  void PopulateAdjacencyMatrix();
  
  // https://www.coderslexicon.com/dijkstras-algorithm-for-c/
  void DjikstraLoop();
  void Djikstra(int* vertices);
};
