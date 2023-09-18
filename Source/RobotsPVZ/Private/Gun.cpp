#include "Gun.h"
#include "MainPlayer.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Zombie.h"
#include "RobotsPVZ/RobotsPVZ.h"

AGun::AGun() {
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	SetRootComponent(GunMesh);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ForwardArrow"));
	ForwardArrow->SetupAttachment(GetRootComponent());

	LaserNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LaserNiagara"));
	LaserNiagara->SetupAttachment(ForwardArrow);
	LaserNiagara->SetVisibility(false);

	LaserImpactNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LaserImpactNiagara"));
	LaserImpactNiagara->SetupAttachment(ForwardArrow);
	LaserImpactNiagara->SetVisibility(false);

	Character = nullptr;

	LaserShooting = false;

	LastHitZombie = nullptr;
}

void AGun::BeginPlay() {
	Super::BeginPlay();

	LaserNiagara->SetRelativeScale3D(LaserScale);
	LaserNiagara->SetColorParameter(FName("Color"), LaserColor);

	LaserImpactNiagara->SetRelativeScale3D(LaserImpactScale);
	LaserImpactNiagara->SetColorParameter(FName("Color"), LaserColor);

	Character = Cast<AMainPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Character) {
		FAttachmentTransformRules TransformRules(
			EAttachmentRule::SnapToTarget, true);
		GunMesh->AttachToComponent(Character->GetMesh(), TransformRules,
			FName("RightHandSocket"));
		Character->SetGun(this);
	}

	//LaserNiagara->OnComponentBeginOverlap.AddDynamic(this,
	//			&AGun::OnLaserOverlap);
}

void AGun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (LastHitZombie && !LaserShooting) {
		LastHitZombie->SetIsBeingHurt(false);
		LastHitZombie = nullptr;
	}

	if (LaserShooting) {
		int ScreenX, ScreenY;
		APlayerController *PlayerController =
			UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FVector StartLocationRC, WorldDirection;
		PlayerController->GetViewportSize(ScreenX, ScreenY);
		PlayerController->DeprojectScreenPositionToWorld(
			ScreenX / 2.f,
			ScreenY / 2.f,
			StartLocationRC,
			WorldDirection
		);
		FVector EndLocationRC = StartLocationRC +
			WorldDirection * LaserMaxDistance;
		FHitResult HitResultRC;
		bool BlockingHitRC = GetWorld()->LineTraceSingleByChannel(
			HitResultRC,
			StartLocationRC,
			EndLocationRC,
			ECC_Camera
		);

		FVector LaserEndLocation = (BlockingHitRC) ?
			HitResultRC.Location : EndLocationRC;
		LaserNiagara->SetVectorParameter(FName("LaserEnd"),
			LaserEndLocation);

		if (LastHitZombie) {
			LastHitZombie->SetIsBeingHurt(false);
			LastHitZombie = nullptr;
		}

		LaserImpactNiagara->SetVisibility(BlockingHitRC);
		if (BlockingHitRC) {
			LaserImpactNiagara->SetWorldLocation(HitResultRC.Location);
		
			AZombie *Zombie = Cast<AZombie>(HitResultRC.GetActor());
			if (Zombie) {
				LastHitZombie = Zombie;
				Zombie->TakeDamage(0.1);
				Zombie->SetIsBeingHurt(true);
			}
		}
	}
}

//void AGun::OnLaserOverlap(UPrimitiveComponent *OverlappedComponent,
//		AActor *OtherActor, UPrimitiveComponent *OtherComp,
//		int32 OtherBodyIndex, bool bFromSweep,
//		const FHitResult &SweepResult) {
//	AZombie *Zombie = Cast<AZombie>(OtherComp->GetOwner());
//	if (Zombie) {
//		Zombie->TakeDamage(0.1);
//		Zombie->SetIsBeingHurt(true);
//	}
//}

UArrowComponent *AGun::GetForwardArrow() {
	return ForwardArrow;
}

void AGun::SetLaserShooting(bool Value) {
	if (Value && !LaserShooting) {
		LaserNiagara->SetVisibility(Value);
		LaserShooting = Value;
	}

	if (!Value && LaserShooting) {
		LaserNiagara->SetVisibility(Value);
		LaserImpactNiagara->SetVisibility(Value);
		LaserShooting = Value;
	}
}

