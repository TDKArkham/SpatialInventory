// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemObject.h"

FIntPoint UItemObject::GetDimension() const
{
	return Dimension;
}

UMaterialInstance* UItemObject::GetIcon() const
{
	if(bIsRotated)
	{
		return IconRotated;
	}

	return Icon;
}
