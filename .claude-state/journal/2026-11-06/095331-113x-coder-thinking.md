---
ts: 2026-11-06T16:53:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_y3Xt1BXwdufJbpO9yuNl
---
no_ot: cnt is in t1, target t0. Also `lw t0,0(at)` vs `lw t1,0(at)` — ot load: mine t0, target t1. So the registers t0/t1 are swapped between cnt and ot.

With the ot pin ($9=t1), ot is t1 and cnt gets t0. Without, cnt=t1 and ot=t0.

To fix lever-free: make cnt take t0 and ot t1. cnt = RotTransPers(...) result; ot = a load. The priority: cnt is used in the div and the loop (cnt << 2 → used in otAddr = ot + cnt and prim += ...?). cnt is live from the call to otAddr computation. ot is loaded just before otAddr.

If cnt has higher priority than ot, cnt gets the lower reg (t0). In mine, cnt=t1 (higher) and ot=t0. Hmm, so cnt got the higher (t1) because it's allocated first? The allocation order: the first-allocated gets the lowest free reg (t0). So cnt was allocated after ot? or ot before cnt.

ot's birth: after the div (ot = load). cnt's birth: at the call (move v0). The allocno order by regno: cnt is pseudo X created early, ot created later. Local-alloc/global-alloc: both are block-local? cnt is live across blocks? cnt is used in the div (same block) and later in otAddr (same block?) — the function has no branches between; so both are block-local to the big block. Local-alloc assigns by priority.

Priority: cnt refs: def(call), use(blez), def(sll), use(div, bnez, bne, bne?) → many refs. ot refs: def(load), use(addu) → 2 refs. cnt should have much higher priority → gets t0. But mine gives cnt=t1.

Hmm, wait: maybe local-alloc assigned t0 to the ot *load* because... Let me look: mine[80] `lw t0,0(at)` (ot), mine[84] `addu s6,t0,t1` (otAddr = ot + cnt). So ot=t0, cnt=t1.

In the pinned version, ot=t1 (pin) and cnt=t0.

The local-alloc priority: cnt's qty has more refs and a longer life → higher priority → t0. Unless cnt's pseudo is a *global* allocno (live across blocks) and ot is block-local; local-alloc assigns block-locals first, taking t0! Yes: ot (block-local, short) gets t0 in local-alloc; then global-alloc gives cnt t1 (t0 taken).

In the target, the pin forces ot=t1, so cnt gets t0.

To get cnt=t0 without pinning ot: make cnt block-local too? cnt is live across the two `if (cnt <= 0) return;` branches → it's a global allocno. In the target, cnt is in t0 — a caller-saved reg used across branches (fine, no calls in between).

So: ot is block-local and takes t0 first. To prevent, make ot's allocation not take t0: e.g., give ot a longer life so it becomes global (then it competes with cnt by priority and loses → gets t1). How to extend ot's live range? Use ot earlier (before the div) — e.g., load ot before the div? The source loads it after sc. If we move the ot load earlier (before the div), it'd be live across the div, still block-local.

Make ot live across a branch: e.g., use ot in the loop (it is: AddPrim(otAddr, prim) uses otAddr, not ot). Hmm.

Alternatively make cnt's priority higher so that even as a global it gets t0? Global-alloc can't take t0 if a block-local took it.

Alternatively, avoid the separate `ot` variable: compute `otAddr` directly from the load:
```
otAddr = *(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + cnt;
```
Then there's no ot variable. The load's temp is block-local and short; the add uses it. That could change allocation: the load temp might still take t0.

Hmm. But in the target, the load is `lw t1,0(at)` and the addu `addu s6,t1,t0`. The target's ot is t1 — the pin.

Since the target is what it is, we need the load result in t1 while cnt is t0.

What if cnt is used *before* the ot load in a way that allocates t0 first? Local-alloc processes insns in order and assigns registers as it encounters defs? No, it collects quantities and sorts by priority.

Actually the local-alloc assignment order is by priority (refs*size/life), computed over the block. ot: 2 refs, life 2 insns → pri = 2/2 = 1.0. cnt as a global isn't in the block's local list. Other block-locals (sc, sx, sy, d, t, m, etc.) also compete. t0/t1 are caller-saved; the first high-priority block-local gets t0.

In the target (pinned), ot=t1 fixed; cnt=t0.

Can we make ot a global (cross-block) allocno? If ot were used inside the loop (e.g., AddPrim(ot, prim) instead of otAddr?), the source uses otAddr in the loop. If we changed the loop to use `ot` directly... the target's loop uses otAddr (s6) I think.

Hmm, what if we make ot's live range cross the `if (cnt<=0) return;` branches? E.g., load ot BEFORE the cnt check. Then ot is live across branches → global allocno → competes with cnt by priority. cnt has more refs → cnt gets t0 first, ot gets t1. And the target's ot load position is after the div (line ~80), but if we load ot earlier, the instruction order changes → mismatch. Unless sched1 moves the load later? A load from memory can't be moved across... it could be sunk? sched1 might sink it to its use. Risky but let me try:

Move `ot = *(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14));` to before `cnt = RotTransPers(...)`? That changes the live range and the instruction order (sched1 might sink the load down since it has no dependencies). Actually the load depends on D_800B9A02 (a global) and D_800A651C; it could be scheduled anywhere. sched1 might place it right before its use, as in the target.

That's a promising move! Let me test: variant ot_early: move the ot load line to just before `cnt = RotTransPers(...)`.

Similarly for the t0c pin: `t0c = (s32)((u8 *)buf + 0xC); prim = (u8 *)t0c;` — need the addiu v0/move pair. Making t0c used later (live across blocks) might force the copy: e.g., move the t0c assignment earlier? Or make prim's value come from t0c in a later statement.

Let me try the ot_early idea first (with fp and t0c pinned, so if it works we get PARTIAL:$16).
