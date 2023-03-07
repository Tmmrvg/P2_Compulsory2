// Copyright Epic Games, Inc. All Rights Reserved.


#include "P2Compulsory2GameModeBase.h"

AP2Compulsory2GameModeBase::AP2Compulsory2GameModeBase()
{

	PrimaryActorTick.bCanEverTick = true;
	WaveSize.Add(10);
	WaveSize.Add(15);
	WaveSize.Add(20);
	WaveSize.Add(25);

	WaveDifficulty.Add(0.5);
	WaveDifficulty.Add(1);
	WaveDifficulty.Add(1.5);
	WaveDifficulty.Add(2);

	WaveSpawnFrequency.Add(2);
	WaveSpawnFrequency.Add(1.5);
	WaveSpawnFrequency.Add(1);
	WaveSpawnFrequency.Add(0.5);



	minX = 2000;
	maxX = 2200;

	minY = -1000;
	maxY = 1000;

	leftXmin = -2000;
	leftXmax = -2200;
	behindYmin = -4000;
	behindYmax = -3500;


}

void AP2Compulsory2GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentWave = 1;
	LefttoSpawn = WaveSize[CurrentWave - 1];

}

void AP2Compulsory2GameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	clock += DeltaTime;

	if (clock > WaveSpawnFrequency[CurrentWave - 1])
	{
		clock = 0.f;
		FVector location = FVector(FMath::RandRange(minX, maxX), FMath::RandRange(minY, maxY), 90);
		AActor* Actor = GetWorld()->SpawnActor<AActor>(Target_BP, location, FRotator::ZeroRotator);
		ATarget* Target1 = Cast<ATarget>(Actor);
		Target1->Enemyspeed *= WaveDifficulty[CurrentWave - 1];
		
		if (LefttoSpawn <= 0)
		{
			ChangeWave(CurrentWave + 1);
		}

		/*if(LefttoSpawn <= 0)
		{
			ChangeWave(CurrentWave + 1);
		}*/


	}
	if (clock > WaveSpawnFrequency[CurrentWave - 1])
	{



	}



}
void AP2Compulsory2GameModeBase::ChangeWave(int wave)
{
	if (WaveSize.Num() < wave)
	{
		return;

	}
	CurrentWave++;
	LefttoSpawn = WaveSize[CurrentWave - 1];

}
