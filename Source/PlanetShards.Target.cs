// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlanetShardsTarget : TargetRules
{
	public PlanetShardsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] {"PlanetShards"});
	}
}