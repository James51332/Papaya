#pragma once

// -------------------------------------------
// ----- Core Engine -------------------------
// -------------------------------------------

#include "main/core/EntryPoint.h"
#include "main/core/Game.h"
#include "main/core/Layer.h"
#include "main/core/Log.h"
#include "main/core/Timestep.h"
#include "main/core/Input.h"

// -------------------------------------------
// ----- Rendering ---------------------------
// -------------------------------------------

#include "main/renderer/Buffer.h"
#include "main/renderer/BufferLayout.h"
#include "main/renderer/Shader.h"
#include "main/renderer/Texture.h"
#include "main/renderer/PipelineState.h"
#include "main/renderer/Framebuffer.h"
#include "main/renderer/Renderer.h"
#include "main/renderer/Renderer2D.h"
#include "main/renderer/RenderCommand.h"
#include "main/renderer/ImGuiRenderer.h"

// -------------------------------------------
// ----- Utilities ---------------------------
// -------------------------------------------

#include "main/utils/Memory.h"
#include "main/utils/String.h"

// -------------------------------------------
// ----- Events ------------------------------
// -------------------------------------------

#include "main/events/Event.h"
#include "main/events/KeyEvent.h"
#include "main/events/MouseEvent.h"
#include "main/events/AppEvent.h"

// -------------------------------------------
// ----- ECS ---------------------------------
// -------------------------------------------

#include "main/scene/Entity.h"
#include "main/scene/Components.h"
#include "main/scene/Scene.h"
