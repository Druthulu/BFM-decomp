---
ts: 2026-10-22T08:02:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ypXZzgF1HvlS9dlMPq8d
---
Very interesting!

**801880E0**: current win.c already has the structure but score 29ish; the diff shows the w/ot swap (s1<->s2) and the missing `move s0,s4` + `sltu a0,zero,s0`. Wait, the current win.c doesn't have the s16 flag change nor the `ot = func_800D27DC(...)` split. Let me apply the G02 moves:
- flag2/flag3/flag4 → s16
- `ot = func_800D27DC(flag4 != 0, ot, w->f4, w->fC, 0);` split before return
- keep `w` as a local `w = w0;`

The diff shows target has `move s0,s4` at 91 — that's the flag4 = flag2 + zr copy (addu s0,s4,zero). And `sltu a0,zero,s0` at 93 (vs mine 68 `sltu a0,zero,s4`). So mine has flag4 aliased to s4 (cse merged) → need the s16 trick.

Great, so applying the G02 moves should crack it.

**8017E6EC**: score 6, diff shows the li v0,16 / lhu swap. Target has `li v1,16` and `lhu v0,52(s1)`. So in target, the constant 0x10 is in v1 and the loaded value in v0. Mine has the reverse. The note says: t4 is a global pseudo crossing the goto; global-alloc gives it a reg after local-alloc gave $2 to the block-local constant.

So we need the constant 0x10 to be in v1 and the global t4 in v0. Hmm. In the target: `li v1,16` (materializing 0x10) and `lhu v0,52(s1)` then `sw v1,28(s1)`?? Wait: target[106]=`lhu v0,52(s1)`, target[107]=`sw v1,28(s1)`. So the store of 0x10 uses v1 (the constant) and the load uses v0.

Hmm wait: `((Unkstruct_800B5CB8 *)arg0)->unk1C = 0x10;` is in case 2 → `li v1,16; sw v1,28(s1)`. And the lhu v0,52(s1) is a separate load. So in the target the constant 0x10 got v1 and the lhu got v0.

In mine: `li v0,16` (constant in v0), `lhu v1,52(s1)` (load in v1). Then sw v0.

So we need to swap: constant → v1, load → v0.

Then at 154: target `lhu v0,52(s1)`, `addiu v0,v0,1`, `sh v0,52(s1)`. Mine: `lhu v1,...; addiu v1,v1,1; sh v1,...`. So the second load also needs v0.

Hmm, in mine, the constant 0x10 took v0 and the loads took v1. In the target the constant took v1 and the loads took v0. So it's a global-alloc ordering issue: the constant 0x10 is a block-local constant (case 2) and the loads are... hmm.

Actually per the note: "the group `t4` is a GLOBAL pseudo (its value crosses the goto lab_e958), so global-alloc gives it a register only after local-alloc has already handed $2 to the block-local constant 0x10 (live 104..107, overlapping t4's 105..156)".

Hmm wait, that says the constant gets $2 and t4 gets $3. But in the actual target the constant is in v1 ($3) and t4 in v0 ($2). Let me re-read: "t4 therefore gets $3/v1 and the constant gets $2/v0, the exact mirror of the target. The target's assignment ($2 for the global, $3 for the local constant)".

So target: t4 (global) → $2, constant → $3.

Currently mine: constant → $2 (v0), t4 → $3 (v1). So we need to flip.

The global pseudo t4 spans from its def (case 4 lab_e954, or case 2) to lab_e958 and beyond. Local-alloc assigns $2 (v0) first to the block-local constant 0x10 which is live 104..107. Then global-alloc assigns $3 to t4.

To flip: we need the local constant NOT to take v0, or t4 to be allocated first.

Options:
- Make the constant not a separate pseudo: e.g. `((Unkstruct_800B5CB8 *)arg0)->unk1C = 0x10;` → the store needs a register holding 0x10. If we make it `t4 = 0x10;` then `unk1C = t4;`? That changes t4's value. Hmm, but in the target, `li v1,16` is a separate constant reg v1, and `sw v1,28(s1)`.

Hmm, actually if the constant 0x10 were part of t4's value... no, t4 holds unk34+1.

Alternative: restructure so the constant 0x10 is materialized later or is a different pseudo with a different birth.

Hmm, what if we write the store as `((Unkstruct_800B5CB8 *)arg0)->unk1C = (s32)0x10;` — same.

What about making the constant live in a way that local-alloc prefers differently? E.g. the constant pseudo's live range 104..107 — it overlaps t4's range so they conflict; local-alloc gives v0 to the constant because local-alloc runs first (local-alloc handles block-local pseudos; global-alloc handles the cross-block ones).

