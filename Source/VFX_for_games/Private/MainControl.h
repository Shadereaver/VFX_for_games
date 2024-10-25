#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainControl.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS(Abstract)
class VFX_FOR_GAMES_API AMainControl : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="input")
	TObjectPtr<UInputAction> _LookAction;
	UPROPERTY(EditAnywhere, Category="input")
	TObjectPtr<UInputAction> _MoveAction;
	UPROPERTY(EditAnywhere, Category="input")
	TObjectPtr<UInputAction> _JumpAction;
	UPROPERTY(EditAnywhere, Category="input")
	TObjectPtr<UInputAction> _AttackAction;
	UPROPERTY(EditAnywhere, Category="input")
	TObjectPtr<UInputAction> _Ability1Action;
	UPROPERTY(EditAnywhere, Category="input")
	TObjectPtr<UInputAction> _Ability2Action;
	UPROPERTY(EditAnywhere, Category="input")
	TObjectPtr<UInputAction> _Ability3Action;

	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();
	void AttackPressed();
	void AttackReleased();
	void Ability1();
	void Ability2();
	void Ability3();
};
