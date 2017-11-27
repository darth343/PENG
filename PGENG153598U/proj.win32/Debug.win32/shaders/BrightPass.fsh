varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
//uniform defined for our use
uniform float brightcheckvalue;

void main()
{	
	//Get the pixel value at the current location from the built-in Cocos2d uniform "CC_Texture0"
	vec4 color = texture2D(CC_Texture0, v_texCoord);
	
	float lumaValue = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
	float lumaClamped = max(lumaValue - brightcheckvalue, 0.0f);
	
	color.rgb *= lumaClamped / lumaValue;
	
	gl_FragColor = color;
}