Actually gcc's reg allocator: `global_alloc` assigns registers to pseudos that live across blocks (in the "global" set), and `local_alloc` assigns the rest. Order in gcc 2.7: `local_alloc` is called... hmm. In gcc's flow.c, `allocate_registry` → then `global_alloc` for the "global" pseudos and `local_alloc` for local ones. Actually in gcc 2.7 flow.c: `allocate_registry` builds the reg order; then `global_alloc` is called (in `allocate_registry`? no). Let me recall: flow.c `allocate_registry()` → `reg_alloc` ... The order: `local_alloc()` is called first (for regs not needing global allocation), then `global_alloc()`. Yes — in gcc 2.7, `local_alloc` comes before `global_alloc` in `allocate_registry`.

So the local constant gets v0 first. To make t4 get v0, the constant must not be a local pseudo — i.e. the constant must be cross-block, or the constant must be eliminated.

Idea: if the store `unk1C = 0x10` is done with the value being a cross-block pseudo... hmm.

Alternatively: what if the constant 0x10 is materialized as part of a value that is live across blocks? E.g. `t4 = 0x10; ... unk1C = t4;` no, t4 is used differently.

Hmm — wait. Actually maybe simpler: reorder so that the constant is materialized in a block where it's the *second* local pseudo to need v0. E.g., if another local pseudo already took v0 in local_alloc, then the constant would take v1.

The target at 104: `li v1,16`. What's in v0 at that point? target[105] `lhu v0,52(s1)`. So v0 is used by the load. In mine at 104: `li v0,16`, 105: `lhu v1,52(s1)`.

The lhu loads are local pseudos in their blocks too! In the target, the load at 105 gets v0 and the constant gets v1. So in local_alloc, the load is allocated before the constant? Or the load is a "global" pseudo? The load at 154 is `lhu v0,52(s1)` in the case-4 block — that feeds t4 which is global.

Hmm, in the target the lhu at 105 is in case 2 (after `func_8017ECC4`), and 154 in case 4. These loads are the sources of `t4` (global). Wait no.

Hold on. Let me re-map. Original source case 1:
```
c = arg0->unk94;
if (c == 0x10) {
    t = CAST_SIGN(u16,arg0,0x106) + 1;     // t1
    arg0->unk106 = t;
    if ((t<<16)>>16 == 2) { arg0->unk98=0; t = arg0->unk34+1; arg0->unk34=t; ...}
}
...
t = CAST_SIGN(u32,arg0,0x1C)+1;             // t3
arg0->unk1C = t;
```
case 2:
```
...
t = arg0->unk34;   // t4
arg0->unk1C = 0x10;
goto lab_e958;
```
case 4:
```
...
t = CAST_SIGN(u32,arg0,0x1C)+1;   // t5
arg0->unk1C = t;
...
lab_e954:
t = arg0->unk34;   // t4
lab_e958:
t = t + 1;
arg0->unk34 = t;
```

So t4 is defined in case 2 (and case 4 at lab_e954) and used at lab_e958. It's cross-block → global pseudo.

The `li v1,16` at insn 104 and `sw v1,28(s1)` at 107: that's `arg0->unk1C = 0x10` in case 2. And `lhu v0,52(s1)` at 105 is `CAST_SIGN(u16,arg0,0x106)`? No wait, that's in case 1. Hmm, 0x106/4 = 0x41 = 65. 52 = 0x34 = unk34. So `lhu v0,52(s1)` loads unk34 (u16?). Hmm.

Hmm, in the target at 154-157: `lhu v0,52(s1); addiu v0,v0,1; sh v0,52(s1)`. That's `t = (u16)arg0->unk34 + 1; arg0->unk34 = t;` at lab_e958 (t = t+1 where t = unk34). So `lhu` loads unk34.

And at 104-107: `li v1,16; lhu v0,52(s1); sw v1,28(s1)`. Hmm — the lhu v0,52(s1) loads unk34 and... where's it used? Probably the `sh` later? Actually 107 `sw v1,28(s1)` = unk1C = 0x10 (offset 0x1C = 28). So at 104: li v1,16 (the constant 0x10), 105: lhu v0,52(s1) — that's the t4 = unk34 load, 106: ? (target[105:106] not shown, but target[104:106] vs mine[104:106] replaced). Let me get the full target listing to be sure.

Actually, from the diff: "replace mine[104:106] target[104:106]: 104 li v0,16 | li v1,16; 105 lhu v1,52(s1) | lhu v0,52(s1)". So 3 instructions replaced by 3; target[106] = mine[106] presumably (a `sh v0,52(s1)`? no...). Hmm, mine[106] is the same as target[106]. Then target[107] = `sw v1,28(s1)` vs mine[107] = `sw v0,28(s1)`.

Hmm so mine[106] is some instruction common. Actually the diff replaces [104:106] with [104:106] and separately [107:108] with [107:108]. So mine[106]==target[106] and mine[105] != target[105]... wait no, "replace mine[104:106] target[104:106]" lists lines 104 and 105 only. That means line 106 matched. Hmm, but that's weird: if 105 differs and 106 matches, the tool shows the changed block.

OK whatever. The gist: in target, the constant 0x10 → v1, and the loads of unk34 → v0.

In mine: constant → v0, loads → v1.

