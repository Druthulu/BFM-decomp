---
ts: 2026-11-06T21:01:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iYjTEJBBOmt7E0FgCfAS
---
So target:
- 80: sll a1,s0,2   → off in a1
- 84-8c: at = D_801E8F78 + off; lh v1,0(at)  → lim
- 90-94: lui/addiu a0 = D_801E8F78  → e in a0
- 98: slt v0,v0,v1 (t < lim)
- 9c: beqz
- a0: addu v0,a0,a1  → v0 = e + off
- a4: lh a0,2(v0)

So off = a1, e = a0.

In mine, off = a0, e = a1. So exactly swapped.

This is a global-alloc priority between two pseudos both hard-reg preferences? Actually a0/a1 are caller-saved. off and e are both local to the block but live across the call to func_80029178? Wait no — the call is inside the `if`, after the slt. e and off are used after the call? Let me see: `if (t<lim) { if (*(s16*)((u8*)e+off+2)==0 || (func_80029178(...) & 0xFF)==0) idx=-1; }`. The call func_80029178 takes `*(s16*)((u8*)e+off+2)` as argument. After the call, e/off are not used again (short-circuit ||: the second operand only if first false; the load is before the call). Actually both loads happen before the call in the ||. So e and off die at the call. They don't cross the call.

So they're both short-lived, and global-alloc assigns a0/a1 based on priority. off has: 1 def (sll), uses: addu for lim address? Actually in target off (a1) used at 88 (addu at,at,a1) and at a0 (addu v0,a0,a1). e used at a0 (addu) and that's it? e is lui/addiu into a0 then used once at a0. Hmm e has 1 use; off has 2 uses. So off has more refs → higher priority → should get a0. But target gives a0 to e!

Wait, unless the lim address computation uses off but cse... Hmm. Let me reconsider: maybe in the target, the lim load's address uses a different temp: `lui at; addu at,at,a1`. The a1 there is off. Then e is a0.

Hmm so target has off=a1 with 2 uses, e=a0 with 1 use. That contradicts higher-refs-gets-a0. Unless global-alloc priority is by live_length: e is born at 90 (lui a0) and dies at a0; off born at 80, dies at a0. off has longer live range → but target gives off the *later* free reg?

Actually maybe the assignment order: global-alloc assigns registers to pseudos by priority; the highest priority gets first pick among *available* regs. But the register numbers used are from allocno ordering. Hmm.

Alternatively: the local-alloc (per-basic-block) is doing this, not global-alloc, because these pseudos are used in one block. local-alloc assigns by qty priority too. The order of allocation within the block: it processes quantities in order of priority; the first gets the first free hard reg in a preference order.

Rather than theorize, experiment. The lever that flipped this originally was the launder `e = (s16*)D_801E8F78` via asm with tied operands. That asm pins e to the same register as input... actually "=r"(e) : "0"(e) means output in same reg as input; it doesn't pin a specific hard reg, it forces a 2nd set. Hmm, it forces e to be materialized then re-tied. The effect: e gets an extra definition (2 sets), altering priority.

Since we can't use asm, we need a real-C 2nd set or ref change. Options:
- Make e's value assigned twice: `e = (s16*)D_801E8F78;` then later `e = (s16*)D_801E8F78;`? Redundant; cse may merge. A "real 2nd set" that's value-preserving could work: e.g. compute e from idx? 

Idea: e = (s16*)((u8*)D_801E8F78) — same.

Better approach from catalog: split a real 2nd set: e.g. `e = (s16 *)D_801E8F78;` and then use `lim = D_801E8F78[idx][0];`. Hmm.

Let me look at what makes off get a0 in mine: off is the sll result. In target off is a1. Since a0/a1 are both free, the difference could be simply the *order* in which the allocator encounters them, i.e., which pseudo is "born" first. In target, off is born first (sll at 80) and gets a1; e born second (90) gets a0. In mine off born first gets a0, e gets a1. So it's reversed.

Hmm, so in target the *first-born* gets a1, the second gets a0? That suggests allocation processes highest priority first and gives it... a1? Or the reg preferences: local-alloc qty has a preferred reg derived from something.

Wait — maybe the key is that in the target, the value `D_801E8F78` constant address appears in both `e` and the lim load. cse might represent the lim address as at = sym + off. The `e` is the bare sym. Hmm.

Let me just try many variants quickly and see scores. Ideas:
1. Compute `off` after `lim`: `lim = D_801E8F78[idx][0]; off = idx*4;` — reorders births.
2. Use idx*4 inline in lim and keep off: `lim = D_801E8F78[idx][0]; off = idx*4; e = ...`.
3. Make e a `u8*` then cast at use.
4. Declare e before off (decl order) - already tried, score 4.
5. Make off a u16/s16 (width) - could change sll/sra.
6. Use `e = (s16 *)D_801E8F78;` and then `off` computed as `idx << 2`.

Let me try variant 1 and 2.

Actually, a thought: the target's `sll a1` is `idx*4`; note idx is s16, so `idx*4` might involve sign extension? idx loaded via lbu s0 → so idx is unsigned char value (0..255). sll a1,s0,2 directly, no sra. Fine.

Let me try reordering births: put `off = idx*4` after `lim`. But `lim = D_801E8F78[idx][0]` needs idx*4 internally. That might produce a separate sll or reuse. Let's test.

Also try: use `idx` cast to s32. Hmm.

Let me generate variants.
