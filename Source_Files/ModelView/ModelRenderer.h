#ifndef MODEL_RENDERER
#define MODEL_RENDERER
/*
	Renders 3D-model objects;
	it can render either with or without a Z-buffer;
	without a Z-buffer, it depth-sorts polygons

	Created by Loren Petrich, July 18, 2001
*/

#include "Model3D.h"

struct ModelRenderShader
{
	unsigned int Flags;
	void (* TextureCallback)(void *);
	void *TextureCallbackData;
	
	ModelRenderShader() {obj_clear(*this);}
};

class ModelRenderer
{
	// Kept here to avoid unnecessary re-allocation
	vector<GLfloat> CentroidDepths;
	vector<unsigned short> Indices;
	vector<GLushort> SortedVertIndices;
	vector<GLfloat> ExtLightColors;
	
	void SetupRenderPass(Model3D& Model, ModelRenderShader& Shader);
	
public:
	
	// Needed for depth-sorting the model triangles by centroid
	GLfloat ViewDirection[3];
	
	// Needed for external colors;
	// the first index is the color channel,
	// while the second index is in two parts,
	// the first three (0-2) multipled by the normal vector in dot-product fasion
	// and the fourth (3) added
	
	GLfloat ExternalLight[3][4];
	
	// Render flags:
	enum {
		Textured	= 0x0001,
		Colored		= 0x0002,
		ExtLight	= 0x0004,
	};
	
	// Does the actual rendering; args:
	// A 3D model (of course!)
	// Whether or not to assume a Z-buffer is present
	// Array of shaders to be used for multipass rendering
	// How many shaders in that array to use
	void Render(Model3D& Model, bool Use_Z_Buffer, ModelRenderShader *Shaders, int NumShaders);
	
	// In case one wants to start over again with these persistent arrays
	void Clear();
};


#endif
