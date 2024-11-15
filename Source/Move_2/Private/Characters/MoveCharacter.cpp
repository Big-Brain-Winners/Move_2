// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MoveCharacter.h"


#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

// Sets default values
AMoveCharacter::AMoveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMoveCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMoveCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	//AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
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
	}



}

void AMoveCharacter::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, Value);
	}
}

