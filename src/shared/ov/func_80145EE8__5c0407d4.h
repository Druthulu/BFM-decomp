/* func_80145EE8 — shared body (overlay slot 0x80128158, h_exact 5c0407d4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80145EE8(s32 param_1)
{
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x1F) != 0) {
            ((void (*)(void *))guess_MoveImageList)(D_80180484);
        }
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x21) != 0) {
            ((void (*)(void *))guess_MoveImageList)(D_801804B4);
        }
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x1E) != 0) {
            ((void (*)(void *))guess_MoveImageList)(D_80180504);
        }
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x1D) != 0) {
            ((void (*)(void *))guess_MoveImageList)(D_80180534);
        }
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))guess_MoveImageList)(D_80180564);
        break;
    case 1:
        ((void (*)(void *))guess_MoveImageList)(D_80180484);
        ((void (*)(void *))guess_MoveImageList)(D_801804B4);
        ((void (*)(void *))guess_MoveImageList)(D_80180504);
        ((void (*)(void *))guess_MoveImageList)(D_80180534);
        ((void (*)(void *))guess_MoveImageList)(D_80180564);
        break;
    }
}
