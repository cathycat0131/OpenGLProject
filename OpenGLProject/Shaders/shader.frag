#version 330
           
in vec4 vCol;
in vec2 TexCoord;

out vec4 colour;

struct DirectionalLight {
    vec3 colour;
    float ambientIntensity;
};
        
uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
 
void main()
{
    //Calculate the intensity of the light colour
    vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
    
    //Get the colour from the light
    colour = texture(theTexture, TexCoord) * ambientColour;
}
