/* func_8013F138 — shared body (overlay slot 0x80128158, h_exact 67cef5a4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013F138(void) {
    u16 *p = &guess_g_MenuTransitionTimer;
    *p += 0x10;
    if ((u16)*p >= 0x40) {
        if (guess_g_OpenMenuId == 0) {
            ((void (*)(int, unsigned char *))guess_OpenTextWindowCenteredAt)((int)guess_GetStoryGoalText(), &D_801805F4);
        }
        guess_g_MenuStep += 1;
    }
}
