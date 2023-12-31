#include "Renderer.h"

float Renderer::current_time;
float Renderer::last_time;
bool Renderer::Buildable = false;
bool Renderer::Changed = false;
Camera*        Renderer::m_Camera;
Skybox*        Renderer::m_Skybox;
Ground*        Renderer::m_Ground;
Shape_Meteor*  Renderer::m_Meteor;
Water_SHAPE*   Renderer::m_Water;
Shape_Car*	   Renderer::m_Car;
Shape_FireTruck* Renderer::m_FireTruck;
std::vector<glm::mat4> Renderer::GroundTransforms;
std::vector<GLfloat> Renderer::GroundTexturesID;
ProgramObject* Renderer::m_InstanceProgram;
ProgramObject* Renderer::m_NormalProgram;
ProgramObject* Renderer::m_RayProgram;
ProgramObject* Renderer::m_SkyboxProgram;
FrameBuffer*   Renderer::m_FrameBuffer;
Texture2D*     Renderer::m_GameTexture;
TextureMap*    Renderer::m_SkyboxTexture;
std::unordered_map<RenderShapeType, std::pair<Shape*, std::vector<glm::mat4>>> Renderer::m_ShapeData;

/**
 * Initializes the renderer with the given camera.
 *
 * @param camera A pointer to the camera object.
 *
 * @returns None
 */
