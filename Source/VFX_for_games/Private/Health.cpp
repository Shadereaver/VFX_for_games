#include "Health.h"


UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = false;

	_MaxHealth = 100.f;
	_CurrentHealth = _MaxHealth;
}


void UHealth::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealth::DamageTaken);
}

void UHealth::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	AActor* DamageCauser)
{
	_CurrentHealth -= FMath::Min(_CurrentHealth, Damage);
	if (FMath::IsNearlyZero(_CurrentHealth)) {GetOwner()->Destroy();}
}
