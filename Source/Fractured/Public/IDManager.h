// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDManager.generated.h"

class ABaseActorWithID;

USTRUCT(BlueprintType)
struct FActorWithIDData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Json")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Json")
	int32 UniqueID;
};

USTRUCT(BlueprintType)
struct FActorsDetail
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Json)
	TArray<FActorWithIDData> Details;
};

UCLASS()
class FRACTURED_API AIDManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIDManager();

	int32 GenerateID(AActor* AimActor);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FActorsDetail ActorsDetail;
	
private:
	UPROPERTY()
	TArray<AActor*> TaggedActors;

	void SaveToJson();
	void LoadFromJson();
};
