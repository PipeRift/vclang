// Copyright 2015-2019 Piperift - All rights reserved

#pragma once

#if WITH_EDITOR

#include "UI/Window.h"


class LogWindow : public Window {
	CLASS(LogWindow, Window)

	ImGuiTextBuffer textBuffer;
	ImGuiTextFilter filter;
	TArray<i32> lineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
	bool bAutoScroll = true;
	bool bScrollToBottom = false;

public:

	static Ptr<LogWindow> globalLogWindow;


	LogWindow() : Super(), filter{} {}

	void Log(const String& str);
	void Log(const char* str, size_t len);

protected:

	virtual void Build() override;

	virtual void Tick(float deltaTime) override;

	void Clear()
	{
		textBuffer.clear();
		lineOffsets.Empty();
		lineOffsets.Add(0);
	}
};

#endif