void Renderer::Init(Camera* camera)
{
	//[OPENGL]------------------------------------------------------------------------------------//
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2.0f);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	
	//[PROGRAM_OBJECTS]---------------------------------------------------------------------------//
	m_InstanceProgram = new ProgramObject();
	m_InstanceProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/Instance.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/Instance.frag")
		},
		{
			ShaderObjectLayout(0, "vert_position"),
			ShaderObjectLayout(1, "vert_normal"),
			ShaderObjectLayout(2, "vert_texture"),
			ShaderObjectLayout(3, "vert_textureID"),
			ShaderObjectLayout(4, "vert_id"),
			ShaderObjectLayout(5, "vert_transforms")
		}
		);

	m_NormalProgram = new ProgramObject();
	m_NormalProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/Base.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/Base.frag")
		},
		{
			ShaderObjectLayout(0, "vert_position"),
			ShaderObjectLayout(1, "vert_normal"),
			ShaderObjectLayout(2, "vert_texture"),
			ShaderObjectLayout(3, "vert_matrix")
		}
		);

	m_RayProgram = new ProgramObject();
	m_RayProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/Ray.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/Ray.frag")
		},
		{
		}
		);

	m_SkyboxProgram = new ProgramObject();
	m_SkyboxProgram->Initialize
	(
		{
			ShaderObject(GL_VERTEX_SHADER, "Engine/Shaders/SkyBox.vert"),
			ShaderObject(GL_FRAGMENT_SHADER, "Engine/Shaders/SkyBox.frag")
		},
		{
			ShaderObjectLayout(0, "vert_position")
		}
	);

	//[TEXTURES]---------------------------------------------------------------------------//

	m_GameTexture = new Texture2D();
	m_GameTexture->LoadTexture("Engine/Renderer/Assets/Textures.png");

	m_SkyboxTexture = new TextureMap();
	m_SkyboxTexture->LoadTexture
	(
		{
		"Engine/Renderer/Assets/right.jpg",
		"Engine/Renderer/Assets/left.jpg",
		"Engine/Renderer/Assets/top.jpg",
		"Engine/Renderer/Assets/bottom.jpg",
		"Engine/Renderer/Assets/front.jpg",
		"Engine/Renderer/Assets/back.jpg"
		}
	);

	//[VIEWPORT]---------------------------------------------------------------------------//

	m_Camera = camera;
	m_FrameBuffer = new FrameBuffer((int)m_Camera->Get_Width(), (int)m_Camera->Get_Height());

	//[SHAPES]---------------------------------------------------------------------------//

	m_Skybox = new Skybox();
	m_Ground = new Ground();
	m_Meteor = new Shape_Meteor();
	m_Water = new Water_SHAPE();
	m_Car = new Shape_Car();
	m_FireTruck = new Shape_FireTruck();

	m_ShapeData[RENDER_RESIDENTIAL_LVL1] = std::make_pair(new ResidenceBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_RESIDENTIAL_LVL2] = std::make_pair(new ResidenceBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_RESIDENTIAL_LVL3] = std::make_pair(new ResidenceBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL1]  = std::make_pair(new IndustryBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL2]  = std::make_pair(new IndustryBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_INDUSTRIAL_LVL3]  = std::make_pair(new IndustryBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_SERVICE_LVL1]     = std::make_pair(new ServiceBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_SERVICE_LVL2]     = std::make_pair(new ServiceBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_SERVICE_LVL3]     = std::make_pair(new ServiceBuilding3(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_FOREST]           = std::make_pair(new Tree(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_POLICESTATION]    = std::make_pair(new PoliceBuilding(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_FIRESTATION]      = std::make_pair(new FireBuilding(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_HIGHSCHOOL]       = std::make_pair(new SchoolBuilding1(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_UNIVERSITY]       = std::make_pair(new SchoolBuilding2(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_STADIUM]          = std::make_pair(new StadionBuilding(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_WINDTURBINE]      = std::make_pair(new WindTurbine(), std::vector<glm::mat4>());
	m_ShapeData[RENDER_WINDTURBINE_PROPELLER] = std::make_pair(new WindTurbinePropeller(), std::vector<glm::mat4>());

	InitShapeBuffers();

	last_time = (float)glfwGetTime();
}

/**
 * Destroys all resources used by the Renderer object.
 *
 * @param None
 *
 * @returns None
 */
void Renderer::Destroy()
{
	delete  m_InstanceProgram;
	delete  m_NormalProgram;
	delete  m_RayProgram;
	delete  m_SkyboxProgram;
	delete  m_GameTexture;
	delete  m_SkyboxTexture;
	delete  m_FrameBuffer;
}

/**
 * Prepares the renderer for rendering the scene.
 *
 * @param None
 *
 * @returns None
 */
void Renderer::PreRender()
{
	m_FrameBuffer->Bind();
	m_Camera->Set_ProjMatrix(m_FrameBuffer->Get_FrameWidth(), m_FrameBuffer->Get_FrameHeight());

	ClearScene();

	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_UseTexture", 1);
	m_InstanceProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_InstanceProgram->SetUniform("u_eye", m_Camera->Get_CameraEye());
	m_InstanceProgram->SetUniformTexture("u_SpriteTexture", 0, m_GameTexture);
	m_InstanceProgram->UnBind();

	m_NormalProgram->Bind();
	m_NormalProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_NormalProgram->SetUniformTexture("u_SpriteTexture", 0, m_GameTexture);
	m_NormalProgram->UnBind();

	current_time = (float)glfwGetTime();
}

/**
 * Performs post-rendering operations such as unbinding the frame buffer, clearing shape transforms, and updating the state of the renderer.
 *
 * @returns None
 */
void Renderer::PostRender()
{
	m_FrameBuffer->UnBind();
	ClearShapeTransforms();
	Changed = false;
	last_time = current_time;
}

/**
 * Renders the scene based on the specified render mode.
 *
 * @param mode The render mode to use.
 *
 * @returns None
 */
void Renderer::SceneRender(RenderMode mode)
{
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		if (mode == INSTANCED) RenderInstanced((*it).second.first, (*it).second.second);
		if (mode == INSTANCED_WIREFRAME) RenderInstanced_Wireframe((*it).second.first, (*it).second.second);
	}

	Render_Meteors();
	Render_Cars();
	RenderInstancedGround();
	Render_Skybox();
}

/**
 * Renders an instance of a shape with the given transforms.
 *
 * @param shape A pointer to the shape to be rendered.
 * @param transforms A vector of transformation matrices to be applied to the shape.
 *
 * @returns None
 */
void Renderer::RenderInstanced(Shape* shape, const std::vector<glm::mat4>& transforms)
{
	if (transforms.size() == 0 && shape->Get_InstanceCount() == 0) return;

	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_UseVertexTexID", (float)(shape == m_Ground));

	glm::mat4 rotation = (shape == m_ShapeData[RENDER_WINDTURBINE_PROPELLER].first ? glm::rotate<float>(static_cast<float>(M_PI * glfwGetTime()), glm::vec3(0, 0, 1)) : glm::mat4(1));
	m_InstanceProgram->SetUniform("u_M", rotation);

	shape->Bind();
	if (Changed)
	{
		shape->AttachMatricesSubData(transforms);
	}
	shape->RenderInstanced();
	shape->UnBind();

	m_InstanceProgram->UnBind();
}

/**
 * Renders an instanced wireframe of a given shape with the provided transforms.
 *
 * @param shape A pointer to the shape to be rendered.
 * @param transforms A vector of transformation matrices to be applied to each instance of the shape.
 *
 * @returns None
 */
void Renderer::RenderInstanced_Wireframe(Shape* shape, const std::vector<glm::mat4>& transforms)
{

	glDisable(GL_CULL_FACE);
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	RenderInstanced(shape, transforms);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glEnable(GL_CULL_FACE);
}


/**
 * Clears the scene by clearing the color and depth buffers and setting the background color to a dark gray.
 *
 * @returns None
 */
void Renderer::ClearScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
}


/**
 * Clears all shape transforms and ground transforms and textures.
 *
 * @param None
 *
 * @returns None
 */
void Renderer::ClearShapeTransforms()
{
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		it->second.second.clear();
	}

	GroundTransforms.clear();
	GroundTexturesID.clear();
}

/**
 * Adds shape transforms to the renderer for a given shape type.
 *
 * @param type The type of shape to add transforms for.
 * @param x The x-coordinate of the shape.
 * @param y The y-coordinate of the shape.
 * @param direction The direction of the shape.
 * @param amount The number of transforms to add.
 *
 * @returns None
 */
void Renderer::AddShapeTransforms(RenderShapeType type, int x, int y, int direction, int amount)
{
	if (m_ShapeData.find(type) == m_ShapeData.end()) return;

	Transform transform_MAJOR;
	transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 1));
	transform_MAJOR.rotate = glm::rotate<float>(static_cast<float>(M_PI / 2 * direction), glm::vec3(0, 1, 0));
	transform_MAJOR.scale = glm::mat4(1); //TODO: 2x2 field

	if (type == RENDER_STADIUM || type == RENDER_UNIVERSITY)
	{
		transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 2, 0, 2 * x + 2));
		transform_MAJOR.scale = glm::scale(glm::vec3(2.5,1.5,2.5));
	}

	if (type == RENDER_HIGHSCHOOL)
	{
		if (direction == 0 || direction == 2)
		{
			transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 2, 0, 2 * x + 1));
		}
		if (direction == 1 || direction == 3)
		{
			transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 2));
		}
		transform_MAJOR.scale = glm::scale(glm::vec3(2.5, 1, 1));
	}

	for (int i = 0; i < m_ShapeData[type].first->Get_Transforms().size() && i < amount; i++)
	{
		Transform transform_MINOR;
		transform_MINOR.translate = m_ShapeData[type].first->Get_Transforms()[i].translate;
		transform_MINOR.rotate = m_ShapeData[type].first->Get_Transforms()[i].rotate; //TODO: Dynamic
		transform_MINOR.scale = m_ShapeData[type].first->Get_Transforms()[i].scale;

		m_ShapeData[type].second.push_back(Transform::ConvertToMatrix(transform_MAJOR) * Transform::ConvertToMatrix(transform_MINOR));
		
		if (type == RENDER_WINDTURBINE)
		{
			Transform transform_MINOR_2;
			transform_MINOR_2.translate = m_ShapeData[RENDER_WINDTURBINE_PROPELLER].first->Get_Transforms()[i].translate;
			transform_MINOR_2.rotate = m_ShapeData[RENDER_WINDTURBINE_PROPELLER].first->Get_Transforms()[i].rotate; //TODO: Dynamic
			transform_MINOR_2.scale = m_ShapeData[RENDER_WINDTURBINE_PROPELLER].first->Get_Transforms()[i].scale;

			m_ShapeData[RENDER_WINDTURBINE_PROPELLER].second.push_back(Transform::ConvertToMatrix(transform_MAJOR) * Transform::ConvertToMatrix(transform_MINOR_2));
		}
	}
}

