---
ts: 2026-11-06T11:07:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1nPrfk6yyPbIVQHiXZM4
---
Still 4. So the direct call isn't the difference.

Let me compare item 3 and item 4 more carefully. Item 4's x_dwafter scored 0. Let me look at the item 4 win.c (x_dwafter) and see its exact structure, then diff against item 3's v_win to spot the difference.

Item 4's C:
```
void func_8018B238(void) {
    extern u16 aD800B9A02 __asm__("D_800B9A02");
    ...
    extern s32 *func_8018B478(s32 *ot, Panel_S40_8018B238 *w0, s16 idx);
    ...
    s16 n;
    ...
}
```
Item 3 uses `Panel_S40_8018B238_80187EA0` types (different names).

Wait, maybe the difference is the `func_8013AB54` call: item 4 has `ot = (s32 *)func_8013AB54((s32)ot, (s32)(D_800AE7BC[aD800B9A02].ot + 2), (s32)D_801C17E8, 0);` — item 3 similar.

Hmm, but the diff shows the problem is only in the loop (positions 73-93), not elsewhere. The rest matches.

So in item 3 the loop's delay slot isn't filled. In item 4 it is. The loop code is identical except the call. Let me diff the two win.c files' loop regions.

Item 3's v_win loop:
```
        do {
            if (D_80115158[i].h != 0) {
                ot = func_801880E0(ot, w, i);
                do { } while (0);  // !FAKE: do-while
            }
            i++;
            w++;
        } while (i < cnt);
```
Wait, in v_win (derived from x_dwafter), the call is still the cast version (v_win was built from x_dwafter, not v_direct). Let me check the order of the do-while: x_dwafter = the call followed by `do { } while (0);`.

Item 4's x_dwafter: same.

Hmm, so why the difference? The functions differ in other parts (the Panel types, the globals). The register allocation of the loop could differ.

Wait — maybe the difference is `func_801880E0` vs `func_8018B478`: the call's return value handling. In item 4, `func_8018B478` returns s32* and is assigned to ot. Same in item 3.

Hmm, but item 3's v_win has n as s16 and the struct alias; item 4's x_dwafter has n as s16 and the struct alias (v_sa). Yes.

Let me diff the two C files to see the structural differences.
