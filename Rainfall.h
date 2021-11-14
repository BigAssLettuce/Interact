#pragma once



#ifndef RAINFALL
#define RAINFALL



#include "Core/Core.h"


#ifdef MODULE_MESH3D
#include "Modules/Mesh/Mesh.h"
#endif // MODULE_MESH

#ifdef MODULE_LIGHT
#include "Modules/Light/LightManager.h"
#endif
#ifdef MODULE_CAMERA3D
#include "Modules/Camera/Camera.h"
#endif

#ifdef MODULE_ECS
#include "Modules/ECS/ECS.h"
#endif

#ifdef MODULE_TRANSFORM3D
#include "Modules/Transform/3D/Transform3D.h"
#endif

#ifdef MODULE_RENDER3D
#include "Modules/Render/3D/Render3D.h"
#endif


using namespace glm;
#endif