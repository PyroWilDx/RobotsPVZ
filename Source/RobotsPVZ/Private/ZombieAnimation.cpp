#include "ZombieAnimation.h"
#include "Zombie.h"

void UZombieAnimation::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	Zombie = Cast<AZombie>(TryGetPawnOwner());	
}

void UZombieAnimation::NativeUpdateAnimation(float DeltaTime) {
	Super::NativeUpdateAnimation(DeltaTime);

}
