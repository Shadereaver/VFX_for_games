#include "Wall.h"

#include "DamageMultiply.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWall::AWall()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("_Collider"));
	RootComponent = _Collider;
	_Collider->SetBoxExtent(FVector(200, 10, 125));

	_Wall = CreateDefaultSubobject<UNiagaraComponent>(TEXT("_Wall"));
	_Wall->SetupAttachment(RootComponent);

	InitialLifeSpan = 10;
}

void AWall::Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UDamageMultiply::StaticClass()))
	{
		IDamageMultiply::Execute_MultiplyDamage(OtherActor, 2);
	}
}

void AWall::BeginPlay()
{
	Super::BeginPlay();

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWall::Handle_Overlap);

}

