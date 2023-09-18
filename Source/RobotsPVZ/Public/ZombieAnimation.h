#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZombieAnimation.generated.h"

class AZombie;

UCLASS()
class ROBOTSPVZ_API UZombieAnimation : public UAnimInstance {
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly);
	AZombie *Zombie;

};
