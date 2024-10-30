#include "MainControl.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inputable.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AMainControl::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &AMainControl::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &AMainControl::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Triggered, this, &AMainControl::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &AMainControl::JumpReleased);
		EIP->BindAction(_AttackAction, ETriggerEvent::Started, this, &AMainControl::AttackPressed);
		EIP->BindAction(_AttackAction, ETriggerEvent::Completed, this, &AMainControl::AttackReleased);
		EIP->BindAction(_Ability1Action, ETriggerEvent::Started, this, &AMainControl::Ability1);
		EIP->BindAction(_Ability2Action, ETriggerEvent::Started, this, &AMainControl::Ability2);
		EIP->BindAction(_Ability3Action, ETriggerEvent::Started, this, &AMainControl::Ability3);
	}
}

void AMainControl::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
		{
			Subsystem->AddMappingContext(IInputable::Execute_GetMappingContext(InPawn), 0);
		}
	}

	UGameplayStatics::GetPlayerCameraManager(this, 0)->ViewPitchMax = 90;
	UGameplayStatics::GetPlayerCameraManager(this, 0)->ViewPitchMin = -90;
}

void AMainControl::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Look(CurrentPawn, LookVector);
		}
	}
}

void AMainControl::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Move(CurrentPawn, MoveVector);
		}
	}
}

void AMainControl::JumpPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpPressed(CurrentPawn);
		}
	}
}

void AMainControl::JumpReleased()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpReleased(CurrentPawn);
		}
	}
}

void AMainControl::AttackPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_AttackPressed(CurrentPawn);
		}
	}
}

void AMainControl::AttackReleased()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_AttackReleased(CurrentPawn);
		}
	}
}

void AMainControl::Ability1()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Ability1(CurrentPawn);
		}
	}
}

void AMainControl::Ability2()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Ability2(CurrentPawn);
		}
	}
}

void AMainControl::Ability3()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Ability3(CurrentPawn);
		}
	}
}
