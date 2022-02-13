// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ThirdPersonUdemyProjEditorTarget : TargetRules
{
	public ThirdPersonUdemyProjEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		// DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ThirdPersonUdemyProj");
	}
}
