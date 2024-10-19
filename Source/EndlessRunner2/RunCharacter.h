// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunCharacter.generated.h"

UCLASS()
class ENDLESSRUNNER2_API ARunCharacter : public ACharacter
{
	GENERATED_BODY()
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraFollow;

	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunGameModeBase* RunGameModeBase;
	
public:

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	int32 currentLane = 1;

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	int32 nextLane = 0;

	bool timelineActive = false;

	bool side = false;
	// Sets default values for this character's properties
	ARunCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeLane();

	UFUNCTION(BlueprintImplementableEvent)
	void CameraChangeLane();
	
	UFUNCTION(BlueprintCallable)
	void ChangeLaneUpdate(float value);

	UFUNCTION(BlueprintCallable)
	void ChangeLaneFinished();

	UFUNCTION(BlueprintCallable)
	void ChangeCameraLaneUpdate(float value);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveLeft();

	UFUNCTION()
	void MoveRight();

	UFUNCTION()
	void MoveDown();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
