#ifndef __GLUTGAME_RENDER_H__
#define __GLUTGAME_RENDER_H__
uint64_t glutGameRenderScreenWidth();
uint64_t glutGameRenderScreenHeight();
void glutGameRenderSceneSet(void (*fnc_p)());
void glutGameRenderScene();
void glutGameRender2DScene();
void glutGameRender();
void glutGameRescale(GLint n_w, GLint n_h);
void glutGameRenderFPS();
double glutGameRenderGetFPS();
#endif
