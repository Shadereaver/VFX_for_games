#include "Portal.h"

#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"


APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("_Collider"));
	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APortal::Handle_Overlap);
	RootComponent = _Collider;

	_Portal = CreateDefaultSubobject<UNiagaraComponent>(TEXT("_Portal"));
	_Portal->SetupAttachment(RootComponent);
}

void APortal::Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->SetActorLocation(_Partner->GetActorLocation());
}
