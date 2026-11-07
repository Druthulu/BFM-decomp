---
ts: 2026-11-06T16:46:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3YOeo3w5VzFGOz8J325f
---
no_t0c: the only real difference is:
```
122 addiu s3,s4,12    | addiu v0,s4,12
123 --                | move s3,v0
```
So target computes `addiu v0,s4,12; move s3,v0` (t0c = buf + 0xC into v0, then prim = t0c into s3), while mine does `addiu s3,s4,12` directly. Plus the branch offsets (from the extra insn).

So the target has a genuine copy: t0c in v0, prim in s3. In the source:
```
{
    register s32 t0c __asm__("$2");
    t0c = (s32)((u8 *)buf + 0xC);
    prim = (u8 *)t0c;
}
```
So t0c = buf+0xC; prim = (u8*)t0c. Without the pin, gcc folds t0c into prim (copy propagation) producing `addiu s3,s4,12`.

To keep the copy without a pin, we need cse to not merge t0c with prim. Options:
- Make prim a different type? `prim = (u8 *)(s32)t0c;` — still a copy.
- Use t0c after prim's assignment? It isn't used elsewhere.
- Dead-reset? no.

The target: `addiu v0,s4,12; move s3,v0` — the value goes to v0 then copied to s3. Why would the compiler do that? Because t0c was a separate variable with a use... Hmm. In the original source, maybe:
```
prim = (u8 *)((s32)buf + 0xC);
...
primPtrs[0] = (s32)prim;
```
would give addiu s3 directly.

The v0 hop suggests the original code had `prim = (u8 *)buf; prim += 0xC;`? That would be `addiu s3,s4,12` too.

Or: `t0c = (s32)buf + 0xC; prim = (u8 *)t0c;` where t0c is used later? It's not.

Hmm, why would gcc allocate a temporary to v0 then move? Because the value is needed in v0 for something? Actually `func_8005A600((s32)buf, 0, 0, (u16)tpage, 0);` — the call before; buf is s4.

Maybe the original source computed `prim = (u8 *)((s32)buf + 0xC)` where the +0xC was part of a larger expression... 

Alternatively, the v0 hop could come from a *cast*: `(u8 *)t0c` where t0c is s32 and prim is u8* — expand may create a copy through a temp. But we already have that.

Let me look at the target more: `addiu v0,s4,12; move s3,v0`. This is likely a copy that survived because of the pin? No wait, no_t0c removes the pin and mine folds. With the pin, the target (pinned) has the move. Hmm, the pinned version forces t0c=v0, then prim=t0c (move to s3). So the target's move is an artifact of the pin itself? But then the target bytes came from the original game's code, not from our pins... The src body was crafted to match; the pin reproduces a genuine move in the original.

So the original code had something that produced `addiu v0; move s3,v0`. Since the value 12+ buf is used later in primPtrs[0] = (s32)prim (a store), and prim is the loop pointer.

Maybe the original was:
```
prim = (u8 *)func_80010A08(0x9C);  // no
```

What C produces addiu v0 then move s3? If the variable is `u8 *prim` and the assignment `prim = buf + 0xC;` where buf is `void *` — the addition in Pmode: `addiu s3,s4,12`. A copy would appear if the expression is assigned to an s32 first.

We have exactly that (t0c). Without the pin it's folded because t0c's only use is prim = t0c. To keep it: give t0c another use. E.g., use t0c later in a way that's free? The target doesn't have t0c used elsewhere.

Hmm, what if t0c is used in the `primPtrs[0] = (s32)prim;` line? No, prim is.

What if we declare prim from t0c but make cse unable to merge by a mode difference: t0c is s32, prim is u8* (Pmode=SI). Same mode.

What if t0c is `u32`? same.

Hmm, what if we use a pointer for t0c: `u8 *t0c = buf + 0xC; prim = t0c;` → same fold.

Dead-reset technique (C0414): `t0c = ...; prim = (u8*)t0c; t0c = 0;` — flow deletes the dead set before sched1, but cse's forward scan sees the set and invalidates the equivalence... Actually the dead-reset is designed exactly to stop cse merging two *uses* of the same expression. Here the issue is cse merging t0c into prim's value. A dead-reset after the copy wouldn't prevent the merge of the first use (cse scans forward; the set t0c=... then prim=t0c; at that point t0c is the canonical?).

Hmm, actually which direction does cse merge? `prim = t0c` is a copy; cse makes prim eqv to t0c, then rewrites later uses of prim to t0c? But prim is used later (primPtrs[0], AddPrim) and stays in s3, so no.

The fold happened at expand/combine: `t0c = buf+0xC; prim = (u8*)t0c;` → prim is just t0c; combine folds the copy into the addiu destination.

Hmm, what if prim's declaration is at a different scope/order such that... no.

Alternative: make the copy *not* a copy by using t0c in a comparison? e.g. `if (t0c) prim = (u8*)t0c;` adds a branch. No.

What about making t0c the *first* use of buf and prim = t0c + 0? adds.

Let me think about the actual original code. Maybe the original was:
```
prim = (u8 *)buf + 0xC;
...
primPtrs[0] = (s32)prim;
```
but with `buf` being `s32`? Or maybe the original had:
```
u8 *prim = (u8 *)((s32)buf + 0xC);
```
Hmm.

