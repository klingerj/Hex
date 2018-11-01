// Fill out your copyright notice in the Description page of Project Settings.

#include "HexGridTile.h"
#include "EngineGlobals.h"

// Sets default values
AHexGridTile::AHexGridTile() : distanceToMove(0), onShortestPath(false)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Init components
    //hexGridTileEffect = CreateDefaultSubobject<UHexGridTileEffect>(TEXT("Hex Grid Tile Effect Component"));
    //AddOwnedComponent(hexGridTileEffect);
}

// Called when the game starts or when spawned
void AHexGridTile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHexGridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHexGridTile::SetGridIndex() {
    // Get grid indices from blueprint properties
    // Taken from: https://answers.unrealengine.com/questions/161741/accessing-blueprint-variables-through-c.html
    static const FName gridIndexX_BP(TEXT("gridIndexX"));
    static const FName gridIndexY_BP(TEXT("gridIndexY"));
    static const FName ID_BP(TEXT("ID"));

    UClass* MyClass = GetClass();
    for (UProperty* Property = MyClass->PropertyLink; Property; Property = Property->PropertyLinkNext) {
        UIntProperty* property = Cast<UIntProperty>(Property);
        if (property && Property->GetFName() == gridIndexX_BP) {
            gridIndexX = property->GetPropertyValue(Property->ContainerPtrToValuePtr<int32>(this));
        }
        if (property && Property->GetFName() == gridIndexY_BP) {
            gridIndexY = property->GetPropertyValue(Property->ContainerPtrToValuePtr<int32>(this));
        }
        if (property && Property->GetFName() == ID_BP) {
            ID = property->GetPropertyValue(Property->ContainerPtrToValuePtr<int32>(this));
        }
    }
    
    // For debugging, print the grid index
    /*if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Grid index:( %i, %i)"), gridIndexX, gridIndexY));
    }*/
}

void AHexGridTile::AddPrevNode_Djikstra(AHexGridTile* node) {
    prevNodes.insert(node);
}

void AHexGridTile::ClearPrevNodes() {
    prevNodes.clear();
}

void AHexGridTile::SetGridEffect(UHexGridTileEffect* effect) {
	hexGridTileEffect = effect;
}
