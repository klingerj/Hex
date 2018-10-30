// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridGraphManager.h"
#include <iostream>
#include "Engine/World.h"
#include "EngineUtils.h"
#include "HexGridTile.h"


// Sets default values
AHexGridGraphManager::AHexGridGraphManager() : adjacencyMatrix(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHexGridGraphManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexGridGraphManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

uint32 Index2DTo1D(uint32 x, uint32 y, uint32 dim) {
    return y * dim + x;
}

void AHexGridGraphManager::PopulateAdjacencyMatrix() {
    // todo: need to get dimension of the grid
    uint32 dim = 3;

    adjacencyMatrix = new int[dim*dim*dim*dim];
    for (uint32 i = 0; i < dim*dim*dim*dim; ++i) {
        adjacencyMatrix[i] = -1;
    }

    for (TActorIterator<AHexGridTile> actorIter(GetWorld()); actorIter; ++actorIter) {
        AHexGridTile* actor = *actorIter;
        uint32 index1D = Index2DTo1D(actor->gridIndexX, actor->gridIndexY, dim);

        UE_LOG(LogClass, Log, TEXT("Current Actor's Indices: (%d, %d) which has a 1D index of %d"), actor->gridIndexX, actor->gridIndexY, index1D);
        UE_LOG(LogClass, Log, TEXT("Adjacency Matrix Before: "));
        for (uint32 i = 0; i < dim*dim; ++i) {
            UE_LOG(LogClass, Log, TEXT("Row %d: %d, %d, %d, %d, %d, %d, %d, %d, %d"), i, adjacencyMatrix[Index2DTo1D(0, i, dim*dim)], adjacencyMatrix[Index2DTo1D(1, i, dim*dim)], adjacencyMatrix[Index2DTo1D(2, i, dim*dim)], adjacencyMatrix[Index2DTo1D(3, i, dim*dim)], adjacencyMatrix[Index2DTo1D(4, i, dim*dim)], adjacencyMatrix[Index2DTo1D(5, i, dim*dim)], adjacencyMatrix[Index2DTo1D(6, i, dim*dim)], adjacencyMatrix[Index2DTo1D(7, i, dim*dim)], adjacencyMatrix[Index2DTo1D(8, i, dim*dim)]);
        }
        UE_LOG(LogClass, Log, TEXT("Adjacency Matrix Before: "));
        if (actor->gridIndexX == (uint32)0) { // left wall
            if (actor->gridIndexY == (uint32)0) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
            } else if (actor->gridIndexY == (uint32)(dim - 1)) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
            } else {
                if (actor->gridIndexY % 2 == (uint32)0) {
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                } else {
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                }
            }
        } else if (actor->gridIndexX == (uint32)(dim - 1)) { // right wall
            if (actor->gridIndexY == (uint32)0) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
            } else if (actor->gridIndexY == (uint32)(dim - 1)) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
            } else {
                if (actor->gridIndexY % 2 == (uint32)0) {
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                } else {
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                }
            }
        } else if (actor->gridIndexY == (uint32)0) { // top wall minus corners
            if (actor->gridIndexX > (uint32)0 && actor->gridIndexX < (uint32)(dim - 1)) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY + 1, dim)] = 1;
            }
        } else if (actor->gridIndexY == (uint32)(dim - 1)) { // bottom wall minus corners
            if (actor->gridIndexX > (uint32)0 && actor->gridIndexX < (uint32)(dim - 1)) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY - 1, dim)] = 1;
            }
        } else { // normal case
            if (actor->gridIndexY % 2 == (uint32)0) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
            } else {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY + 1, dim)] = 1;
            }
        }

        UE_LOG(LogClass, Log, TEXT("Adjacency Matrix After: "));
        for (uint32 i = 0; i < dim*dim; ++i) {
            UE_LOG(LogClass, Log, TEXT("Row %d: %d, %d, %d, %d, %d, %d, %d, %d, %d"), i, adjacencyMatrix[Index2DTo1D(0, i, dim*dim)], adjacencyMatrix[Index2DTo1D(1, i, dim*dim)], adjacencyMatrix[Index2DTo1D(2, i, dim*dim)], adjacencyMatrix[Index2DTo1D(3, i, dim*dim)], adjacencyMatrix[Index2DTo1D(4, i, dim*dim)], adjacencyMatrix[Index2DTo1D(5, i, dim*dim)], adjacencyMatrix[Index2DTo1D(6, i, dim*dim)], adjacencyMatrix[Index2DTo1D(7, i, dim*dim)], adjacencyMatrix[Index2DTo1D(8, i, dim*dim)]);
        }
    }
}
