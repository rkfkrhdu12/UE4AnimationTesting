// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AnimTestProject : ModuleRules
{
    public AnimTestProject(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay",
            "AIModule",
            "NavigationSystem",
            "GameplayTasks"
        });
    }
}
