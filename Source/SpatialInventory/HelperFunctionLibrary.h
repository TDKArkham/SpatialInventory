// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperFunctionLibrary.generated.h"

class UItemObject;

/**
 * 
 */
UCLASS()
class SPATIALINVENTORY_API UHelperFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "SpawnActor")
	static AActor* SpawnActorFromItemObject(UItemObject* ItemObject, AActor* OriginLocationActor);
};
