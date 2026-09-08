/* func_80171928 — shared body (overlay slot 0x80128158, h_exact d6fa4f05). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80171A1C(u8 *a0);
void func_80171928(void * a0)
{
    unsigned char idx     = *(unsigned char *)((char *)a0 + 0x214);
    unsigned int *base    = *(unsigned int **)((char *)a0 + 0x1FC);
    unsigned int  cur     = *(unsigned int *)((char *)a0 + 0x1F8);
    *(unsigned int *)((char *)a0 + 0x1F8) = base[idx] | (cur & 0x7F000000);
    ((void (*)(void *))func_80171A1C)(a0);
}
