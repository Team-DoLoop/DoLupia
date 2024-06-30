// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerTakeDamageWidget.h"

#include "Components/TextRenderComponent.h"
#include "Kismet/KismetTextLibrary.h"

// Sets default values
APlayerTakeDamageWidget::APlayerTakeDamageWidget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageTextRender = CreateDefaultSubobject <UTextRenderComponent>(TEXT("textRender"));
	DamageTextRender->SetupAttachment(RootComponent);
	DamageTextRender->SetTextRenderColor(FColor::Red);
}

// Called when the game starts or when spawned
void APlayerTakeDamageWidget::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerTakeDamageWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerTakeDamageWidget::SetDamageText(int32 Damage)
{
	FText _DamageText = UKismetTextLibrary::Conv_IntToText(Damage);
	DamageTextRender->SetText(_DamageText);
}

