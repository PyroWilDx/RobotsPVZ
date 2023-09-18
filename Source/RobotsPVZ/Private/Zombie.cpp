#include "Zombie.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer.h"

AZombie::AZombie() {
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->SetGenerateOverlapEvents(true);

	Character = nullptr;

	IsBeingHurt = false;
}

void AZombie::BeginPlay() {
	Super::BeginPlay();

	Character = Cast<AMainPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AZombie::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
}

void AZombie::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZombie::TakeDamage(double Value) {
	Hp -= Value;
}

void AZombie::SetIsBeingHurt(bool Value) {
	IsBeingHurt = Value;
}

double AZombie::GetHp() {
	return Hp;
}