/**
 * Sets the light properties for the renderer.
 *
 * @param LightProperties The light properties to be set.
 *
 * @returns None
 */
void Renderer::Set_LightProperties(const LightProperties& LightProperties)
{
	m_InstanceProgram->Bind();
	m_InstanceProgram->SetUniform("u_LightDir", LightProperties.lightDir);
	m_InstanceProgram->SetUniform("u_Specular_Pow", LightProperties.specularPow);
	m_InstanceProgram->SetUniform("u_La", LightProperties.La);
	m_InstanceProgram->SetUniform("u_Ld", LightProperties.Ld);
	m_InstanceProgram->SetUniform("u_Ls", LightProperties.Ls);
	m_InstanceProgram->SetUniform("u_Ka", LightProperties.Ka);
	m_InstanceProgram->SetUniform("u_Kd", LightProperties.Kd);
	m_InstanceProgram->SetUniform("u_Ks", LightProperties.Ks);
	m_InstanceProgram->UnBind();
}

/**
 * Renders the skybox using the current camera and skybox texture.
 *
 * @param None
 *
 * @returns None
 */
void Renderer::Render_Skybox()
{
	m_SkyboxProgram->Bind();
	m_SkyboxProgram->SetUniform("u_UseTexture", 1);
	m_SkyboxProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());
	m_SkyboxProgram->SetUniform("u_M", glm::translate(m_Camera->Get_CameraEye()));
	m_SkyboxProgram->SetUniformTexture("u_textureMap", 0, m_SkyboxTexture);

	m_Skybox->Render();

	m_SkyboxProgram->UnBind();
}

