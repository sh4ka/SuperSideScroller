// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickableActor_Base.h"
#include "PickableActor_Collectable.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API APickableActor_Collectable : public APickableActor_Base
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void PlayerPickedUp(ASuperSideScroller_Player* Player) override;

public:
	UPROPERTY(EditAnywhere, Category=Collectable)
	int32 CollectableValue = 1;
	
};
