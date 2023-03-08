// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "MyPlayer.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATarget::ATarget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(100, 100, 100));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnOverlap);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());
	SkeletalMesh->SetRelativeScale3D(FVector(0.1f, 1.f, 1.f));
	SkeletalMesh->SetRelativeLocation(FVector(0.f, 0.f, 40));
	SkeletalMesh->SetRelativeRotation(FRotator());
	MovementSpeed = 350;
	RotationSpeed = 0.f;
	XKillPosition = -200.f;
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	/*RotationSpeed = FMath::RandRange(0.5f, 1.5f);*/
	MovementSpeed += FMath::RandRange(0, 250);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move
	FVector NewLocation = GetActorLocation();
	if (const APlayerController* pc = GetWorld()->GetFirstPlayerController())
		if (const APawn* Pawnpc = pc->GetPawn()) {
			const FVector PawnLocation = Pawnpc->GetActorLocation();
			FVector VectorPtoT = PawnLocation - NewLocation;
			VectorPtoT.Normalize();
			VectorPtoT *= FVector(1, 1, 0);
			
			SetActorLocation(NewLocation + VectorPtoT * MovementSpeed * DeltaTime);
		}

	//Rotate
	SetActorRotation(GetActorRotation() + FRotator(0, RotationSpeed, 0));

	//kill
	if (GetActorLocation().X < XKillPosition)
	{
		DestroyTarget();
	}
}

void ATarget::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AMyPlayer>())
	{
		Cast<AMyPlayer>(OtherActor)->HitByTarget();

		DestroyTarget();
	}
}

void ATarget::DestroyTarget()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}