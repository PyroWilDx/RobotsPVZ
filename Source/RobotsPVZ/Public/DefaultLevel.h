#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "DefaultLevel.generated.h"

UCLASS()
class ROBOTSPVZ_API ADefaultLevel : public ALevelScriptActor {
	GENERATED_BODY()

public:
	ADefaultLevel();

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ZombieToSpawn;
	
	int ZombieCount;

};
