// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParantClass.generated.h"

UCLASS()
class HOMEWORK5_API AParantClass : public AActor
{
	GENERATED_BODY()
public:
	// 변수를 에디터에서 언제든 수정 가능하도록 하는 매크로 UProperty, BlueprintReadWrite는 블루프린트에서 RW권한, 카테고리로 묶어줌
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveAndTurn")
	// double moveDistance;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveAndTurn")
	// double turnAngle;

private:
	int moveCount = 0;
	int eventCount = 0;
	double totalMoveDist = 0.f;
	FVector targetLocation;
	FRotator targetRotation;
	FVector startLocation;
	FVector positionBefore;
	bool isRotating = false;
	double distanceTrabled = 0.f;

	void printActorLocation();
	void printNextLocation();
	void eventTrigger();
	void getRandomTargetPosition();
	//void setRandomDirection();
	//void setRandomDistance();
	void move(float DeltaTime);
	void turn(float DeltaTime);
public:	
	// Sets default values for this actor's properties
	AParantClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
