#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetRelativeLocation(FVector(0, 0, 40));
	StaticMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 1.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Ammo = 10;
	MaxAmmo = 10;
    MovementSpeed = 1000;
	Lives = 5;
	Bounds = 1000;
	
	CanRestart = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	checkRestart = 0;
	GameOver = false;
}


// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*FVector ForwardVector = FVector(XInput, YInput, 0.f);
	ForwardVector.Normalize();

	FVector NewLocation = GetActorLocation() + (ForwardVector * MovementSpeed * DeltaTime);
	SetActorLocation(NewLocation);*/

	PlayerPosX = GetActorLocation().X;
	PlayerPosY = GetActorLocation().Y;
	
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);

	if ((Controller != nullptr) && (XInput != 0.f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		SetActorLocation(GetActorLocation() + (Direction * XInput * MovementSpeed * DeltaTime));

		SetActorRotation(Rotation);
	}
	
	if ((Controller != nullptr) && (YInput != 0.f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;

		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		SetActorLocation(GetActorLocation() + (Direction * YInput * MovementSpeed * DeltaTime));

		SetActorRotation(Rotation);
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Get the player controller
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Triggered, this, &AMyPlayer::Forward);
        EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Triggered, this, &AMyPlayer::Right);
        EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Completed, this, &AMyPlayer::Forward);
        EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Completed, this, &AMyPlayer::Right);
        EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Triggered, this, &AMyPlayer::MouseX);
        EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Triggered, this, &AMyPlayer::MouseY);

        EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Completed, this, &AMyPlayer::MouseX);
        EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Completed, this, &AMyPlayer::MouseY);
        EnhanceInputCom->BindAction(ShootInput, ETriggerEvent::Started, this, &AMyPlayer::Shoot);
        EnhanceInputCom->BindAction(ReloadInput, ETriggerEvent::Started, this, &AMyPlayer::Reload);
		EnhanceInputCom->BindAction(RestartInput, ETriggerEvent::Started, this, &AMyPlayer::Restart);
    }
}


void AMyPlayer::MouseX(const FInputActionValue& input)
{
    float yaw = input.Get<float>();
    AddControllerYawInput(yaw);
}

void AMyPlayer::MouseY(const FInputActionValue& input)
{
    float pitch = input.Get<float>();
    AddControllerPitchInput(pitch);
}

void AMyPlayer::Forward(const FInputActionValue& input)
{
    XInput = input.Get<float>();

    if (PlayerPosX >= Bounds)
    {
	    SetActorLocation(FVector(PlayerPosX - 50, PlayerPosY, GetActorLocation().Z));
    }
	
    if(PlayerPosX <= -Bounds)
    {
    	SetActorLocation(FVector(PlayerPosX + 50, PlayerPosY, GetActorLocation().Z));
    }

	if (PlayerPosY >= Bounds)
	{
		SetActorLocation(FVector(PlayerPosX, PlayerPosY - 50, GetActorLocation().Z));
	}
	
	if(PlayerPosY <= -Bounds)
	{
		SetActorLocation(FVector(PlayerPosX, PlayerPosY  + 50, GetActorLocation().Z));
	}
}
void AMyPlayer::Right(const FInputActionValue& input)
{
    YInput = input.Get<float>();

	if (PlayerPosX >= Bounds)
	{
		SetActorLocation(FVector(PlayerPosX - 50, PlayerPosY, GetActorLocation().Z));
	}
	
	if(PlayerPosX <= -Bounds)
	{
		SetActorLocation(FVector(PlayerPosX + 50, PlayerPosY, GetActorLocation().Z));
	}

	if (PlayerPosY >= Bounds)
	{
		SetActorLocation(FVector(PlayerPosX, PlayerPosY - 50, GetActorLocation().Z));
	}
	
	if(PlayerPosY <= -Bounds)
	{
		SetActorLocation(FVector(PlayerPosX, PlayerPosY  + 50, GetActorLocation().Z));
	}
}

void AMyPlayer::HitByTarget()
{
	Lives--;
	if (Lives <= 0)
	{
		GameOver = true;
		return;
		// TODO : Game over
	}
}

void AMyPlayer::Shoot(const FInputActionValue& input)
{
    if (Ammo > 0)
    {
        Ammo--;

        if (Controller != nullptr)
        {
            FRotator Rotation = Controller->GetControlRotation();
            Rotation.Pitch = 0.f;
            Rotation.Roll = 0.f;

            FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

            GetWorld()->SpawnActor<AActor>(BP_Bullet,                                        // What to spawn
                                            GetActorLocation() + (Direction * 50.f), // Location
                                            Rotation);                                        // Rotation
        }
    }
}

void AMyPlayer::Reload(const FInputActionValue& input)
{
	Ammo = MaxAmmo;
}

void AMyPlayer::Restart(const FInputActionValue& input)
{
	CanRestart = true;
	checkRestart = 1;
}
