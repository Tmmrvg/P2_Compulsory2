// Copyright Epic Games, Inc. All Rights Reserved.


#include "P2Compulsory2GameModeBase.h"
#include "Target.h"
AP2Compulsory2GameModeBase::AP2Compulsory2GameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;
	WaveSize.Add(10);
	WaveSize.Add(15);
	WaveSize.Add(20);

	WaveDifficulty.Add(0.5);
	WaveDifficulty.Add(1);
	WaveDifficulty.Add(2);

	WaveSpawnFrequency.Add(2);
	WaveSpawnFrequency.Add(1);
	WaveSpawnFrequency.Add(0.5f);

	MinX = 2000;
	MaxX = 2200;

	MinY = -400;
	MaxY = 400;
	GameWon = false;


}

void AP2Compulsory2GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentWave = 1;
	LeftToSpawn = WaveSize[CurrentWave - 1];

}

void AP2Compulsory2GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Clock += DeltaTime;

	if (Clock > WaveSpawnFrequency[CurrentWave - 1] && !GameWon==true)
	{
		Clock = 0.f;
		FVector Location = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), 80);

		// Spawning
		AActor* Actor = GetWorld()->SpawnActor<AActor>(Target_BP, Location, FRotator::ZeroRotator);
		ATarget* target = Cast<ATarget>(Actor);

		// Changing Target Values
		target->MovementSpeed *= WaveDifficulty[CurrentWave - 1];
		LeftToSpawn--;
		if (LeftToSpawn <= 0)
		{
			ChangeWave(CurrentWave + 1);
		}
	}


}
void AP2Compulsory2GameModeBase::ChangeWave(int wave)
{
	if (WaveSize.Num() < wave)
	{
		// Game Won
		GameWon = true;
		return;
	}

	CurrentWave = wave;
	LeftToSpawn = WaveSize[CurrentWave - 1];

}
