// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class ViewPortPriority : uint8
{
	Interaction,
	Default,
	Inventory,
	Main,
	Quest
};

/**
 * 
 */
class PROJECTD_API WidgetData
{

public:
	WidgetData();
	~WidgetData();


};
