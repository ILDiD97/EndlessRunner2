// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"

#include "EndlessRunGameModeBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = sceneComponent;

	floorTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorTile"));
	floorTile -> SetupAttachment(sceneComponent);

	attachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachPoint"));
	attachPoint -> SetupAttachment(sceneComponent);

	// centerLane = CreateDefaultSubobject<UArrowComponent>(TEXT("CenterLane"));
	// centerLane -> SetupAttachment(sceneComponent);
	//
	// rightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("RightLane"));
	// rightLane -> SetupAttachment(sceneComponent);
	//
	// leftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftLane"));
	// leftLane -> SetupAttachment(sceneComponent);

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox -> SetupAttachment(sceneComponent);
	triggerBox -> SetBoxExtent(FVector(32.f,500.f,200.f));
	triggerBox -> SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();

	runGameMode = Cast<AEndlessRunGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(runGameMode);

	// triggerBox -> OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnTriggerBoxOverlap);
	
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector floorPosition = GetActorLocation() - (translation * DeltaTime);
	SetActorLocation(floorPosition);

	if(floorPosition.X < -400)
	{
		DestroyTile();
	}

}

void AFloorTile::DestroyTile()
{
	this->Destroy();
	bool obsSpawn = runGameMode->ManageFloorTile();
	runGameMode->AddFloorTile(obsSpawn);
}

// void AFloorTile::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	ARunCharacter* runChar = Cast<ARunCharacter>(OtherActor);
// 	if(runChar)
// 	{
// 		runGameMode->AddFloorTile();
//
// 		GetWorldTimerManager().SetTimer(destroyTimer, this, &AFloorTile::DestroyTile, destroyTime, false);
// 	}
// }


