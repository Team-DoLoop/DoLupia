// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectD : ModuleRules
{
	public ProjectD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "UMG", "HTTP", "Json" ,"GameplayTasks", "OctopusBackpack", "MinimapPlugin", "Niagara", "GeometryCollectionEngine", "Slate", "SlateCore", "LevelSequence", "MovieScene", "GamePlayCameras" });
    }
}
