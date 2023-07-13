//Declare openGL version and core profile functionality
#version 330 core

/*
	Next we declare all the input vertex attributes in the vertex shader with the in keyword.
	Right now we only care about position data so we only need a single vertex attribute.
	GLSL has a vector datatype that contains 1 to 4 floats based on its postfix digit.
	Since each vertex has a 3D coordinate we create a vec3 input variable with the name aPos.
	We also specifically set the location of the input variable via layout (location = 0)
	and you'll later see that why we're going to need that location. 
*/
layout (location = 0) in vec3 aPos;

void main()
{
/*
	To set the output of the vertex shader we have to assign the position data to the predefined
	gl_Position variable which is a vec4 behind the scenes. At the end of the main function,
	whatever we set gl_Position to will be used as the output of the vertex shader. Since our
	input is a vector of size 3 we have to cast this to a vector of size 4. We can do this by
	inserting the vec3 values inside the constructor of vec4 and set its w component to 1.0f
	*/

	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
/*
	This is a simplest-possible vertex shader.
	We only forwarded our input data to the shader's output, without processing it first
*/