Wait — maybe the v0 hop comes from the *order*: `primPtrs[1] = buf+0x30; primPtrs[2] = buf+0x54; primPtrs[0] = prim; primPtrs[3] = buf+0x78;` In the target assembly:
```
addiu v0,s4,12
move s3,v0
lui s5,0
addiu s5,s5,0
addiu s0,s4,46   (fp = prim + 0x22)
addiu v0,s4,38
addiu v0,s4,48
addiu v0,s4,84
addiu v0,s4,120
sw s3,24(sp)     ; primPtrs[0]
```
Interesting: the target computes all the primPtrs. `addiu v0,s4,38` is buf+0x26? Hmm, 38 decimal = 0x26. primPtrs[1] = buf+0x30 = 48. So 38 is... fp-0x1E? Hmm no, these are before the loop.

Actually target lines 127-135: `addiu s0,s4,46` (fp? no, fp = prim+0x22 = buf+0x2E = 46 decimal! yes s0 = fp = buf+0x2E), `addiu v0,s4,38` (buf+0x26 = prim+0x1A?), `addiu v0,s4,48` (0x30 = primPtrs[1]), `addiu v0,s4,84` (0x54), `addiu v0,s4,120` (0x78). And `sw s3,24(sp)` = primPtrs[0] (sp+0x18 = index 0 → 24(sp)). So primPtrs[0]=prim (s3).

And `addiu v0,s4,38` = buf+0x26 = prim+0x1A — that's `*(s16 *)(fp - 0x1A)`? fp-0x1A = buf+0x2E-0x1A = buf+0x14. Hmm no. 38 = 0x26; fp = 0x2E; 0x2E-0x26 = 8. Hmm, maybe it's `*(s16 *)(cbase + 0x18 + ...)`? no.

Wait, maybe 38 is for `primPtrs[1]`? 0x30=48. So 38 is something else. Looking at source: primPtrs[1] = buf+0x30, [2]=buf+0x54, [0]=prim, [3]=buf+0x78. And the cbase = (s8*)primPtrs. So 38=0x26 doesn't appear. Hmm, maybe it's `buf + 0x26`? Not in source. Let me not chase.

Focus: t0c → prim copy. Mine folds; target keeps the move. To keep a copy alive without a pin, one option: make the copy's source used again *after* the copy, so it can't be folded. E.g.:

```
t0c = (s32)((u8 *)buf + 0xC);
prim = (u8 *)t0c;
... later use t0c in a way that's free
```
Is there any free use? Maybe `primPtrs[0] = t0c;` instead of `primPtrs[0] = (s32)prim;`! If the source wrote `primPtrs[0] = t0c;` then t0c has 2 uses: prim = t0c and the store. But then the store would need t0c live until then (it's at line 3883, after primPtrs[1] and [2]). In the target, `sw s3,24(sp)` stores s3 = prim, not v0. So the store uses prim's register s3, not t0c's v0. Hmm, that means t0c isn't used at the store.

Alternatively the original source could be:
```
prim = (u8 *)buf + 0xC;
```
with a *different* variable for the v0 hop: maybe `t0c` was `(s32)buf + 0xC` used for the fp computation? fp = prim + 0x22.

Hmm, let's look at the pinned target assembly around there to understand exactly.

Let me dump the target function's asm (build object) and the pinned o1.s (my dump of orig with pins). Then compare to no_t0c.

Actually the simplest: since no_t0c only loses the `addiu v0; move s3` pair, maybe I can get the same pair by using a dead-reset or a different C form. Let me try:
- `t0c = (s32)buf; t0c += 0xC; prim = (u8 *)t0c;` (two statements) — expand may keep t0c as a pseudo and prim as a copy; combine may still fold.
- `prim = (u8 *)buf; prim = (u8 *)((s32)prim + 0xC);` → prim's def twice; maybe addiu into prim's reg directly.
- Use a union/pointer cast.
- `prim = (u8 *)((s32)buf + 0xC); if (prim) {}` no.

Let me test a batch of C variants for this line, scoring with the other pins present (so the residual isolates this change).

Variants (with ot and fp pins kept, t0c unpinned):
v1: current nopin t0c (score 5)
v2: `s32 t0c; t0c = (s32)buf; t0c += 0xC; prim = (u8 *)t0c;`
v3: `s32 t0c; t0c = (s32)((u8*)buf + 0xC); prim = (u8*)t0c; t0c = 0;` (dead-reset)
v4: `u8 *t0c; t0c = (u8*)buf + 0xC; prim = t0c;`
v5: `prim = (u8*)((s32)buf + 0xC); prim = (u8*)(s32)prim;` — silly.
v6: `s32 t0c; t0c = (s32)buf + 0xC; primPtrs[0] = t0c; prim = (u8*)t0c;` and remove the later primPtrs[0] line — changes store source to v0 (target uses s3). no.

Hmm. Let me look at the pinned target assembly to see if v0 is used for anything else between addiu and the move. Maybe t0c's value is stored into primPtrs[0] later? The target `sw s3,24(sp)` uses s3.

Let me get the target's exact assembly first.
