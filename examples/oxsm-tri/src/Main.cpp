#include <nds.h>
#include <filesystem.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/oxnds.h"

oxModel* model;
float rotateX = 0.0;
float rotateY = 0.0;

void drawScene()
{
	oxBeginFrame();

    // Move model away from the camera
	glTranslatef32(0, 0, floattof32(-2));
	// Rotate model
	glRotateX(rotateX);
	glRotateY(rotateY);

    // Draw the model
	oxDrawModelTris(model);

	oxEndFrame();
}

int main()
{
    consoleDemoInit();

	// Init NitroFS.
    if(!nitroFSInit(NULL))
		debug_err("NitroFS Init failed.\n");

    // Init 3D on main (top) screen.
    oxInit3D_Main();

    model = oxCreateStaticModel("tri.oxsm");

	// 1 light in front of the triangle.
    glLight(0, RGB15(25, 25, 25), 0, 0, -0.75);

    bool running = true;
    while (running)
    {
        scanKeys();

		u16 kHeld = keysHeld();
		u16 kDown = keysDown();

        if((kDown & KEY_UP) || (kHeld & KEY_UP)) rotateX += 3;
		if((kDown & KEY_DOWN) || (kHeld & KEY_DOWN)) rotateX -= 3;
		if((kDown & KEY_LEFT) || (kHeld & KEY_LEFT)) rotateY += 3;
		if((kDown & KEY_RIGHT) || (kHeld & KEY_RIGHT)) rotateY -= 3;

		drawScene();

		if(kDown & KEY_START) running = false;
    }
}