// ShootTheMap

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootTheMapEditorTarget : TargetRules
{
	public ShootTheMapEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootTheMap" } );
	}
}
