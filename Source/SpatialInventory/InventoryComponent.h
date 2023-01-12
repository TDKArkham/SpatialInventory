// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector2D End;
};

USTRUCT(BlueprintType)
struct FTile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Y;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPATIALINVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ExposeOnSpawn = true))
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ExposeOnSpawn = true))
	int32 Rows;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	static UInventoryComponent* GetInventoryComponent(AActor* TargetActor);
};
