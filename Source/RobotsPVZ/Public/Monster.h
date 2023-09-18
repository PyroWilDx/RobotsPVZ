#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Monster.generated.h"

class UCapsuleComponent;
class UArrowComponent;
class UCharacterMovementComponent;
class AMainPlayer;

UCLASS()
class ROBOTSPVZ_API AMonster : public APawn {
	GENERATED_BODY()

public:
	AMonster();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(VisibleDefaultsOnly)
	UCapsuleComponent *HitBox;

	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent *ZombieMesh;

	UPROPERTY(VisibleDefaultsOnly)
	UArrowComponent *ForwardArrow;

	UPROPERTY(VisibleDefaultsOnly)
	UCharacterMovementComponent *MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	AMainPlayer *Character;

};
