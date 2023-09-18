#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainPlayerAnimation.generated.h"

class AMainPlayer;
class UCharacterMovementComponent;

UCLASS()
class ROBOTSPVZ_API UMainPlayerAnimation : public UAnimInstance {
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly);
	AMainPlayer *Character;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement);
	UCharacterMovementComponent *CharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement);
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement);
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category = Shooting);
	bool IsShooting;

	UPROPERTY(BlueprintReadOnly, Category = Shooting);
	float AimPitch;

};
