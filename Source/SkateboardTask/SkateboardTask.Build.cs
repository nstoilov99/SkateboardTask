// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SkateboardTask : ModuleRules
{
	public SkateboardTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "UMG", "Engine", "InputCore", "EnhancedInput" });
	}
}
