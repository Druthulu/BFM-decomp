---
ts: 2026-11-06T05:33:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vFIUE5y8jI0X9p40PMWV
---
h1 = 14, others 8.

I'm at ~25 tries. Let me try 5 more targeted ideas, then decide.

Actually, let me reconsider the problem from scratch. Maybe the copy that survives isn't `tmp = iVar2` but rather... Let me look at the orig's *greg* dump to see the allocation and the launder's effect.

Hmm, alternatively — maybe I can find the actual original source in the game's code style. The function is `func_80181784` in ov_SC01_005. The decompiled source uses iVar1/iVar2/tmp names. The target asm has the copy. Maybe the *real* original source is:

```c
void func_80181784(s32 a0) {
    s32 *p;
    s16 v;
    ...
    func_80181B00(a0);
    func_801820F8(a0);
    p = ((Unk*)a0)->unk20;
    v = *(s16*)(p+0x10);
    if (v != 0) {
        s32 t = v;     // ?
```

Hmm.

Wait — maybe the key is that `tmp` is used with `(s16)tmp` in the store: `((Unkstruct_800B5CB8 *)iVar1)->unk10 = (s16)tmp;`. And the condition `if (0 < tmp * 0x10000)` uses the SI tmp.

What if the copy `move v0,a0` is actually the *sign-extension* of a HImode load: i.e., `iVar2` is HImode and `tmp` is its sign-extended SI copy. We saw `lh` loads directly sign-extended. gcc's RTL: HI reg + sll/sra. Combine folds sll/sra into the lh (the load's sign extension is free). But then `tmp = iVar2` would be the SI value = the same register as the lh dest → no copy.

Unless the tests use the HImode value (needing the raw register) and the arms need the SI value... same register.

Hmm.

Let me look at the target's `move v0,a0` differently: maybe it's not tmp=iVar2 but the *comparison* result? No, beqz/bgez are direct.

OK, let me try 5 more then WALL:
i1: `tmp = iVar2;` with iVar1 declared `void *` and CAST via u8*.
i2: `tmp = iVar2;` and the arms' store uses `tmp` but with a `(s16)` on the *variable* — same.
i3: `iVar2` declared at function scope but assigned via a temp: `s32 t2 = CAST_SIGN(...); iVar2 = t2;`
i4: `tmp = iVar2;` where the copy is `tmp = iVar2 * 1;`? folds.
i5: `tmp = iVar2;` inside a do-while that wraps the whole if.
i6: the second test `if (iVar2 < 0)` written as `if ((s16)iVar2 < 0)`.
i7: `tmp = iVar2;` and add `iVar2 = iVar2;`? self-copy deleted.

Let me try i3, i5, i6, and also try making iVar1's live range shorter by moving the CAST_SIGN for the second block before... no.

Hmm, let me think about i3: `s32 t2 = CAST_SIGN(s16, iVar1, 0x10); iVar2 = t2;` — adds a copy (which folds).

Actually, let me try something different: what if the whole `tmp` business is written with the copy in the *else* direction:
```c
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
if (iVar2 != 0) {
    if (iVar2 < 0) {
        tmp = iVar2 + 0x80;
```
Then the addiu computes directly from iVar2 (a0) into tmp (v0): `addiu v0,a0,128`. The target has `move v0,a0; addiu v0,v0,128`. So no.

Let me now check the time and decide. Let me run date.
