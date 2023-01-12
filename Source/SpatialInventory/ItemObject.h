// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemObject.generated.h"

class AItem;

/**
 * 
 */
UCLASS(Blueprintable)
class SPATIALINVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemObject", meta = (ExposeOnSpawn = true))
	FIntPoint Dimension;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemObject", meta = (ExposeOnSpawn = true))
	UMaterialInstance* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemObject", meta = (ExposeOnSpawn = true))
	UMaterialInstance* IconRotated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemObject", meta = (ExposeOnSpawn = true))
	TSubclassOf<AItem> ItemClass;

	bool bIsRotated;

public:
	UFUNCTION(BlueprintCallable, Category = "ItemObject")
	FIntPoint GetDimension() const;
};
