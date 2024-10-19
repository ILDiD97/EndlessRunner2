// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EndlessRunAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER2_API UEndlessRunAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
	float speed;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
	class APawn* pawnChar;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
	class UPawnMovementComponent* movementComponent;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;
};
