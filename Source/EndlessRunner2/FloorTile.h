// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "FloorTile.generated.h"

class USceneComponent;
class UBoxComponent;

UCLASS()
class ENDLESSRUNNER2_API AFloorTile : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AFloorTile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* sceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* floorTile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* attachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* centerLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* rightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* leftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* triggerBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	FVector translation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	float destroyTime;
	
	FORCEINLINE const FTransform& GetAttachTransform() const{
		return attachPoint->GetComponentTransform();
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FTimerHandle destroyTimer;

	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunGameModeBase* runGameMode;

	// UFUNCTION()
	// void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	// 	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestroyTile();
};
