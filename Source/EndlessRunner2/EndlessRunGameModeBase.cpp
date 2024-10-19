// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunGameModeBase.h"

#include "FloorTile.h"
#include "Kismet/KismetMathLibrary.h"


void AEndlessRunGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CreateInitialFloorTile();
}

void AEndlessRunGameModeBase::CreateInitialFloorTile()
{
	for(int32 i = 0; i < numMaxTile; i++){
		AddFloorTile(false);
		currentSpawnPoint.X = add * i;
	}
	currentSpawnPoint.X -= 800.f;
	//GetWorldTimerManager().SetTimer(addTimer, this, &AEndlessRunGameModeBase::AddFloorTile, addTime, true);
}

bool AEndlessRunGameModeBase::ManageFloorTile()
{
	tiles.RemoveAt(0);

	float randChoice = FMath::FRandRange(0.f,1.f);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if(IsValid(obstacleClass))
	{
		
	}
	
	
	
	if(UKismetMathLibrary::InRange_FloatFloat(randChoice, 0.5, 1, true, true))
	{
		
	}
	
	return false;
}


void AEndlessRunGameModeBase::AddFloorTile(const bool bSpawnObs)
{
	UWorld* world = GetWorld();

	if(world && tiles.Num() < numMaxTile){
		AFloorTile* tile = world->SpawnActor<AFloorTile>(floorTileClass, nextSpawnPoint);

		if(tile){
			tiles.Add(tile);
			nextSpawnPoint.SetLocation(currentSpawnPoint);
			if(bSpawnObs)
			{
				
			}
		}
	}
}


