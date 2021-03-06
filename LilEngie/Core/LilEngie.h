#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "src/Game/Game.h"

#include "src/Application/Window.h"
#include "src/Application/Debug.h"
#include "src/Application/Time.h"

#include "src/Graphics/Renderer.h"
#include "src/Graphics/BaseMeshes.h"
#include "src/Graphics/MaterialHandler.h"
#include "src/Graphics/ShaderHandler.h"
#include "src/Graphics/LightHandler.h"
#include "src/Graphics/Model.h"
#include "src/Graphics/ModelHandler.h"
#include "src/Graphics/TextureHandler.h"
#include "src/Graphics/Vertex.h"
#include "src/Graphics/Text/Character.h"
#include "src/Graphics/Text/Font.h"
#include "src/Graphics/Text/FontLoader.h"
#include "src/Graphics/Text/TextHandler.h"
#include "src/Graphics/Text/TextRenderer.h"

#include "src/Utilities/ModelLoader.h"

#include "src/Entity/Scene.h"
#include "src/Entity/SceneManager.h"
#include "src/Entity/GameObject.h"
#include "src/Entity/Component.h"
#include "src/Entity/Components/Mesh.h"
#include "src/Entity/Components/Camera.h"
#include "src/Entity/Components/PointLight.h"
#include "src/Entity/Components/DirectionalLight.h"
#include "src/Entity/Components/SpotLight.h"
#include "src/Entity/Components/Text.h"

#include "src/Utilities/ModelLoader.h"

#include "src/Input/Input.h"
#include "src/Input/Keys.h"
