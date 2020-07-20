// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "FPSObjectiveActor.generated.h"


class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, category = "Components")
	UStaticMeshComponent* MeshComp;    // to visually see the component on the game.


	UPROPERTY(VisibleAnywhere, category = "Components")
	USphereComponent* SphereComp;   //this will hold collision information. 

	UPROPERTY(EditDefaultsOnly, category = "Effects")
	UParticleSystem* PickupFX;


	void PlayEffects(); //No one outside this class will be able to access this function. 

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
