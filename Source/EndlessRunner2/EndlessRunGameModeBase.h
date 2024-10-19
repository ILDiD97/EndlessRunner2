// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FloorTile.h"
#include "Obstacle.h"
#include "EndlessRunGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER2_API AEndlessRunGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public: 

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AFloorTile> floorTileClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AObstacle> obstacleClass;
	
	UPROPERTY(EditAnywhere, Category = "Config")
	int32 numMaxTile = 10;

	UPROPERTY(EditAnywhere, Category = "Config")
	TArray<float> laneSwitch;

	UPROPERTY(EditAnywhere, Category = "Config")
	TArray<AFloorTile*> tiles;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	FTransform nextSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	FVector currentSpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	float add;

	UPROPERTY()
	FTimerHandle addTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	float addTime;
	
	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorTile();

	UFUNCTION(BlueprintCallable)
	bool ManageFloorTile();
	
	UFUNCTION(BlueprintCallable)
	void AddFloorTile(const bool bSpawnObs);
	
protected:

	virtual void BeginPlay() override;
};
