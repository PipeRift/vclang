// Copyright 2015-2021 Piperift - All rights reserved

#include "Editors/RootEditor.h"

#include <Files/FileDialog.h>
#include <RiftContext.h>
#include <UI/UI.h>


namespace Rift
{
	void RootEditor::Draw()
	{
		if (GetContext<RiftContext>()->HasProject())
		{
			projectEditor->Draw();
		}
		else
		{
			ImGui::OpenPopup("Project Picker");
		}

		DrawMenuBar();
		DrawProjectPickerPopup();

		memoryDebugger.Draw();

#if BUILD_DEBUG
		if (showDemo)
		{
			ImGui::ShowDemoWindow(&showDemo);
		}
#endif
	}

	void RootEditor::DrawMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Views"))
			{
				ImGui::MenuItem("Memory", nullptr, &memoryDebugger.open);
				ImGui::EndMenu();
			}

#if BUILD_DEBUG
			ImGui::MenuItem("Demo", nullptr, &showDemo);
#endif

			ImGui::EndMainMenuBar();
		}
	}

	void RootEditor::DrawProjectPickerPopup()
	{
		// Center modal when appearing
		ImGui::SetNextWindowPos(
		    ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		if (ImGui::BeginPopupModal("Project Picker", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::Button("Open Project..."))
			{
				Path folder = Dialogs::SelectFolder("Select project folder", Paths::GetCurrent());

				if (GetContext<RiftContext>()->OpenProject(folder))
				{
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::SetItemDefaultFocus();
			ImGui::Separator();
			ImGui::Text("Recent Projects");
			static const char* recentProjects[]{"One recent project"};
			static int selected = 0;
			if (ImGui::BeginListBox("##RecentProjects"))
			{
				for (int n = 0; n < IM_ARRAYSIZE(recentProjects); ++n)
				{
					const bool is_selected = (selected == n);
					if (ImGui::Selectable(recentProjects[n], is_selected))
					{
						selected = n;
					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation
					// focus)
					if (is_selected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndListBox();
			}
			ImGui::EndPopup();
		}
	}
}    // namespace Rift
