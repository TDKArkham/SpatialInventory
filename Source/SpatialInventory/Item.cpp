// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "InventoryComponent.h"
#include "Components/SphereComponent.h"

AItem::AItem()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetCollisionProfileName("NoCollision");
	RootComponent = StaticMeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereComponent->SetupAttachment(StaticMeshComponent);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnComponentBeginOverlap);

	if (ItemObject == nullptr)
	{
		ItemObject = GetDefaultItemObject();
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UInventoryComponent* InventoryComponent = UInventoryComponent::GetInventoryComponent(OtherActor);
	if (InventoryComponent)
	{
		if (InventoryComponent->TryAddItem(ItemObject))
		{
			Destroy();
		}
	}
}

UItemObject* AItem::GetDefaultItemObject_Implementation()
{
	return nullptr;
}
