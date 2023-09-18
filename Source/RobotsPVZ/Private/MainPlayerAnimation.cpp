#include "MainPlayerAnimation.h"
#include "MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMainPlayerAnimation::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	Character = Cast<AMainPlayer>(TryGetPawnOwner());
	if (Character) {
		CharacterMovement = Character->GetCharacterMovement();
	}
}

void UMainPlayerAnimation::NativeUpdateAnimation(float DeltaTime) {
	Super::NativeUpdateAnimation(DeltaTime);

	if (CharacterMovement) {
		GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovement->Velocity);
		IsFalling = CharacterMovement->IsFalling();
	}

	if (Character) {
		IsShooting = Character->GetPlayerIsShooting();
		AimPitch = Character->GetControlRotation().Pitch;
		if (AimPitch > 90.f) {
			AimPitch = AimPitch - 360.f;
		}
	}
}
