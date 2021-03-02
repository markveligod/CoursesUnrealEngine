// ShootTheMap

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootTheMapTarget : TargetRules
{
	public ShootTheMapTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootTheMap" } );
	}
}
