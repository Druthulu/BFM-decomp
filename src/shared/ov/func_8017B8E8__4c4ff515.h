/* func_8017B8E8 — shared body (overlay slot 0x80128158, h_exact 4c4ff515). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: lwr $v0, 0x8($a0) at ov_SC03_126:0x8017B91C; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x54, ov_SC03_126 objdump */
s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_8018F98C) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_8018F984) = ((S8_8017B8E8 *)src)[1];
}
