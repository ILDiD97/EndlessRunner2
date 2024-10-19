// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
void UEndlessRunAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	if(pawnChar == nullptr){
		pawnChar = TryGetPawnOwner();
	}

	if(pawnChar){
		movementComponent = pawnChar->GetMovementComponent();
	}
}

void UEndlessRunAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if(pawnChar && movementComponent){
		bIsInAir = movementComponent->IsFalling();
		speed = pawnChar->GetVelocity().Size();
	}
}
