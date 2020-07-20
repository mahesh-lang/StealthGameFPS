// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 

	OvelapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OvelapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OvelapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OvelapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OvelapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OvelapComp;

	OvelapComp->SetHiddenInGame(false);
	OvelapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
	//get an event when we overlap the player component

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp->SetupAttachment(RootComponent);
}


void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	if (MyPawn == nullptr)
	{

		return;
	}

	if (MyPawn->bIsCarryingObjective)
	{

		AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (GM)
		{
			GM->CompleteMission(MyPawn);
		}
	}

	else {

		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);  //Static function. 
	}
	
		UE_LOG(LogTemp, Log, TEXT("Overlapped with Extraction Zone!"));

	


}

