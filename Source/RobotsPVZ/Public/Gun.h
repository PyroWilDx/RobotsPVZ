#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UArrowComponent;
class UNiagaraComponent;
class AMainPlayer;
class AZombie;

UCLASS()
class ROBOTSPVZ_API AGun : public AActor {
	GENERATED_BODY()

public:
	AGun();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//void OnLaserOverlap(UPrimitiveComponent *OverlappedComponent,
	//	AActor *OtherActor, UPrimitiveComponent *OtherComp,
	//	int32 OtherBodyIndex, bool bFromSweep,
	//	const FHitResult &SweepResult);

	UArrowComponent *GetForwardArrow();

	void SetLaserShooting(bool Value);

	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent *GunMesh;

	UPROPERTY(VisibleDefaultsOnly)
	UArrowComponent *ForwardArrow;

	UPROPERTY(VisibleDefaultsOnly)
	UNiagaraComponent *LaserNiagara;

	UPROPERTY(VisibleDefaultsOnly)
	UNiagaraComponent *LaserImpactNiagara;

	UPROPERTY(VisibleDefaultsOnly)
	AMainPlayer *Character;

	UPROPERTY(EditDefaultsOnly, Category = "Laser Property")
	float LaserMaxDistance = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Laser Property")
	FVector LaserScale = { 1.f, 1.f, 1.f };

	UPROPERTY(EditDefaultsOnly, Category = "Laser Property")
	FVector LaserImpactScale = { 1.f, 1.f, 1.f };

	UPROPERTY(EditDefaultsOnly, Category = "Laser Property")
	FLinearColor LaserColor = { 0, 0, 0, 0 };

private:
	bool LaserShooting;

	AZombie *LastHitZombie;

};
