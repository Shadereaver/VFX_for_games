#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

class UInputMappingContext;

UINTERFACE()
class UInputable : public UInterface
{
	GENERATED_BODY()
};

class VFX_FOR_GAMES_API IInputable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Move(FVector2D Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Look(FVector2D Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_AttackPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_AttackReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Ability1();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Ability2();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Ability3();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInputMappingContext* GetMappingContext();
};
