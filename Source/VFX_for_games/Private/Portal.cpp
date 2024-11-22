#include "Portal.h"

#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"


APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("_Collider"));
	RootComponent = _Collider;

	_Portal = CreateDefaultSubobject<UNiagaraComponent>(TEXT("_Portal"));
	_Portal->SetupAttachment(RootComponent);

	_Uses = 3;
}

void APortal::Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (_bCanTeleport)
	{
		_Partner->_bCanTeleport = false;
		OtherActor->SetActorLocation(_Partner->GetActorLocation());
		DecrementUses();
		_Partner->DecrementUses();
	}
}

void APortal::Handle_EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	_bCanTeleport = true;
}

void APortal::DecrementUses()
{
	_Uses--;
	if (_Uses == 0) {Destroy();}
}

void APortal::BeginPlay()
{
	Super::BeginPlay();

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APortal::Handle_Overlap);
	_Collider->OnComponentEndOverlap.AddUniqueDynamic(this, &APortal::Handle_EndOverlap);
}
