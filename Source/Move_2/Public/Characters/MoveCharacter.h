// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InputActionValue.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MoveCharacter.generated.h"


class UInputMappingContext;
class UInputAction;



UCLASS()
class MOVE_2_API AMoveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMoveCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float Value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* MoveContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LeftLegAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RightLegAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LeftArmAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RightArmAction;


	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	void Look(const FInputActionValue& Value);
};