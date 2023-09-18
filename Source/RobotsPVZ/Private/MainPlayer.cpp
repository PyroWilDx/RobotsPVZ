#include "MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Misc/App.h"
#include "Gun.h"

AMainPlayer::AMainPlayer() {
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	PlayerMesh = GetMesh();

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(PlayerMesh);
	CameraBoom->TargetArmLength = 300.f;

	CameraView = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraView"));
	CameraView->SetupAttachment(CameraBoom);

	PlayerGun = nullptr;

	PlayerIsShooting = false;
	LaserChargeTimer = 0.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMainPlayer::SetGun(AGun *GunToSet) {
	PlayerGun = GunToSet;
}

void AMainPlayer::BeginPlay() {
	Super::BeginPlay();

}

void AMainPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this,
		&AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this,
		&AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this,
		&AMainPlayer::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this,
		&AMainPlayer::LookUp);
	PlayerInputComponent->BindAxis(FName("CameraZoom"), this,
		&AMainPlayer::CameraZoom);
	PlayerInputComponent->BindAxis(FName("Shoot"), this,
		&AMainPlayer::Shoot);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed,
		this, &AMainPlayer::Jump);
}

void AMainPlayer::MoveForward(float Value) {
	if (Controller && Value && !PlayerIsShooting) {
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainPlayer::MoveRight(float Value) {
	if (Controller && Value && !PlayerIsShooting) {
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainPlayer::Turn(float Value) {
	AddControllerYawInput(Value);
}

void AMainPlayer::LookUp(float Value) {
	AddControllerPitchInput(Value);
}

void AMainPlayer::CameraZoom(float Value) {
	if (Controller && Value) {
		CameraBoom->TargetArmLength = FMath::Clamp(
			CameraBoom->TargetArmLength + Value * 100.f,
			100.f, 800.f);
	}
}

void AMainPlayer::Shoot(float Value) {
	const float MinFOV = 42.f;
	const float MaxFOV = 90.f;
	const float ZoomSpeed = 400.f;

	if (Controller && Value && 
			!GetMovementComponent()->IsFalling()) {
		PlayerIsShooting = true;

		SetActorRotation(FRotator(
			GetActorRotation().Pitch,
			GetControlRotation().Yaw,
			GetActorRotation().Roll));

		if (CameraView->FieldOfView > MinFOV) {
			CameraView->SetFieldOfView(
				FMath::Max(MinFOV,
				CameraView->FieldOfView -
					ZoomSpeed * FApp::GetDeltaTime()));
		} else {
			if (LaserChargeTimer < LaserChargeTime) {
				LaserChargeTimer += GetWorld()->GetDeltaSeconds();
			} else {
				PlayerGun->SetLaserShooting(true);
			}
		}
	}

	if (Value == 0.f ||
		GetMovementComponent()->IsFalling()) {
		PlayerIsShooting = false;
		PlayerGun->SetLaserShooting(false);

		if (CameraView->FieldOfView < MaxFOV) {
			CameraView->SetFieldOfView(
				FMath::Min(MaxFOV,
					CameraView->FieldOfView +
						ZoomSpeed * FApp::GetDeltaTime()));
		}

		LaserChargeTimer = 0.f;
	}
}

void AMainPlayer::Jump() {
	Super::Jump();
}

bool AMainPlayer::GetPlayerIsShooting() {
	return PlayerIsShooting;
}
