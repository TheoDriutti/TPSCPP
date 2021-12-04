// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaveGame.h"

int UMySaveGame::slotCounter = 0;
int UMySaveGame::slotToInstantiate = 0;

UMySaveGame::UMySaveGame()
{
	PlayerLocation = FVector(0.f,0.f,0.f);
}