/**
 * Adds ground transforms to the renderer for a given render shape type, position, direction, and texture.
 *
 * @param type The type of render shape.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @param direction The direction of the render shape.
 * @param texture The texture of the render shape.
 *
 * @returns None
 */
void Renderer::AddGroundTransforms(RenderShapeType type, int x, int y, int direction, int texture)
{
	Transform transform_MAJOR;
	transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 1));
	transform_MAJOR.rotate = glm::rotate<float>(static_cast<float>(M_PI / 2 * (texture / 100)), glm::vec3(0,1,0));
	transform_MAJOR.scale = glm::mat4(1); //TODO SCALE

	if (type == RENDER_STADIUM || type == RENDER_UNIVERSITY)
	{
		transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 2, 0, 2 * x + 2));
		transform_MAJOR.scale = glm::scale(glm::vec3(2, 1, 2));
	}

	if (type == RENDER_HIGHSCHOOL)
	{
		transform_MAJOR.rotate = glm::rotate<float>(static_cast<float>(M_PI / 2 * direction), glm::vec3(0, 1, 0));
		if (direction == 0 || direction == 2)
		{
			transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 2, 0, 2 * x + 1));
		}
		if (direction == 1 || direction == 3)
		{
			transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 2));
		}
		transform_MAJOR.scale = glm::scale(glm::vec3(2, 1, 1));
	}

	for (int i = 0; i < m_Ground->Get_Transforms().size(); i++)
	{
		Transform transform_MINOR;
		transform_MINOR.translate = m_Ground->Get_Transforms()[i].translate;
		transform_MINOR.rotate = m_Ground->Get_Transforms()[i].rotate; //TODO: Dynamic
		transform_MINOR.scale = m_Ground->Get_Transforms()[i].scale;

		//TODO -> ONLY ONCE
		GroundTransforms.push_back(Transform::ConvertToMatrix(transform_MAJOR) * Transform::ConvertToMatrix(transform_MINOR));
	}

	GroundTexturesID.push_back((GLfloat)(texture % 100));
}

