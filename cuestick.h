///////////////////////////////////////////////////////////////////////////////
//
// Geometry for the Cue Stick and Two Balls
// Vertex Colored Triangle Lists
//
///////////////////////////////////////////////////////////////////////////////
#define CUEFORMAT		GL_C3F_V3F	// MODEL HAS COLOR AND VERTEX ONLY
#define CUEPOLYCNT	48
float CUEMODEL[] = {
		0.3608f, 0.2549f, 0.0000f, 0.0795f, -0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.1125f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0000f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.1125f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0795f, -0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0563f, -0.0563f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, 0.1125f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0563f, -0.0563f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0796f, 0.0000f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, 0.0796f, 0.0000f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, 0.0563f, -0.0563f, 2.5000f, 
		0.8980f, 0.6824f, 0.4745f, 0.0247f, -0.0247f, 0.0187f, 
		0.9059f, 0.7137f, 0.5255f, 0.0796f, 0.0000f, 2.5000f, 
		0.8980f, 0.6824f, 0.4745f, 0.0247f, -0.0247f, 0.0187f, 
		0.9059f, 0.7137f, 0.5255f, 0.0350f, -0.0000f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0350f, -0.0000f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0247f, -0.0247f, 0.0187f, 
		0.2314f, 0.4471f, 0.4510f, 0.0000f, -0.0000f, -0.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, -0.1125f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0795f, -0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0000f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0795f, -0.0795f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0000f, -0.1125f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0000f, -0.0796f, 2.5000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0795f, -0.0795f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0000f, -0.0796f, 2.5000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0563f, -0.0563f, 2.5000f, 
		0.8980f, 0.6824f, 0.4745f, 0.0563f, -0.0563f, 2.5000f, 
		0.8706f, 0.6039f, 0.3451f, -0.0000f, -0.0796f, 2.5000f, 
		0.8392f, 0.5098f, 0.1882f, 0.0000f, -0.0350f, 0.0187f, 
		0.8980f, 0.6824f, 0.4745f, 0.0563f, -0.0563f, 2.5000f, 
		0.8392f, 0.5098f, 0.1882f, 0.0000f, -0.0350f, 0.0187f, 
		0.8980f, 0.6824f, 0.4745f, 0.0247f, -0.0247f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0247f, -0.0247f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0000f, -0.0350f, 0.0187f, 
		0.2314f, 0.4471f, 0.4510f, 0.0000f, -0.0000f, -0.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0795f, -0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, -0.1125f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0000f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0000f, -0.1125f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0795f, -0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0563f, -0.0563f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0000f, -0.1125f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0563f, -0.0563f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0000f, -0.0796f, 2.5000f, 
		0.8706f, 0.6039f, 0.3451f, -0.0000f, -0.0796f, 2.5000f, 
		0.8980f, 0.6824f, 0.4745f, -0.0563f, -0.0563f, 2.5000f, 
		0.8980f, 0.6824f, 0.4745f, -0.0247f, -0.0247f, 0.0187f, 
		0.8706f, 0.6039f, 0.3451f, -0.0000f, -0.0796f, 2.5000f, 
		0.8980f, 0.6824f, 0.4745f, -0.0247f, -0.0247f, 0.0187f, 
		0.8392f, 0.5098f, 0.1882f, 0.0000f, -0.0350f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0000f, -0.0350f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, -0.0247f, -0.0247f, 0.0187f, 
		0.2314f, 0.4471f, 0.4510f, 0.0000f, -0.0000f, -0.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.1125f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0795f, -0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0000f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0795f, -0.0795f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.1125f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0796f, 0.0000f, 2.5000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0795f, -0.0795f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0796f, 0.0000f, 2.5000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0563f, -0.0563f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, -0.0563f, -0.0563f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, -0.0796f, 0.0000f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, -0.0350f, -0.0000f, 0.0187f, 
		0.9059f, 0.7137f, 0.5255f, -0.0563f, -0.0563f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, -0.0350f, -0.0000f, 0.0187f, 
		0.8980f, 0.6824f, 0.4745f, -0.0247f, -0.0247f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, -0.0247f, -0.0247f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, -0.0350f, -0.0000f, 0.0187f, 
		0.2314f, 0.4471f, 0.4510f, 0.0000f, -0.0000f, -0.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0795f, 0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.1125f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0000f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.1125f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0795f, 0.0795f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0563f, 0.0563f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, -0.1125f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0563f, 0.0563f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0796f, 0.0000f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, -0.0796f, 0.0000f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, -0.0563f, 0.0563f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, -0.0247f, 0.0247f, 0.0187f, 
		0.9059f, 0.7137f, 0.5255f, -0.0796f, 0.0000f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, -0.0247f, 0.0247f, 0.0187f, 
		0.9059f, 0.7137f, 0.5255f, -0.0350f, -0.0000f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, -0.0350f, -0.0000f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, -0.0247f, 0.0247f, 0.0187f, 
		0.2314f, 0.4471f, 0.4510f, 0.0000f, -0.0000f, -0.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, 0.1125f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0795f, 0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0000f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0795f, 0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, 0.1125f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, 0.0796f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0795f, 0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, 0.0796f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, -0.0563f, 0.0563f, 2.5000f, 
		0.9059f, 0.7098f, 0.5216f, -0.0563f, 0.0563f, 2.5000f, 
		0.8706f, 0.6039f, 0.3451f, 0.0000f, 0.0796f, 2.5000f, 
		0.8667f, 0.5961f, 0.3333f, 0.0000f, 0.0350f, 0.0187f, 
		0.9059f, 0.7098f, 0.5216f, -0.0563f, 0.0563f, 2.5000f, 
		0.8667f, 0.5961f, 0.3333f, 0.0000f, 0.0350f, 0.0187f, 
		0.8902f, 0.6706f, 0.4588f, -0.0247f, 0.0247f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, -0.0247f, 0.0247f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0000f, 0.0350f, 0.0187f, 
		0.2314f, 0.4471f, 0.4510f, 0.0000f, -0.0000f, -0.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0795f, 0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, 0.1125f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0000f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, 0.1125f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0795f, 0.0795f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0563f, 0.0563f, 2.5000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, 0.1125f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0563f, 0.0563f, 2.5000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0000f, 0.0796f, 2.5000f, 
		0.8706f, 0.6039f, 0.3451f, 0.0000f, 0.0796f, 2.5000f, 
		0.9059f, 0.7098f, 0.5216f, 0.0563f, 0.0563f, 2.5000f, 
		0.8902f, 0.6706f, 0.4588f, 0.0247f, 0.0247f, 0.0187f, 
		0.8706f, 0.6039f, 0.3451f, 0.0000f, 0.0796f, 2.5000f, 
		0.8902f, 0.6706f, 0.4588f, 0.0247f, 0.0247f, 0.0187f, 
		0.8667f, 0.5961f, 0.3333f, 0.0000f, 0.0350f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0000f, 0.0350f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0247f, 0.0247f, 0.0187f, 
		0.2314f, 0.4471f, 0.4510f, 0.0000f, -0.0000f, -0.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.1125f, 0.0000f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, 0.0795f, 0.0795f, 5.0000f, 
		0.3608f, 0.2549f, 0.0000f, -0.0000f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0795f, 0.0795f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.1125f, 0.0000f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0796f, 0.0000f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0795f, 0.0795f, 5.0000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0796f, 0.0000f, 2.5000f, 
		0.4863f, 0.3451f, 0.0000f, 0.0563f, 0.0563f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, 0.0563f, 0.0563f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, 0.0796f, 0.0000f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, 0.0350f, -0.0000f, 0.0187f, 
		0.9059f, 0.7137f, 0.5255f, 0.0563f, 0.0563f, 2.5000f, 
		0.9059f, 0.7137f, 0.5255f, 0.0350f, -0.0000f, 0.0187f, 
		0.8902f, 0.6706f, 0.4588f, 0.0247f, 0.0247f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0247f, 0.0247f, 0.0187f, 
		0.3373f, 0.6588f, 0.6588f, 0.0350f, -0.0000f, 0.0187f, 
		0.2314f, 0.4471f, 0.4510f, 0.0000f, -0.0000f, -0.0000f, 
};