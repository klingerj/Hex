// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridGraphManager.h"
#include <iostream>
#include "Engine/World.h"
#include "EngineUtils.h"
#include "HexGridTile.h"
#include <vector>
#include <set>
#include <algorithm>

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
    uint32 dim = 5;

    adjacencyMatrix = new int[dim*dim*dim*dim];
    for (uint32 i = 0; i < dim*dim*dim*dim; ++i) {
        adjacencyMatrix[i] = -1;
    }

    for (TActorIterator<AHexGridTile> actorIter(GetWorld()); actorIter; ++actorIter) {
        AHexGridTile* actor = *actorIter;
        uint32 index1D = Index2DTo1D(actor->gridIndexX, actor->gridIndexY, dim);

        if (actor->gridIndexX == (uint32)0) { // left wall
            if (actor->gridIndexY == (uint32)0) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
            }
            else if (actor->gridIndexY == (uint32)(dim - 1)) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
            }
            else {
                if (actor->gridIndexY % 2 == (uint32)0) {
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                }
                else {
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                }
            }
        }
        else if (actor->gridIndexX == (uint32)(dim - 1)) { // right wall
            if (actor->gridIndexY == (uint32)0) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
            }
            else if (actor->gridIndexY == (uint32)(dim - 1)) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
            }
            else {
                if (actor->gridIndexY % 2 == (uint32)0) {
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                }
                else {
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                    adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                }
            }
        }
        else if (actor->gridIndexY == (uint32)0) { // top wall minus corners
            if (actor->gridIndexX > (uint32)0 && actor->gridIndexX < (uint32)(dim - 1)) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
            }
        }
        else if (actor->gridIndexY == (uint32)(dim - 1)) { // bottom wall minus corners
            if (actor->gridIndexX > (uint32)0 && actor->gridIndexX < (uint32)(dim - 1)) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
            }
        }
        else { // normal case
            if (actor->gridIndexY % 2 == (uint32)0) {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;

                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY + 1, dim)] = 1;    
            }
            else {
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX - 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX, actor->gridIndexY + 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY - 1, dim)] = 1;
                adjacencyMatrix[index1D * dim*dim + Index2DTo1D(actor->gridIndexX + 1, actor->gridIndexY + 1, dim)] = 1;
            }
        }
    }
    distances = new int[dim * dim];
    DjikstraLoop();
}

void AHexGridGraphManager::DjikstraLoop() {
    constexpr uint32 dim = 5;

    std::vector<AHexGridTile*> gridTiles;
    AHexGridTile* gridPtrs[dim*dim];
    int vertices[dim*dim];

    for (TActorIterator<AHexGridTile> actorIter(GetWorld()); actorIter; ++actorIter) {
        gridTiles.push_back(*actorIter);
        (*actorIter)->onShortestPath = false;
    }
    std::sort(gridTiles.begin(), gridTiles.end(), [](const AHexGridTile* lhs, const AHexGridTile* rhs) {
        return lhs->ID < rhs->ID;
    });
    for (size_t i = 0; i < gridTiles.size(); i++) {
        gridPtrs[i] = gridTiles[i];
    }

    for (int i = 0; i < dim*dim; i++) {
        vertices[i] = i;
    }

    vertices[sourceTileID] = -1; // this is the source vertex
    distances[sourceTileID] = 0;

    for (int i = 0; i < dim*dim; i++) {
        if (i == sourceTileID) { continue; }
        distances[i] = adjacencyMatrix[Index2DTo1D(i, sourceTileID, dim*dim)];
        if (distances[i] > 0) {
            gridPtrs[i]->AddPrevNode_Djikstra(gridPtrs[sourceTileID]);
        }
    }
    for (int i = 0; i < dim*dim; i++) {
        Djikstra(vertices, gridPtrs);
    }
    for (int i = 0; i < dim*dim; i++) {
        gridPtrs[i]->distanceToMove = distances[i];
    }
}

void AHexGridGraphManager::Djikstra(int* vertices, AHexGridTile* tiles[]) {
    constexpr uint32 dim = 5;
    int minValue = 500; // high number
    int minNode = 0;
    int oldMinNode = -1;

    for (int i = 0; i < dim*dim; i++) {
        if (vertices[i] == -1) {
            oldMinNode = i;
            continue;
        }
        if (distances[i] > 0 && distances[i] < minValue) {
            minValue = distances[i];
            minNode = i;
        }
    }

    vertices[minNode] = -1; // set the shortest vert to be the target of the next iteration

    for (int i = 0; i < dim*dim; i++) {
        if (adjacencyMatrix[Index2DTo1D(i, minNode, dim*dim)] < 0) { continue; }
        if (distances[i] < 0) {
            distances[i] = minValue + adjacencyMatrix[Index2DTo1D(i, minNode, dim*dim)];
            if (tiles[minNode]->ID != tiles[i]->ID) {
                tiles[i]->AddPrevNode_Djikstra(tiles[minNode]);
            }
            continue;
        }
        if ((distances[minNode] + adjacencyMatrix[Index2DTo1D(i, minNode, dim*dim)]) < distances[i]) {
            distances[i] = minValue + adjacencyMatrix[Index2DTo1D(i, minNode, dim*dim)];
        } else if ((distances[minNode] + adjacencyMatrix[Index2DTo1D(i, minNode, dim*dim)]) == distances[i]) {
            if (tiles[minNode]->ID != tiles[i]->ID) {
                tiles[i]->AddPrevNode_Djikstra(tiles[minNode]);
            }
        }
    }
}

// tell all tiles that lie on the shortest path that they do so they can be highlighted in the game
void AHexGridGraphManager::SetShortestPath_Backwards(AHexGridTile* targetTile) {
    if (targetTile->onShortestPath) {
        return;
    }
    targetTile->onShortestPath = true;
    const std::set<AHexGridTile*>& prevNodes = targetTile->prevNodes;
    for (AHexGridTile* node : prevNodes) {
        SetShortestPath_Backwards(node);
    }
}

void AHexGridGraphManager::ResetShortestPath() {
    for (TActorIterator<AHexGridTile> actorIter(GetWorld()); actorIter; ++actorIter) {
        (*actorIter)->onShortestPath = false;
    }
}

void AHexGridGraphManager::SetSourceTileID(int id) {
    sourceTileID = id;
}
