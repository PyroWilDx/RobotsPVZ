#include "Monster.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AMonster::AMonster() {
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UCapsuleComponent>(FName("HitBox"));
	SetRootComponent(HitBox);

	ZombieMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMesh"));
	ZombieMesh->SetupAttachment(HitBox);

	ForwardArrow = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
	ForwardArrow->SetupAttachment(HitBox);

	MovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>(FName("Movement"));

	Character = nullptr;
}

void AMonster::BeginPlay() {
	Super::BeginPlay();

	Character = Cast<AMainPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AAIController *AIController =
		Cast<AAIController>(GetController());
	AIController->MoveToActor(Character);
}

void AMonster::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AMonster::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

