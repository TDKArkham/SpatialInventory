// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemObject;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryChanged, UItemObject*, ChangedItemObject);

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

	FTile()
	{
		X = 0;
		Y = 0;
	}

	FTile(int32 InX, int32 InY)
	{
		X = InX;
		Y = InY;
	}

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

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ExposeOnSpawn = true))
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ExposeOnSpawn = true))
	int32 Rows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TArray<UItemObject*> Items;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryAddItem(UItemObject* ItemObjectToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CheckIsRoomAvailable(UItemObject* ItemObject, int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemAt(UItemObject* ItemObjectToAdd, int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(UItemObject* ItemObjectToRemove);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	FORCEINLINE FTile IndexToTile(int32 Index) { return FTile(Index % Columns, Index / Columns); }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	FORCEINLINE int32 TileToIndex(FTile Tile) { return Tile.X + Tile.Y * Columns; }
	FORCEINLINE int32 TileToIndex(int32 TileX, int32 TileY) { return TileX + TileY * Columns; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TMap<UItemObject*, FTile> GetAllItems() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory")
	static UInventoryComponent* GetInventoryComponent(AActor* TargetActor);
};
