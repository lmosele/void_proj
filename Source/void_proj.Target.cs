// Temp

using UnrealBuildTool;
using System.Collections.Generic;

public class void_projTarget : TargetRules
{
	public void_projTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "void_proj" } );
	}
}
