// Fill out your copyright notice in the Description page of Project Settings.


#include "RunCharacter.h"

#include "EndlessRunGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"


// Sets default values
ARunCharacter::ARunCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm -> TargetArmLength = 350.f;
	SpringArm -> SocketOffset = FVector(0.f,0.f,100.f);
	SpringArm -> bUsePawnControlRotation = true;
	SpringArm -> SetupAttachment(GetRootComponent());

	CameraFollow = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraFollow -> bUsePawnControlRotation = true;
	CameraFollow -> SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	RunGameModeBase = Cast<AEndlessRunGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameModeBase);
}

// Called every frame
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FRotator controlRot = GetControlRotation();

	controlRot.Roll = 0.f;
	controlRot.Pitch = 0.f;

	AddMovementInput(controlRot.Vector());
}

// Called to bind functionality to input
void ARunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARunCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARunCharacter::StopJumping);
	
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARunCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunCharacter::MoveRight);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ARunCharacter::MoveDown);
	
}



void ARunCharacter::ChangeLaneUpdate(float value)
{
	FVector location = GetCapsuleComponent()->GetComponentLocation();

	location.Y = FMath::Lerp(RunGameModeBase->laneSwitch[currentLane], RunGameModeBase->laneSwitch[nextLane],value);
	//location.Y = RunGameModeBase->laneSwitch[nextLane];
	
	SetActorLocation(location);
}

void ARunCharacter::ChangeLaneFinished()
{
	currentLane = nextLane;
	timelineActive = false;
}

void ARunCharacter::ChangeCameraLaneUpdate(float value)
{
	float offset;
	float rotation;
	
	if(side)
	{
		offset = 125.f;
		rotation = -25.f;
	}
	else
	{
		offset = -125.f;
		rotation = 25.f;
	}
	
	float offsetValue = FMath::Sin(value) * offset;
	float rotationValue = FMath::Sin(value) * rotation;

	SpringArm->SocketOffset.Y = offsetValue;
	
	FRotator rot = CameraFollow->GetComponentRotation();
	rot.Yaw = rotationValue;
	CameraFollow->SetRelativeRotation(rot);
}


void ARunCharacter::MoveLeft()
{
	if(!timelineActive)
	{
		nextLane = FMath::Clamp(currentLane -1, 0, 2);
		ChangeLane();
		CameraChangeLane();
		timelineActive = true;
		side = false;
	}
}

void ARunCharacter::MoveRight()
{
	if(!timelineActive)
	{
		nextLane = FMath::Clamp(currentLane +1, 0, 2);
		ChangeLane();
		CameraChangeLane();
		timelineActive = true;
		side = true;
	}
}

void ARunCharacter::MoveDown()
{
	UE_LOG(LogTemp, Warning, TEXT("ciaoD"));
}

