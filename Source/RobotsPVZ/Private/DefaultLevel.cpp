#include "DefaultLevel.h"
#include "Zombie.h"
#include "RobotsPVZ/RobotsPVZ.h"

ADefaultLevel::ADefaultLevel() {
	ZombieCount = 0;
}

void ADefaultLevel::Tick(float DeltaTime) {
	if (ZombieCount < 10) {
		AActor *SpawnedActor = GetWorld()->SpawnActor<AActor>(
			ZombieToSpawn,
			FVector(1000.f, 1000.f, 120.f),
			FRotator(0.f, 0.f, 0.f)
			);
		if (SpawnedActor) {
			ZombieCount++;
		}
	}
}
