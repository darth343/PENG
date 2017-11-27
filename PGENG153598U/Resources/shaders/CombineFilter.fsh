varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
//uniform defined for our use
uniform sampler2D blurpass;
uniform sampler2D original;

void main()
{
	//Get the pixel value at the current location from the built-in Cocos2d uniform "CC_Texture0"

	vec4 originalColor = texture2D(original, v_texCoord);
	vec4 blurpassColor = texture2D(blurpass, v_texCoord);
			
	gl_FragColor = blurpassColor * 0.5f + originalColor;
}