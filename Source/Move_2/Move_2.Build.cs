// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Move_2 : ModuleRules
{
	public Move_2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
