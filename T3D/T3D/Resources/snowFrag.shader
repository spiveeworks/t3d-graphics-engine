varying in vec4 P;
varying in vec3 N;
varying in float height;

vec4 snowMaterialDiffuse() {
	float blendG;
	float blendS;
	// branchless blending, why not?
	blendG = 1 - (height + abs(height)) / 2;
	blendS = 1 - (blendG + abs(blendG)) / 2;
	blendG = 1 - blendS;
	
	return gl_FrontMaterial.diffuse * blendG + vec4(1, 1, 1, 1) * blendS;
}

vec4 phongIllumination(vec4 P, vec3 N) {
	// Ambient calculation
	vec4 ambient = gl_FrontMaterial.ambient * gl_LightModel.ambient;

	// Emission calculation
	vec4 emission = gl_FrontMaterial.emission;

	vec3 L = normalize(gl_LightSource[0].position.xyz - vec3(P * gl_LightSource[0].position.w));
	float diffuseIntensity = max(dot(N, L), 0);
	vec4 diffuse = snowMaterialDiffuse() * gl_LightSource[0].diffuse * diffuseIntensity;

	// Specular calculation
	vec3 R = normalize(reflect(L, N));
	vec3 V = normalize(P.xyz);
	float specularIntensity = pow(max(dot(R, V), 0), 0.2*gl_FrontMaterial.shininess);
	vec4 specular = gl_FrontMaterial.specular * gl_LightSource[0].specular * specularIntensity;

	return clamp(ambient + emission + diffuse + specular, 0, 1);
}

void main()
{
    // Do Pixel shading
    gl_FragColor = phongIllumination(P, N);
}