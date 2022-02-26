//------------------------------------------------------------------------------//
//                                                                              //
//  OxideNDS - A 2D + 3D Game/Application Engine for the Nintendo DS (NTR),     //
//  built on devkitARM and libnds.                                              //
//                                                                              //
//  Copyright (C) 2022 - 2022 Conaer Macpherson a.k.a Corvance                  //
//                                                                              //
//  https://www.github.com/corvance/oxide-nds                                   //
//                                                                              //
//------------------------------------------------------------------------------//

//------------------------------------------------------------------------------//
//                                                                              //
//  OxideNDS is licensed under the terms of the MIT License, available at       //
//  the file LICENSE in the root of this Git repository.                        //
//                                                                              //
//  If you discover any bugs, issues or room for improvement, open an           //
//  issue.                                                                      //
//                                                                              //
//------------------------------------------------------------------------------//

/**
 * @file ox_3d.c
 * @author Corvance
 * @brief Initialisation and general functionality for the 3D component.
 * @version 0.1
 * @date 2022-02-26
 */

#include <3d/ox_3d.h>

//------------------------------------------------------------------------------//
// PUBLIC CODE                                                                  //
//------------------------------------------------------------------------------//

void oxInit3D_Main()
{
    debug_info("Initialising OX 3D Main.\n");

    // Set mode 0, enable BG0 and set it to 3D.
    videoSetMode(MODE_0_3D);
    glInit();

    glEnable(GL_ANTIALIAS);

    // Setup the rear plane.
    // BG must be opaque and have a unique poly ID for anti-aliasing to work.
    glClearColor(COMMON_CLEAR_COLOR_RED, COMMON_CLEAR_COLOR_GREEN, COMMON_CLEAR_COLOR_BLUE, COMMON_CLEAR_COLOR_ALPHA);
    glClearPolyID(CLEAR_POLY_ID);
    glClearDepth(GL_MAX_DEPTH);

    // Create main screen viewport.
    glViewport(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    // Set up the projection matrix.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 256.0 / 192.0, 0.1, 100.0);
    glPolyFmt(POLY_ALPHA(COMMON_CLEAR_COLOR_ALPHA) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1 | POLY_FORMAT_LIGHT2);

	gluLookAt(0.0, 0.0, 1.0,	// Camera position XYZ.
			  0.0, 0.0, 0.0,	// Look at XYZ.
			  0.0, 1.0, 0.0 );	// Unit vector describing which direction is up.

	// Setup default material properties.
	oxInitDefaultMaterial(RGB15(31, 31, 31), RGB15(26, 26, 26),
									RGB15(22, 22, 22), RGB15(0, 0, 0));
	// Generate shinyness table.
	glMaterialShinyness();
}

void oxShutdown3D()
{
    debug_info("OX 3D Shutdown\n");

    // Hide BG0 and disable 3D.
    REG_DISPCNT &= ~(DISPLAY_BG0_ACTIVE | ENABLE_3D);

    // Power off 3D hardware.
    powerOff(POWER_3D_CORE | POWER_MATRIX);
}

void oxBeginFrame()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
	glLoadIdentity();
}

void oxEndFrame()
{
    glPopMatrix(1);
	glFlush(0);
}