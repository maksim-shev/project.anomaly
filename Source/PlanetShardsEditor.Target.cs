// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlanetShardsEditorTarget : TargetRules
{
	public PlanetShardsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] {"PlanetShards"});
	}
}