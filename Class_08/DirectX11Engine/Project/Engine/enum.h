#pragma once


enum class COMPONENT_TYPE
{
	TRANSFORM,
	CAMERA,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	ANIMATOR3D,
	LIGHT2D,
	LIGHT3D,

	MESHRENDER,
	DECAL,
	PARTICLESYSTEM,
	TILEMAP,
	LANDSCAPE,

	END,

	SCRIPT,
};

enum class ASSET_TYPE
{
	PREFAB,
	MESH,
	MESH_DATA,
	MATERIAL,
	TEXTURE,
	SOUND,
	GRAPHICS_SHADER,
	COMPUTE_SHADER,

	END,
};

enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL,
	ANIMATION,
	GLOBAL,
	END,
};

// Rasterizer State
enum class RS_TYPE
{
	CULL_BACK,
	CULL_FRONT,
	CULL_NONE,
	WIRE_FRAME,

	END,
};

// DepthStencil State
enum class DS_TYPE
{
	LESS,
	LESS_EQUAL,

	GREATER,

	NO_TEST,
	NO_TEST_NO_WRITE,

	END,
};

enum class BS_TYPE
{
	DEFAULT,		// Src(1), Dest(0)
	ALPHA_BLEND,	// Src(A), Dest(1-A)
	ONE_ONE,		// Src(1), Dest(1)

	END,
};



// Direction Type
enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT,
};

extern Vec3	XAxis;
extern Vec3	YAxis;
extern Vec3	ZAxis;


enum SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,
};


enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,

	TEX_CUBE_0,
	TEX_CUBE_1,
	TEX_CUBE_2,
	TEX_CUBE_4,

	TEX_ARR_0,
	TEX_ARR_1,
	TEX_ARR_2,
	TEX_ARR_3,

	END,
};


enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,

	CUBE,
	SPHERE,
};


enum class PROJ_TYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};

enum class TASK_TYPE
{
	// Param 0 : Layer Index
	// Param 1 : Object Adress
	SPAWN_OBJECT,

	// Param 0 : Object Adress
	DESTROY_OBJECT,

	//
	CHANGE_LEVEL,
};