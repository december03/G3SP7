#include "stdafx.h"
#include "SceneReader.h"

CSceneReader::CSceneReader() : myCurrentBinPath("NA")
{
}

CSceneReader::~CSceneReader()
{
	myStreamPtr = nullptr;
	for (auto& data : myLoadScreenData)
	{
		delete data;
		data = nullptr;
	}
	myLoadScreenData.clear();

	for (auto& data : myInGameData)
	{
		delete data;
		data = nullptr;
	}
	myInGameData.clear();
}

std::vector<SImportedModelData> CSceneReader::LoadUnityScene(const std::string& /*aBinFilePath*/)
{
	//std::ifstream stream;
	//stream.open(aBinFilePath);
	////assert(stream.is_open() && "Bin File %s Failed to open", aBinFilePath);

	//std::string binaryData((std::istreambuf_iterator<char>(myStream)), std::istreambuf_iterator<char>());
	//char* streamPtr = &binaryData[0];

	//Read Header
	/*int header = 0;
	header = Read(header, streamPtr);*/

	return std::vector<SImportedModelData>();
}

bool CSceneReader::OpenBin(const std::string& aBinFilePath)
{
	myCurrentBinPath = aBinFilePath;
	myStream.open(aBinFilePath, std::ios::binary);
	if (!myStream.is_open())
	{
		return false;
	}
    return true;
}

SInGameData& CSceneReader::ReadInGameData()
{
	for (unsigned int i = 0; i < myInGameData.size(); ++i)
	{
		if (myInGameData[i]->myBinPath == myCurrentBinPath)
		{
			myStream.close();
			myStreamPtr = nullptr;
			myCurrentBinPath = "NA";
			std::cout << "Reloading" << std::endl;
			return *myInGameData[i];
		}
	}

	std::string binaryData((std::istreambuf_iterator<char>(myStream)), std::istreambuf_iterator<char>());
	myStreamPtr = &binaryData[0];

	myInGameData.emplace_back(new SInGameData());
	myInGameData.back()->myBinPath = myCurrentBinPath;

	SCameraData cameraData = {};
	myStreamPtr += Read(cameraData);
	myInGameData.back()->myCamera = cameraData;

	SDirectionalLightData directionalLightData = {};
	myStreamPtr += Read(directionalLightData);
	myInGameData.back()->myDirectionalLight = directionalLightData;

	int pointLightDataCount = 0;
	myStreamPtr += Read(pointLightDataCount);
	assert(pointLightDataCount < 1000 && "Something went wrong when reading PointLightData");
	myInGameData.back()->myPointLightData.reserve(pointLightDataCount);
	for (int i = 0; i < pointLightDataCount; ++i)
	{
		SPointLightData pointLightData = {};
		myStreamPtr += Read(pointLightData);
		myInGameData.back()->myPointLightData.emplace_back(pointLightData);
	}

	int myGameObjectDataCount = 0;
	myStreamPtr += Read(myGameObjectDataCount);
	assert(myGameObjectDataCount < 100000 && "Something went wrong when reading GameObjectData");
	myInGameData.back()->myGameObjects.reserve(myGameObjectDataCount);
	for (int i = 0; i < myGameObjectDataCount; ++i)
	{
		SGameObjectData gameObjectData = { 0 };
		myStreamPtr += Read(gameObjectData);
		myInGameData.back()->myGameObjects.emplace_back(gameObjectData);
	}


	myStream.close();
	myStreamPtr = nullptr;
	myCurrentBinPath = "NA";

	return *myInGameData.back();
}

SLoadScreenData& CSceneReader::ReadLoadScreenData()
{
	for (unsigned int i = 0; i < myLoadScreenData.size(); ++i)
	{
		if (myLoadScreenData[i]->myBinPath == myCurrentBinPath)
		{
			myStream.close();
			myStreamPtr = nullptr;
			myCurrentBinPath = "NA";
			std::cout << "Reloading" << std::endl;
			return *myLoadScreenData[i];
		}
	}

	std::string binaryData((std::istreambuf_iterator<char>(myStream)), std::istreambuf_iterator<char>());
	myStreamPtr = &binaryData[0];

	myLoadScreenData.emplace_back(new SLoadScreenData());
	myLoadScreenData.back()->myBinPath = myCurrentBinPath;

	SCameraData cameraData = {};
	myStreamPtr += Read(cameraData);
	myLoadScreenData.back()->myCamera = cameraData;

	SDirectionalLightData directionalLightData = {};
	myStreamPtr += Read(directionalLightData);
	myLoadScreenData.back()->myDirectionalLight = directionalLightData;

	unsigned int pointLightcount = 0;
	myStreamPtr += Read(pointLightcount);

	int myGameObjectDataCount = 0;
	myStreamPtr += Read(myGameObjectDataCount);

	assert(myGameObjectDataCount < 100000 && "Something went wrong when reading GameObjectData");

	myLoadScreenData.back()->myGameObjects.reserve(myGameObjectDataCount);
	for (int i = 0; i < myGameObjectDataCount; ++i)
	{
		SGameObjectData gameObjectData = { 0 };
		myStreamPtr += Read(gameObjectData);
		myLoadScreenData.back()->myGameObjects.emplace_back(gameObjectData);
	}

	myStream.close();
	myStreamPtr = nullptr;
	myCurrentBinPath = "NA";

	return *myLoadScreenData.back();
}
