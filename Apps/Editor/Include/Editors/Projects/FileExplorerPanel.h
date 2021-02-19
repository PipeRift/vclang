// Copyright 2015-2021 Piperift - All rights reserved
#pragma once

// Forward declarations
class ProjectEditor;

struct File
{
	String name;
	TAssetPtr<TypeAsset> info;
};

struct Folder
{
	String name;
	TArray<Folder> folders;
	TArray<File> files;
};

class FileExplorerPanel
{
	ProjectEditor& editor;
	Folder projectFolder;
	bool bOpen  = true;
	bool bDirty = true;


public:
	FileExplorerPanel(ProjectEditor& editor) : editor(editor) {}

	void BuildLayout();
	void Draw();

	void DrawList();

	void CacheProjectFiles();

	void OrganizeProjectFiles();

	void CreateFolderNode(const Folder& folder);
	void CreateFileNode(const File& file);
};
