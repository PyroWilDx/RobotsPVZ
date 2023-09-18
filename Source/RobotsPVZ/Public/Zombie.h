#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

class UCapsuleComponent;
class AMainPlayer;

UCLASS()
class ROBOTSPVZ_API AZombie : public ACharacter {
	GENERATED_BODY()

public:
	AZombie();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void TakeDamage(double Value);

	void SetIsBeingHurt(bool Value);

	double GetHp();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	AMainPlayer *Character;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "State")
	bool IsBeingHurt;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Life")
	double Hp = 100.f;

};
