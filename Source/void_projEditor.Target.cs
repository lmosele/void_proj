// Temp

using UnrealBuildTool;
using System.Collections.Generic;

public class void_projEditorTarget : TargetRules
{
	public void_projEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "void_proj" } );
	}
}
