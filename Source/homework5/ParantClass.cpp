// Fill out your copyright notice in the Description page of Project Settings.


#include "ParantClass.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AParantClass::AParantClass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParantClass::BeginPlay()
{
	Super::BeginPlay();
	startLocation = GetActorLocation();
	positionBefore = GetActorLocation();
	//setRandomDirection();
	//setRandomDistance();
	getRandomTargetPosition();
}

// Called every frame
void AParantClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	totalMoveDist += FVector::Dist(GetActorLocation(), positionBefore);
	positionBefore = GetActorLocation();
	printActorLocation();
	if (moveCount < 10) {
		if (isRotating)
			turn(DeltaTime);
		else
			move(DeltaTime);
	}
	else {

		FString DebugMsg = FString::Printf(TEXT("최종 이동거리 : %.2f, 50%% 확률 이벤트 횟수 : %.d"), totalMoveDist, eventCount);
		GEngine->AddOnScreenDebugMessage(3, 10, FColor::Yellow, DebugMsg);
	}

}

void AParantClass::printActorLocation()
{
	FVector location = GetActorLocation();
	FString DebugMsg = FString::Printf(TEXT("현재 위치 X : %.2f,X : %.2f,X : %.2f | %d번째 이동."), location.X, location.Y, location.Z, moveCount+1);
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, DebugMsg);
}

void AParantClass::printNextLocation()
{
	FString DebugMsg = FString::Printf(TEXT("다음 지점 X : %.2f,X : %.2f,X : %.2f"), targetLocation.X, targetLocation.Y, targetLocation.Z);
	GEngine->AddOnScreenDebugMessage(2, 5, FColor::Green, DebugMsg);
}

void AParantClass::eventTrigger()
{
	// 50% 이벤트 트리거?
	int trigger = FMath::RandRange(0, 1);
	if (trigger == 1)
		eventCount += 1;
}


void AParantClass::getRandomTargetPosition()
{
	// 초기 지점 기준 반경 1000 이내의 랜덤 지점 생성
	// VRAND()로 랜덤 0~1사이를 가진 3차원 벡터 * 1000거리를 곱해 지점 생성.
	FVector randomOffset = FMath::VRand() * FMath::RandRange(0.f, 1000.f);
	//시작지점에 값을더해서 시작지점 주변에서만 움직이도록.
	targetLocation = targetLocation + randomOffset;

	// 현재 위치에서 목표 지점을 바라보는 회전값 가져오기
	// #include "Kismet/KismetMathLibrary.h" 필수. 헤더에 가져오면 오류나니 참고.
	// FindLookAtRotation(시작점, 목표점)
	targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), targetLocation);
	
	eventTrigger();
	printNextLocation();
}





//void AParantClass::setRandomDirection()
//{	//미사용
//	//모든방향 무작위방향으로 회전
//	double randomYaw = FMath::RandRange(0.f, 360.f);
//	double randomPitch = FMath::RandRange(0.f, 360.f);
//	double randomRoll = FMath::RandRange(0.f, 360.f);
//  // 2개이상의 회전값을 쓰면 왜 회전이 멈추지 않는지??
//	// TargetRotation = FRotator{ randomPitch, randomYaw, randomRoll };
//	TargetRotation = FRotator{ 0, randomYaw, 0 };\
//}
//
//void AParantClass::setRandomDistance()
//{	//미사용
//	FVector randomdirection = FMath::VRand();//무작위 방향의 벡터 포인트 반환.
//	auto dist = FMath::RandRange(500, 1000);//이동거리를 결정(500~1000)
//	TargetLocation = StartLocation + (dist*randomdirection);//현재지점 + 랜덤방향의 10~100거리 지점을 이동할 위치로 지정함.
//
//}

void AParantClass::move(float DeltaTime) {
	// 액터의 현재 위치
	FVector CurrentLoc = GetActorLocation();
	// Vector-Interp-to, 벡터값 보간방식, 
	FVector NextLoc = FMath::VInterpTo(CurrentLoc, targetLocation, DeltaTime, 5.f);
	SetActorLocation(NextLoc);
	if (FVector::Dist(CurrentLoc, targetLocation) < 10.f)
	{
		moveCount += 1;
		if (moveCount < 10) {
			getRandomTargetPosition();// 목표 지점 초기화
			isRotating = true;// 다음부터 회전 호출하도록
		}
	}
}

void AParantClass::turn(float DeltaTime) {
	// 액터의 현재 회전값
	FRotator CurrentRot = GetActorRotation();
	// Rotate-Interp-to, 회전값 보간방식, 
	FRotator NextRot = FMath::RInterpTo(CurrentRot, targetRotation, DeltaTime, 5.f);
	SetActorRotation(NextRot);
	if (CurrentRot.Equals(targetRotation, 1.0f))
	{
		isRotating = false;// 이동 호출하도록
	}
}
