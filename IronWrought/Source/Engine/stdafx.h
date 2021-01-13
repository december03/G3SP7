#pragma once
//Windows API
#include "WinInclude.h"

//C++
#include <comdef.h>
#include <d3d11.h>
#include <codecvt>
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


//DirectXTK
#include <DDSTextureLoader.h>
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;

//Utility
#include "Input.h"
#include "Timer.h"
#include "EngineException.h"
#include "ModelMath.h"
#include "JsonReader.h"
#include "Utility.h"

//Engine
#include "DirectXFramework.h"
#include "WindowHandler.h"
#include "EngineDefines.h"

//Lights
#include "EnvironmentLight.h"
#include "PointLight.h"
#include "LightFactory.h"

//Components
#include "TransformComponent.h"

//Singleton
#include "MainSingleton.h"

//Audio
#include "Audio.h"
#include "AudioChannel.h"
#include "FMod.h"


//When Completed
//#include "Engine.h"
//#include "Scene.h"

//#include "PostMaster.h"

//#include "CTextInstance.h" <-- Changed to Component
//#include "CSpriteInstance.h" <-- Changed to Component
//#include "CVFXInstance.h" <-- Changed to Component
//#include "CParticleComponent.h"

//#include "CollisionManager.h"

//#include "FModWrapper.h"

//#include "PopupTextService.h"
//#include "DialogueSystem.h"


