// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P2Compulsory2GameModeBase.generated.h"


class ATarget;
 
struct Wave
{
	Wave(int s, int d)
	{
		Size = s;
		Difficulty = d;
	}
	int Size;
	int Difficulty;
};
UCLASS()
class P2COMPULSORY2_API AP2Compulsory2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
	/**
	 *
	 */
	UCLASS()
		
		GENERATED_BODY()
	public:
		AP2Compulsory2GameModeBase();
	protected:
		virtual void BeginPlay() override;
	public:
		virtual void Tick(float DeltaTime) override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			TArray<int> WaveSize;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			TArray<float> WaveDifficulty;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			TArray<int> WaveSpawnFrequency;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			float minX;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			float maxX;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			float minY;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			float maxY;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			int CurrentWave;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			float leftXmin;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			float leftXmax;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			float behindYmin;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			float behindYmax;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
			TSubclassOf<ATarget> Target_BP;

		void ChangeWave(int wave);

	private:
		int LefttoSpawn;
		float clock;
		float spawnfrequency;







	

};
