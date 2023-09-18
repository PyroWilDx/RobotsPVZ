#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class AGun;

UCLASS()
class ROBOTSPVZ_API AMainPlayer : public ACharacter {
	GENERATED_BODY()

public:
	AMainPlayer();

	void SetGun(AGun *GunToSet);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	void CameraZoom(float Value);

	void Shoot(float Value);

	virtual void Jump() override;

	UFUNCTION(BlueprintCallable)
	bool GetPlayerIsShooting();

	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent *PlayerMesh;

	UPROPERTY(VisibleDefaultsOnly)
	USpringArmComponent *CameraBoom;

	UPROPERTY(VisibleDefaultsOnly)
	UCameraComponent *CameraView;

	UPROPERTY(EditDefaultsOnly, Category = "Particle")
	float LaserChargeTime = 0.6f;
private:
	AGun *PlayerGun;

	bool PlayerIsShooting;
	float LaserChargeTimer;
};