/**
 * Renders an instanced ground object.
 *
 * @param None
 *
 * @returns None
 */
void Renderer::RenderInstancedGround()
{
	if (Changed)
	{
		m_Ground->Bind();
		m_Ground->AttachNumbersSubData(GroundTexturesID);
		m_Ground->UnBind();
	}

	RenderInstanced(m_Ground, GroundTransforms);
}

/**
 * Determines the ID of the ground texture for a given render shape type and containment status.
 *
 * @param type The type of render shape.
 * @param contain The containment status of the render shape.
 *
 * @returns The ID of the ground texture for the given render shape type and containment status.
 *          Returns -1 if the render shape type is not recognized.
 */
int Renderer::DetermineGroundTextureID(RenderShapeType type, int contain)
{
	switch (type)
	{
	case RENDER_RESIDENTIAL_LVL1: return (contain == 0 ? 17 : 7);
	case RENDER_RESIDENTIAL_LVL2: return (contain == 0 ? 17 : 7);
	case RENDER_RESIDENTIAL_LVL3: return (contain == 0 ? 17 : 7);
	case RENDER_INDUSTRIAL_LVL1: return (contain == 0 ? 19 : 9);
	case RENDER_INDUSTRIAL_LVL2: return (contain == 0 ? 19 : 9);
	case RENDER_INDUSTRIAL_LVL3: return (contain == 0 ? 19 : 9);
	case RENDER_SERVICE_LVL1: return (contain == 0 ? 18 : 8);
	case RENDER_SERVICE_LVL2: return (contain == 0 ? 18 : 8);
	case RENDER_SERVICE_LVL3: return (contain == 0 ? 18 : 8);
	case RENDER_FOREST: return 1;
	case RENDER_POLICESTATION: return 11;
	case RENDER_FIRESTATION: return 11;
	case RENDER_HIGHSCHOOL: return 10;
	case RENDER_UNIVERSITY: return 10;
	case RENDER_STADIUM: return 12;
	case RENDER_WINDTURBINE: return 2;
	case RENDER_EMPTY: return 0;
	case RENDER_CRATER: return 62;
	case RENDER_LAKE: return 38;
	}
	return -1;
}

/**
 * Renders the meteor objects using instancing.
 *
 * @returns None
 */
void Renderer::Render_Meteors()
{
	bool not_changed = !Changed;
	Changed = true;

	RenderInstanced(m_Meteor, MeteorGrp::Get_Transforms());

	if (not_changed) Changed = false;
}

/**
 * Renders the cars in the scene using instanced rendering.
 *
 * @returns None
 */
void Renderer::Render_Cars()
{
	bool not_changed = !Changed;
	Changed = true;

	RenderInstanced(m_Car, CarGroup::Get_Transforms());
	RenderInstanced(m_FireTruck, CarGroup::Get_FireTruckTransforms());

	if (not_changed) Changed = false;
}

/**
 * Renders a shape with normal mapping.
 *
 * @param type The type of shape to render.
 * @param x The x-coordinate of the shape.
 * @param y The y-coordinate of the shape.
 * @param direction The direction of the shape.
 *
 * @returns None
 */
