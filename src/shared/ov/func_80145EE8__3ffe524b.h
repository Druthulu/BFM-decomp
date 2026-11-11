/* func_80145EE8 — shared body (overlay slot 0x80128158, h_exact 3ffe524b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80145EE8(s32 param_1)
{
    switch (param_1) {
    case 0:
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x1F) != 0) {
            ((void (*)(void *))guess_MoveImageList)(D_80180C38);
        }
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x21) != 0) {
            ((void (*)(void *))guess_MoveImageList)(D_80180C68);
        }
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x1E) != 0) {
            ((void (*)(void *))guess_MoveImageList)(D_80180CB8);
        }
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x1D) != 0) {
            ((void (*)(void *))guess_MoveImageList)(D_80180CE8);
        }
        if (((unsigned char (*)(int))guess_TestGameFlag)(0x20) == 0) {
            return;
        }
        ((void (*)(void *))guess_MoveImageList)(D_80180D18);
        break;
    case 1:
        ((void (*)(void *))guess_MoveImageList)(D_80180C38);
        ((void (*)(void *))guess_MoveImageList)(D_80180C68);
        ((void (*)(void *))guess_MoveImageList)(D_80180CB8);
        ((void (*)(void *))guess_MoveImageList)(D_80180CE8);
        ((void (*)(void *))guess_MoveImageList)(D_80180D18);
        break;
    }
}
