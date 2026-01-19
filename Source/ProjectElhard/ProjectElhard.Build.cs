// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectElhard : ModuleRules
{
	public ProjectElhard(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
			"GameplayAbilities", "GameplayTags", "GameplayTasks", "GameplayStateTreeModule",
			"GeometryCollectionEngine"
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"StateTreeModule", "AIModule"
		});
	}
};