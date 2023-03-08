// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "P2Compulsory2GameModeBase.generated.h"

class ATarget;
struct FInputActionValue;
//struct Wave
//{
//	Wave(int s, int d)
//	{
//		Size = s;
//		Difficulty = d;
//	}
//	int Size;
//	int Difficulty;
//};
UCLASS()
class P2COMPULSORY2_API AP2Compulsory2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

	public:
		AP2Compulsory2GameModeBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<float> WaveDifficulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<int> WaveSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<int> WaveSpawnFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MinX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MinY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int CurrentWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float Boolcheck;

	/** Blueprints: we set these in our blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TSubclassOf<ATarget> Target_BP;

	/** Blueprints: we set these in our blueprint */
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TSubclassOf<AMyPlayer> Player_BP;*/
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputAction* restart;

private:
	int LeftToSpawn;
	float Clock;
	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadWrite, Category = Bullet)
	bool GameWon;


	void ChangeWave(int wave);
	void Restart();
	





	

};
