#include "VertexBufferObject.h"
#include <iostream>

VertexBufferObject::VertexBufferObject()
{
	// Initialize handles to zero
}

VertexBufferObject::~VertexBufferObject()
{
	// Free up any resources
}

void VertexBufferObject::addAttributeArray(AttributeDescriptor attrib)
{
	// Push the new attrib into the vector of AttributeDescriptors
}

void VertexBufferObject::createVBO(bool interleave /*= true*/)
{
	// Step 1: Tell OpenGL to allocate resources for a new Vertex Array Object (VAO)
	// A VAO encapsulates all of the necessary state changes for rendering
	// call glGenVertexArrays

	// Step 2: Bind the vertex array
	// call glBindVertexArray

	if (!interleave) // not interleaving
	{
		// Step 3: Tell OpenGL to allocate resources new Vertex Buffer Object(s)
		// Note you will need to create more than one VBO (one VBO for each attribute)

		unsigned int numBuffers = attributeDescriptors.size();
		std::vector<unsigned int> _vboHandles(numBuffers);

		// call glGenBuffers with the number of attributes stored in the attributeDescriptors vector
		// You will want to store these VBO in the vboHandles vector

		// for each vbo...
		for (int i = 0; i < vboHandles.size(); i++)
		{
			// Step 4: Call glEnableVertexAttribArray
			// The value you pass into this function will correspond to the layout location
			// specified in the vertex shader. This is how you tell OpenGL what data goes
			// to which layout location.

			// Step 5: Bind the current VBO
			glBindBuffer(GL_ARRAY_BUFFER, vboHandles[i]);

			// Step 6: Send data to the GPU
			// Call glBufferData

			// Step 7: Set up the attribute pointer
			// This is how we tell OpenGL how the data in the VBO is laid out
			// call glVertexAttribPointer

			// Step 8: Unbind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		// Step 9: Unbind the VAO
		// The VAO kept track of the necessary state changes.
		// This means when we want to draw this VBO, we just need to bind the VAO.
		// We never have to bind the VBO again. Binding the VAO will cause OpenGL
		// to set the necessary states for us. Yay!
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
	{
		// Interleaving is for bonus marks, so it is optional
		// Instead of having four separate buffers for the attributes
		// ie. v-v-v-v-v | n-n-n-n-n | uv-uv-uv-uv-uv
		// Make one array the size of all attributes put together and
		// interleave the data
		// ie. v-n-uv | v-n-uv | v-n-uv ...
		// The steps are similar to a creating a non interleaved VBO
		// but you do not have to loop through each buffer. You just send
		// the single interleaved buffer. You will have to call glEnableVertexAttribArray
		// for each attrib.
	}
}

void VertexBufferObject::draw()
{
	// Step 1: Bind the VAO
	// Call: glBindVertexArray

	// Step 2: Draw
	// Call either glDrawArrays or glDrawElements
	// Only one will work. I'll let you figure out which :)
}

void VertexBufferObject::destroy()
{
	// Free up any resources allocated by this buffer
	if (vaoHandle)
	{
		glDeleteVertexArrays(1, &vaoHandle);
		glDeleteBuffers(vboHandles.size(), &vboHandles[0]);
	}

	vboHandles.clear();
	attributeDescriptors.clear();
}


