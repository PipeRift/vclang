// Copyright 2015-2021 Piperift - All rights reserved
#pragma once

#include "DockSpaceLayout.h"
#include "Editors/AssetEditor.h"
#include "Editors/BaseEditor.h"
#include "Editors/Projects/FileExplorerPanel.h"
#include "Tools/ASTDebugger.h"

#include <Assets/AssetPtr.h>
#include <Assets/TypeAsset.h>
#include <Project.h>
#include <UI/UI.h>


namespace Rift
{
	class ProjectEditor : public BaseEditor
	{
		CLASS(ProjectEditor, BaseEditor)

	public:
		static const Name leftNode;
		static const Name centralNode;

		ImGuiID dockspaceID = 0;

		TPtr<Project> currentProject;
		TArray<TOwnPtr<AssetEditor>> assetEditors;
		TArray<TAssetPtr<TypeAsset>> pendingTypesToClose;

		FileExplorerPanel fileExplorer{*this};
		DockSpaceLayout layout;
		Rift::ASTDebugger astDebugger;

	protected:
		bool bSkipFrameAfterMenu = false;


	public:
		ProjectEditor();
		void BeforeDestroy() override;
		void OpenType(TAssetPtr<TypeAsset> asset);
		void CloseType(TAssetPtr<TypeAsset> asset);

		void Draw();

	protected:
		void CreateDockspace();

		void DrawMenuBar();

		void OnProjectChanged(TPtr<Project> newProject);
	};
}    // namespace Rift
