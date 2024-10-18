#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class VFX_FOR_GAMES_API APlayerCharacter : public ACharacter, public IInputable
{

	GENERATED_BODY()

public:
	APlayerCharacter();
	
	virtual UInputMappingContext* GetMappingContext_Implementation() override;
	virtual void Input_AttackPressed_Implementation() override;
	virtual void Input_AttackReleased_Implementation() override;
	virtual void Input_Ability1_Implementation() override;
	virtual void Input_Ability2_Implementation() override;
	virtual void Input_Ability3_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D Value) override;
	virtual void Input_Move_Implementation(FVector2D Value) override;

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> _Arm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;
};
