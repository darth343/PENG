varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
//uniform defined for our use
uniform int steps;
uniform sampler2D image;

void main()
{
	//Get the pixel value at the current location from the built-in Cocos2d uniform "CC_Texture0"

	vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
	float temp = 0;
	for(int i = -steps; i <= steps; i++)
	{
	
		color += texture2D(image, vec2(v_texCoord.x, v_texCoord.y) + vec2(0.00093632958 * steps * temp, 0));
		temp += 1.5f;
	}
	
	float division = steps + steps;
	
	division = 1.0f / division;
	
	color.rgb = vec3(color.r * division, color.g * division, color.b * division);
		
	gl_FragColor = color;
}