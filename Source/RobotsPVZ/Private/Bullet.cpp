#include "Bullet.h"
#include "MainPlayer.h"

ABullet::ABullet() {
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));

	UStaticMesh *MeshObject = LoadObject<UStaticMesh>(nullptr,
		TEXT("/Game/Assets/Weapons/Weapons/Meshes/Ammunition/SM_Shell_545x39"));
	BulletMesh->SetStaticMesh(MeshObject);

	ShooterPlayer = nullptr;
}

void ABullet::Init(AMainPlayer *Shooter) {
	ShooterPlayer = Shooter;
}

void ABullet::BeginPlay() {
	Super::BeginPlay();

	SetActorScale3D(FVector(10.f, 10.f, 10.f));
}

void ABullet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector ForwardVector = GetActorForwardVector();
    FVector Movement = ForwardVector * 6000.f;
	Movement.Y = -Movement.Y;
	Swap(Movement.X, Movement.Y);
    SetActorLocation(GetActorLocation() + Movement * DeltaTime);

	if (GetDistanceTo(ShooterPlayer) > 10000.f) {
		Destroy();
	}
}

