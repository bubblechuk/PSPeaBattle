#include <SDL.h>
#include <SDL_image.h>
#include "CGame.h"
#include "CTextureManager.h"
#ifdef PSP
#include <pspuser.h>
#include <pspdebug.h>
#include <pspdisplay.h>

extern "C" int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

extern "C" int callback_thread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

extern "C" int setup_callbacks(void) {
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if(thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}
#endif
extern "C" int main(int argc, char *args[])
{
    #ifdef PSP
    setup_callbacks();
    #endif
    CGame game;
    game.Init(false, false);
    game.Loop();
    game.Destroy();

    return 0;
}