void Renderer::RenderNormal(RenderShapeType type, int x, int y, int direction)
{
	if (m_ShapeData.find(type) == m_ShapeData.end()) return;

	Shape* shape = m_ShapeData[type].first;

	m_NormalProgram->Bind();
	m_NormalProgram->SetUniform("u_VP", m_Camera->Get_ViewProjMatrix());

	Transform transform_MAJOR;
	transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 1));
	transform_MAJOR.rotate = glm::rotate<float>(static_cast<float>(M_PI / 2 * direction), glm::vec3(0, 1, 0));
	transform_MAJOR.scale = glm::mat4(1); //TODO SCALE

	if (type == RENDER_UNIVERSITY || type == RENDER_STADIUM)
	{
		transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 2, 0, 2 * x + 2));
		transform_MAJOR.scale = glm::scale(glm::vec3(2.5, 1.5, 2.5));
	}

	if (type == RENDER_HIGHSCHOOL)
	{
		if (direction == 0 || direction == 2)
		{
			transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 2, 0, 2 * x + 1));
		}
		if (direction == 1 || direction == 3)
		{
			transform_MAJOR.translate = glm::translate(glm::vec3(2 * y + 1, 0, 2 * x + 2));
		}
		transform_MAJOR.scale = glm::scale(glm::vec3(2.5, 1, 1));
	}

	for (int i = 0; i < shape->Get_Transforms().size(); i++)
	{
		Transform transform_MINOR;
		transform_MINOR.translate = shape->Get_Transforms()[i].translate;
		transform_MINOR.rotate = shape->Get_Transforms()[i].rotate;
		transform_MINOR.scale = shape->Get_Transforms()[i].scale;

		glm::mat4 rotation = (shape == m_ShapeData[RENDER_WINDTURBINE_PROPELLER].first ? glm::rotate<float>(static_cast<float>(M_PI * glfwGetTime()), glm::vec3(0, 0, 1)) : glm::mat4(1));
		m_NormalProgram->SetUniform("u_M", Transform::ConvertToMatrix(transform_MAJOR) * Transform::ConvertToMatrix(transform_MINOR) * rotation);
		m_NormalProgram->SetUniform("u_color", Buildable ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0));

		shape->Bind();
		shape->Render();
		shape->UnBind();
	}

	m_NormalProgram->UnBind();
}

/**
 * Renders a wireframe representation of a shape with normal vectors.
 *
 * @param type The type of shape to render.
 * @param x The x-coordinate of the shape's position.
 * @param y The y-coordinate of the shape's position.
 * @param direction The direction in which to render the shape.
 *
 * @returns None
 */
void Renderer::RenderNormal_Wireframe(RenderShapeType type, int x, int y, int direction)
{
	glDisable(GL_CULL_FACE);
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	RenderNormal(type, x, y, direction);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glEnable(GL_CULL_FACE);
}

/**
 * Initializes the shape buffers for rendering.
 *
 * @param None
 *
 * @returns None
 */
void Renderer::InitShapeBuffers()
{
	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		it->second.first->CreateBuffers(1);
	}

	m_Skybox->CreateBuffers();
	m_Ground->CreateBuffers(1);
	m_Meteor->CreateBuffers(2500);
	m_Water->CreateBuffers(2500);
	m_Car->CreateBuffers(2500);
	m_FireTruck->CreateBuffers(2500);
}

/**
 * Resizes the shape buffers to the specified size.
 *
 * @param buffer_size The new size of the shape buffers.
 *
 * @returns None
 */
void Renderer::ResizeShapeBuffers(int buffer_size)
{
	std::cout << "RESIZED SHAPE BUFFER: " << buffer_size << std::endl;

	for (auto it = m_ShapeData.begin(); it != m_ShapeData.end(); it++)
	{
		it->second.first->AttachMatricesDynamic(std::vector<glm::mat4>(buffer_size * it->second.first->Get_Transforms().size()));
	}

	m_Ground->AttachMatricesDynamic(std::vector<glm::mat4>(buffer_size));
	m_Ground->AttachNumbersDynamic(std::vector<GLfloat>(buffer_size));
}

/**
 * Renders a water curve using the provided transforms.
 *
 * @param transforms A vector of transformation matrices to apply to the water curve.
 *
 * @returns None
 */
void Renderer::RenderWaterCurve(const std::vector<glm::mat4>& transforms)
{
	bool not_changed = !Changed;
	Changed = true;

	RenderInstanced(m_Water, transforms);

	if (not_changed) Changed = false;
}