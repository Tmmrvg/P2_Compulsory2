// Copyright Epic Games, Inc. All Rights Reserved.


#include "P2Compulsory2GameModeBase.h"
#include "Target.h"
#include "MyPlayer.h"

AP2Compulsory2GameModeBase::AP2Compulsory2GameModeBase()
{


	PrimaryActorTick.bCanEverTick = true;
	WaveSize.Add(10);
	WaveSize.Add(15);
	WaveSize.Add(20);

	WaveDifficulty.Add(1.0f);
	WaveDifficulty.Add(1.25f);
	WaveDifficulty.Add(1.5f);

	WaveSpawnFrequency.Add(2);
	WaveSpawnFrequency.Add(1.5f);
	WaveSpawnFrequency.Add(1.0f);

	MinX = 2000;
	MaxX = 2200;

	MinY = -400;
	MaxY = 400;
	GameWon = false;
	Boolcheck = 0;
	/*AActor* PlayerActor = GetWorld()->SpawnActor<AActor>(Player_BP, FVector(0,0,40), FRotator::ZeroRotator);
		AMyPlayer* Player = Cast<AMyPlayer>(PlayerActor);*/

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

	if (Clock > WaveSpawnFrequency[CurrentWave - 1] && !GameWon == true)
	{
		Clock = 0.f;
		FVector Location = FVector(FMath::RandRange(MinX, MaxX), FMath::RandRange(MinY, MaxY), 70);

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

	Restart();
}
void AP2Compulsory2GameModeBase::ChangeWave(int wave)
{
	if (WaveSize.Num() < wave)
	{
		Boolcheck = 1;
		// Game Won
		GameWon = true;

		return;
	}

	CurrentWave = wave;
	LeftToSpawn = WaveSize[CurrentWave - 1];

}

void AP2Compulsory2GameModeBase::Restart()
{
	if (const APlayerController* pc = GetWorld()->GetFirstPlayerController()) 
	{
		if (AMyPlayer* Player = Cast<AMyPlayer>(pc->GetPawn()))
			{
				if (GameWon && Player->CanRestart)
				{
					CurrentWave = 1;
					LeftToSpawn = WaveSize[CurrentWave - 1];
					Player->CanRestart = false;
					GameWon = false;
					Player->GameOver = false;
					Player->Lives = 5;
					Player->SetActorLocation((FVector(0, 0, Player->GetActorLocation().Z)));
				}
				else if (Player->GameOver && Player->CanRestart)
				{
					CurrentWave = 1;
					LeftToSpawn = WaveSize[CurrentWave - 1];
					Player->CanRestart = false;
					GameWon = false;
					Player->GameOver = false;
					Player->Lives = 5;
					Player->SetActorLocation((FVector(0, 0, Player->GetActorLocation().Z)));

				}
			}
	}

}
