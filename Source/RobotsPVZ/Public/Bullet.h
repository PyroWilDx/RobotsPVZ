#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class AMainPlayer;

UCLASS()
class ROBOTSPVZ_API ABullet : public AActor {
	GENERATED_BODY()

public:
	ABullet();

	void Init(AMainPlayer *Shooter);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UStaticMeshComponent *BulletMesh;

	AMainPlayer *ShooterPlayer;

};