The note says the residual is that local-alloc gives v0 to the block-local constant. Hmm but wait — in mine the lhu (load) also is local. Hmm.

Hmm, in the target: at 104 `li v1,16` — the constant is in v1, and the load `lhu v0,52(s1)` in v0. The load at 105 feeds... `sh v0,52(s1)`? but 106 matched between mine and target, and mine[107]=sw v0,28(s1) vs target sw v1,28(s1). Hmm, so 106 is probably `sh v0,52(s1)`? No...

Let me just get the full target asm. Is there a way? delever_search --explain? Or the build/ dir has the .s? Let me check build/.

Actually let's use `tools/cc1_dumps_tu.sh` or find the reference asm. Let me check if there's an objdump of the target available. The delever_search compares with "the function in build/". So build/ has the compiled target. Let me find the .o and objdump it.

Let me check the build dir.

OK, I'm spending a lot of time. Let me prioritize: 4 items, 20-30 min each. Let me start with the most promising: 801880E0 (G02 moves known), then 80182ED4, then 8018302C, then 8017E6EC.

Let me first write the 801880E0 candidate based on G02's win.c and score it.

G02's win.c for 8017E978:
```c
s32 *func_8017E978(s32 *ot, Panel_8017E978 *w0, s16 idx) {
    Panel_8017E978 *w;
    u8 sp18[72];
    s32 sp60[2];
    s32 flag;
    s16 flag2;
    s16 flag3;
    s16 flag4;
    s16 i;
    Prim4_8017E978 *p;
    s32 r;

    w = w0;
    flag = -(D_8011511A != idx) & 0xFF;
    func_80024054(w->f14, sp18);
    flag2 = flag;
    ot = func_800D2650(ot, sp18, w->f10, w->f12, 1, flag != 0 ? 0x585858 : 0x808080);
    ot = func_8017EFA8(ot, w->f18, idx, w->f8, flag2 != 0 ? 0x585858 : 0x808080);
    i = 0;
    flag3 = flag2;
    p = w->f18;
    for (;;) { ... }
    flag4 = flag2;
    ot = func_800D27DC(flag4 != 0, ot, w->f4, w->fC, 0);
    return func_800D29F8(flag4, ot, w->f8, w->fE, 0);
}
```

For 801880E0, the analog:
```c
s32 *func_801880E0(s32 *ot, Panel_8017E978_801880E0 *w0, s16 idx) {
    extern u16 D_8011511A;
    Panel_8017E978_801880E0 *w;
    u8 sp18[72];
    s32 sp60[2];
    s32 flag;
    s16 flag2;
    s16 flag3;
    s16 flag4;
    s16 i;
    Prim4_8017E978_801880E0 *p;
    s32 r;

    w = w0;
    flag = -(D_8011511A != idx) & 0xFF;
    func_80024054(w->f14, sp18);
    flag2 = flag;
    ot = func_800D2650(ot, sp18, w->f10, w->f12, 1, flag != 0 ? 0x585858 : 0x808080);
    ot = func_8018893C(ot, w->f18, idx, w->f8, flag2 != 0 ? 0x585858 : 0x808080);
    i = 0;
    flag3 = flag2;
    p = w->f18;
    for (;;) {
        r = func_801882AC(w->f1C, w->f0, idx, i++, sp60);
        if (r == 0) break;
        if (r < 0) {
            func_80024054((void *)r, sp18);
            if (flag3 != 0) sp60[0] += -0x282828;
            ot = func_800D2650(ot, sp18, p->f0, p->f2, 1, sp60[0]);
        }
        p++;
    }
    flag4 = flag2;
    ot = func_800D27DC(flag4 != 0, ot, w->f4, w->fC, 0);
    return func_800D29F8(flag4, ot, w->f8, w->fE, 0);
}
```

Note the original src uses `w->f14` etc. with w being the pinned local. Also note original had `flag2 = flag + zr;` → now `flag2 = flag;`.

Wait: careful. The G02 version kept `flag2 = flag;` (no +zr) and it matched — because s16 flag2 escapes cse.

But there's a subtlety: `flag2` s16 while flag is s32 with value 0..255 → sign_extend:HI of a value 0..255 → combine nonzero_bits knows bits 8-15 are zero and bit 15 is 0 → sign extension is a no-op → plain move.

And `flag4` s16 = flag2 → same.

And `flag3` s16 = flag2 → same.

Then `flag2 != 0` test → `sltu`/`sne`? With s16 flag2 and the compare `flag2 != 0`, gcc compares sign-extended... The target uses `sltu a0,zero,s4` — hmm, at 68 mine `sltu a0,zero,s4` vs target `nop`. Interesting: the target has a `nop` there. Hmm.

Anyway — apply and score. Let's write it.

Note: `D_8011511A` is `extern u16` declared inside the function in the src. I'll keep that.

Also `i` is s16 in G02's version; in src it's s16. Good.

Let me write the file as c1.c in the item dir and score.

Let me now do it.
