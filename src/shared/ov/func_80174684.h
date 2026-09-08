/* func_80174684 — shared body (overlay slot 0x80128158, h_exact 1d3fce0c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u8 D_80126D6C;
extern void (*D_80127088)(void);
extern s32 D_801270BC;
void func_80174684(void* a0)
{
    D_80126D6C = 0;
    (*(void * *)&D_80127088) = a0;
    D_801270BC = 0;
}
