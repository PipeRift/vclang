// Copyright 2015-2021 Piperift - All rights reserved

#include "Editor.h"

#include <Profiler.h>
#include <RiftContext.h>
#include <UI/Window.h>


namespace Rift
{
	int Editor::Run()
	{
		InitializeContext<RiftContext>();

		// Setup window
		if (!Rift::UI::Init())
		{
			return 1;
		}

		while (!UI::WantsToClose())
		{
			frameTime.Tick();

			UI::PreFrame();
			Tick();
			Draw();
			UI::Render();

			frameTime.PostTick();
			FrameMark;
		}

		UI::Shutdown();
		ShutdownContext();
		return 0;
	}

	Editor::~Editor()
	{
		UI::Shutdown();
	}

	void Editor::Close()
	{
		Rift::UI::Close();
	}

	void Editor::SetUIConfigFile(Path path)
	{
		if (UI::GetWindow())
		{
			configFileChanged          = true;
			configFile                 = Paths::ToString(path);
			ImGui::GetIO().IniFilename = configFile.c_str();
		}
	}

	void Editor::Tick()
	{
		ZoneScopedN("Tick");
		UpdateConfig();

		rootEditor.Tick();
	}
	void Editor::Draw()
	{
		ZoneScopedN("Draw");

		rootEditor.Draw();
	}

	void Editor::UpdateConfig()
	{
		if (configFileChanged)
		{
			ImGui::GetIO().IniFilename = configFile.c_str();
			if (configFile.empty())
			{
				return;
			}

			if (Files::ExistsAsFile(configFile))
			{
				// FIX: Delay this until new frame (essentially, not while already drawing)
				ImGui::LoadIniSettingsFromDisk(configFile.c_str());
			}
			else
			{
				ImGui::SaveIniSettingsToDisk(configFile.c_str());
			}
			configFileChanged = false;
		}
	}
}    // namespace Rift
