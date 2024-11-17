#include "Characters/MoveCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// C++ Program to show how to use
// sleep function
#include <iostream>

// Library effective with Windows
#include <windows.h>

// Library effective with Linux



#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"
// Constructor
AMoveCharacter::AMoveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup state and array for movement and limbs
	MoveState = 0;
	//LimbArray.Init(false, 4);

	//Create boom
	CamBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamBoom"));
	//Attach to character root
	CamBoom->SetupAttachment(GetRootComponent());
	//Distance from player
	CamBoom->TargetArmLength = 200.0f; 


	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	ViewCamera->SetupAttachment(CamBoom);

}
// Called when the game starts or when spawned
void AMoveCharacter::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void AMoveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MoveContext, 0);
		}
	}
	if (bIsMoving)
	{
		AddMovementInput(MovementDirection, 1.0f); // Continuous movement
	}

}
// Called to bind functionality to input
void AMoveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind MoveForward function
	//PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMoveCharacter::MoveForward);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMoveCharacter::Look);

		//GETTING INPUT FROM A KEY TRIGGERS THE HANDLE INPUT FUNCTION FOR THAT LIMB
		EnhancedInputComponent->BindAction(LeftLegAction, ETriggerEvent::Triggered, this, &AMoveCharacter::HandleLimbInput, 0);
		EnhancedInputComponent->BindAction(RightLegAction, ETriggerEvent::Triggered, this, &AMoveCharacter::HandleLimbInput, 1);
		EnhancedInputComponent->BindAction(LeftArmAction, ETriggerEvent::Triggered, this, &AMoveCharacter::HandleLimbInput, 2);
		EnhancedInputComponent->BindAction(RightArmAction, ETriggerEvent::Triggered, this, &AMoveCharacter::HandleLimbInput, 3);
	}
}



void AMoveCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	//AddControllerPitchInput(LookAxisVector.Y);
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		//AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMoveCharacter::HandleLimbInput(int32 LimbIndex)
{
	// Prevent duplicate input for the same limb
	//if (LimbArray[LimbIndex])
	//{
	//	return;
	//}

	//LimbArray[LimbIndex] = true;

	const float MoveDistance = 40.0f; // 0.5 meters
	FVector ForwardDirection = GetActorForwardVector();

	FTimerHandle MovementTimerHandle;

	// Check state transitions
	if (MoveState == 0 && LimbIndex == 0) //Right leg forward (we ignore 1,2)
	{
		UE_LOG(LogTemp, Log, TEXT("Entering State 1"));
		MovementDirection = GetActorForwardVector();
		bIsMoving = true;
		GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AMoveCharacter::StopMovement, 0.20f, false); //Move
		MoveState = 1;
	}
	if (MoveState == 1 && LimbIndex == 1) //Right leg forward (we ignore 1,2)
	{
		UE_LOG(LogTemp, Log, TEXT("Entering State 2"));
		MovementDirection = GetActorForwardVector();
		bIsMoving = true;
		GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AMoveCharacter::StopMovement, 0.20f, false); //Move
		MoveState = 2;
	}
	if (MoveState == 2 && LimbIndex == 2) //Right leg forward (we ignore 1,2)
	{
		UE_LOG(LogTemp, Log, TEXT("Entering State 3"));
		MovementDirection = GetActorForwardVector();
		bIsMoving = true;
		GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AMoveCharacter::StopMovement, 0.20f, false); //Move
		MoveState = 3;
	}
	if (MoveState == 3 && LimbIndex == 3) //Right leg forward (we ignore 1,2)
	{
		UE_LOG(LogTemp, Log, TEXT("Entering State 0"));
		MovementDirection = GetActorForwardVector();
		bIsMoving = true;
		GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AMoveCharacter::StopMovement, 0.20f, false); //Move
		MoveState = 0;
	}
}

int AMoveCharacter::GetMoveState()
{
	//UE_LOG(LogTemp, Log, TEXT("MoveState=", % d), Movestate));

	return MoveState;
}

void AMoveCharacter::StopMovement()
{
	UE_LOG(LogTemp, Log, TEXT("STOPPING MOVEMENT"));
	AddMovementInput(GetActorForwardVector(), 0.0f); // Stop movement input
	bIsMoving = false;

}

