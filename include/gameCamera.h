#ifndef SPACESNAKE_GAMECAMERA_H
#define SPACESNAKE_GAMECAMERA_H

#include "types.h"

typedef struct	s_cameraParams {
	vec3f camDir;
	GLfloat zoom;
	GLfloat zoomMax;
	GLfloat zoomMin;
}				gameCamera;

#endif //SPACESNAKE_GAMECAMERA_H
