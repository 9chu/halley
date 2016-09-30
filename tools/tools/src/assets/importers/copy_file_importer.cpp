#include "copy_file_importer.h"
#include "halley/tools/assets/import_assets_database.h"
#include "halley/file/byte_serializer.h"
#include "halley/resources/metadata.h"

using namespace Halley;

std::vector<Path> CopyFileImporter::import(const ImportingAsset& asset, Path dstDir, ProgressReporter reporter, AssetCollector collector)
{
	std::vector<Path> out;
	
	Path mainFile = asset.inputFiles.at(0).name;
	FileSystem::writeFile(dstDir / mainFile, asset.inputFiles[0].data);
	out.push_back(mainFile);

	if (asset.metadata) {
		Path metaPath = mainFile.replaceExtension(mainFile.getExtension() + ".meta");
		FileSystem::writeFile(dstDir / metaPath, Serializer::toBytes(*asset.metadata));
		out.push_back(metaPath);
	}

	return out;
}
