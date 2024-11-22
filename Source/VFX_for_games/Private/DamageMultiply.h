#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageMultiply.generated.h"

UINTERFACE()
class UDamageMultiply : public UInterface
{
	GENERATED_BODY()
};

class VFX_FOR_GAMES_API IDamageMultiply
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void MultiplyDamage(float Multiplier);
};
