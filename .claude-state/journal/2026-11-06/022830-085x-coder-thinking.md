---
ts: 2026-11-06T09:28:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_StFCA3lpkuoRTgOoG09p
---
Clear mapping:
mine -> target: a2->a3 (c80), a3->t0 (cFF), t0->t1 (cDF), t1->a2 (mlo), t2->t3 (0xFF00 mask), t3->t2 (the sym address).

Target: c80=a3, cFF=t0, cDF=t1, mlo=a2, mask=t3, ob/addr=t2.

So target's constant registers: a3, t0, t1, a2, t3, t2. Mine: a2, a3, t0, t1, t2, t3. It's a rotation.

The pin $10 (ob) = t2 in target! `lui t2,0x0; addiu t2` = ob (D_800AA60C address) — yes, $10 = t2. So in target ob is in $10 (t2) due to the pin. In mine, ob got... t3? And the sym address got t2. The mapping mine->target: t3->t2 means mine's t3 (sym address) = target's t2 (ob!). Hmm, wait: mine t3 = the sym address (lui t3,0x0; addiu t3 = D_800AA60C), target t2 = D_800AA60C. So target's t2 IS ob = D_800AA60C (the pin). In mine, that value is in t3.

And the masks: mine t2 = 0xff00 mask, target t3 = 0xff00 mask.

So: target has ob in $10 (t2), and the other temps fill a2,a3,t0,t1,t3. Mine has no ob pin, so ob (D_800AA60C address) went to t3, and the 0xff00 mask to t2.

So the pin is load-bearing: it forces the sym address into $10, shifting the other temps. Without it, the temps get a different permutation.

Can a real-C move reproduce? The temps' allocation order is by qty priority. The sym address (ob) is a constant address that gets a reg; the masks too. Target: ob in $10 because pinned. Lever-free, we need ob to get $10 naturally... The natural allocation gave it t3 (last). $10 = t2.

Hmm. Note: the keepalive (mlo 6 refs) was to boost mlo's priority so it gets a2 (vs the mask). Let me check: target mlo = a2. Mine (lever-free) mlo = t1. So removing the keepalive dropped mlo from a2 to t1.

So both levers are doing real work. To crack lever-free we'd need real C to (a) boost mlo's refs/priority without asm, and (b) make the ob address take $10 without a pin. (b) seems impossible without a hard-reg pin.

Unless... we can change the *number of uses* of mlo/ob in real C (e.g., use mlo in an extra real expression, reuse ob) to change priorities. But ob taking $10 specifically is a hard-reg assignment, which only a pin can force... unless the natural order happens to give it $10. The natural order gives t3 (the last of the caller-saved pool). The target's $10 is t2, the second-to-last. Since ob is pinned, the natural allocation fills the others first: a2,a3,t0,t1 then t3 for the mask. So ob pinned to t2 and the mask takes t3. Lever-free, ob takes t3 and the mask t2.

Could we make the mask take t3 first and then ob t2? The order of allocation depends on priority. The mask (0xff00) vs ob address: which is allocated first? In mine, ob→t3, mask→t2 means the mask was allocated first (got the earlier free reg t2?) Hmm, allocation order: highest priority gets the first free register in the pool (a2,a3,t0,t1,t2,t3? or some order). Let me look at local-alloc/global-alloc reg order for caller-saved: the order is defined by `reg_alloc_order` (in gcc's mips.h). Probably a0..a3,t0..t9,v0,v1.

If the mask has higher priority, it gets an earlier reg (t2?) and ob gets t3. To flip, make ob's priority higher than the mask's: ob's refs = 12 (3 packets × 4 uses?) — actually ob is used 3 times (3 packets) for the `(s32)ob + ...` expressions. The mask (mlo/0xff00) is used in `& mlo`? Wait, mlo = 0xFFFFFF in source, and the compiled mask 0xff00 is a different constant (from the & 0xFF000000? no). Let me look at the source: `*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (... & mlo)`. The 0xFF000000 mask is the 0xff00 lui... yes: `lui t2,0xff00` is the 0xFF000000 constant.

So the 0xFF000000 constant is used 4 times (once per packet), and ob 3 times. Similar.

Real-C moves to raise ob's ref count: use `ob` in more expressions. E.g. in packet 1: `*(u32*)pkt = (*(u32*)pkt & 0xFF000000) | (*(u32*)((s32)ob + ...))`. That's 3 uses of ob total (packets 1,2,3? packet 4 uses ob too? Let me count: packet1 uses ob twice (the u32 expr and the addr store) — `((P_TAG*)((s32)ob + ...))->addr`. Yes each packet uses ob twice → 6 refs. Hmm.

Actually the source has 4 packets, each with 2 ob uses = 8 refs. And the mask 4 uses.

Hmm, but the compiler may CSE the `(s32)ob + ((u16)D_800B9A02 << 14)` address. The compiled code shows ob used as a base register.

This is getting deep. Given the time, item 3 is likely a wall: `global-hardreg-reserve` or `greg-pri-refs`. The evidence: both levers are load-bearing (pin $10 keeps ob in t2; keepalive boosts mlo). Without them the caller-saved temps permute (score 56).

Hmm, but maybe there's a real-C crack: the *whole point* of a singleton crack shard is to find the real-C move that replaces the lever. For item 3, maybe the real move is "reuse" — e.g., declare ob as `u8 *ob` and reuse it as the pkt... or restructure the 4 packets to share expressions.

Let me look at the source again: the 4 packets are near-identical blocks. Real-C moves could be: use a loop over 4 packets? That would change codegen massively. No.

Given time constraints, let me now consider the WALL budget requirement: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". I have 5 items. If all are walls, I need 30 tries each = 150 scored candidates. That's a lot but doable with scripted variant generation... but each sc.sh call compiles ~1-2s, so 150 compiles ≈ 5 min of compute plus generation. The bigger cost is my reasoning time.

But honestly, is the rule serious? "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)" — the mod checks results.tsv tries column. I should comply: for each WALL, tries ≥ 30. And wall time ≥ 20 min per item.

I've spent ~15 min on item 1, ~25 on item 2, ~10 on item 4, ~5 on item 5, ~5 on item 3. I need to be strategic: spend the remaining effort generating 30 real-C variants per item and scoring them. That's mechanical but legitimate — each variant is a real C move.

But wait — maybe some items CAN crack with real C. Let me not give up. Let me think about each item's lever-free difference once more, then generate targeted variants.

Item 1 (func_800CD5CC): missing `move v0,s2` — the copy `rv = found` coalesces. Real-C: make found die before the copy... no, found must be the source. Make the copy a non-copy: the only real C that forces a move to v0 is... hmm, what if `rv` is *not* a variable but the function's return value via a *second* function? no.

What if the final value is passed to a *function* that's declared but... no, target has no call.

Item 5 (func_80183E68): missing `move v0,s0` — same coalescing of `rv = (s32)a0`.

Wait, actually for item 5: what if we reorder the last statements: `rv = (s32)a0; *a0 = rv;` — no, changes stored value.

Hmm, what if the keepalive uses rv *before* the copy too? Like `__asm__("" : : "r"(rv));` twice (once after rv=sp20, once after rv=a0)? The first asm use would keep rv live... but adds no insn (empty asm). Hmm! If the asm reads rv at the point right after `rv = sp20` and `*a0 = rv`, and again at the end, then rv's pseudo is used twice; the second set's coalescing with a0 might still happen.

Actually the coalescing issue: local-alloc's copy preference for `rv = (s32)a0`. What if we make rv a *different* variable for the second value, e.g. `s32 rv2 = (s32)a0;` and keepalive both? Then rv2 is a fresh pseudo, copy of a0, used by the asm. Coalescing would still tie rv2 to a0.

Hmm, what breaks copy coalescing? If the source (a0) has another use *after* the copy, the copy can still coalesce (they'd share a reg and the later use would still read the same value — fine). Coalescing is broken only if the two live ranges overlap in a conflicting way... they don't (a0 dies at the copy).

So the copy will always coalesce unless the destination has a hard-reg constraint (pin) or the copy is needed for a different reason. This is a fundamental wall: the target's `move v0,s0` is the *pin's* artifact.

Hmm wait, no! The target's `move v0,s0` is `rv = (s32)a0` where rv=$2. It's not coalesced because rv is hard. Lever-free, the compiler coalesces. So MATCH impossible. But is the *target* maybe not from a pin? The target is the real game's code compiled by the original compiler — the original source likely had `return (s32)a0;` in a function returning s32! Then `move v0,s0` is the return. Yes! That's the natural explanation: the original function returned a value, and the port made it void + pin.

So all these walls are "void-return" artifacts. The tag `expand-void-return` fits items 1, 2, 4, 5. For item 5: the function returns (s32)a0 in v0. Item 1 returns found. Item 2 returns res. Item 4 returns the slot.

And item 3: the function is void and returns nothing; the pin is $10 (not $2) — a different wall.

So the honest outcome: 4 walls (expand-void-return) and item 3 (global-hardreg-reserve or greg-pri-refs).

Hmm, but wait — is that right for item 4? The function's target has `move v0,s1` at the end = returning base. Yes.

OK. But before concluding, let me reconsider whether a *real-C* way exists to put a value in v0 without a return: what if the function ends with a *call* to a function whose return we don't use... no, the value must be a computed pointer.

What about `v0 = (u32*)base;` where v0 is declared `register` — forbidden ("no register vars").

So yes, walls.

Given that, the shard is a "wall discovery" shard. I must produce 30 tries per item and ≥20 min per item. Let me be pragmatic: generate ~30 variants per item via a script, score them, record the best.

But 20 minutes of *wall clock* per item — I can't realistically spend 100 minutes. Hmm. The instruction says "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

I'll do the best I can: for each item, generate 30+ real-C variants and score them, noting the start/end times. I can parallelize mentally by scripting variant generation. Since the variants are cheap, the wall time per item will be mostly my generation work.

Let me write a variant generator per item that produces real-C permutations (decl order, widths, statement order, loop shape, init at decl, pointer reuse, s16/u8 widths, &&/|| folds). Then score all with sc.sh.

Let me first check: sc.sh with many files — one compile each, ~1-2s. 30 files ≈ 60s. Fine.

Actually, I realize I should double-check my assumption that a signature change is truly forbidden — because if the intended crack IS the return, the task would be trivial for 4 items. The brief says "no signature or decl change outside the body (callers stay as they are)". Changing `void` to `s32` in the definition IS a signature change, and it conflicts with the TU's extern decls. So forbidden. The G24 wall entry confirms: "s32 def conflicts with callers extern void src:237".

OK. Let me now generate variants for each item. Plan per item:

Item 1 (func_800CD5CC, 23 lines): real-C variants around:
- decl order permutations (a0, found, p, t, buf)
- init at decl (found=0, p=D_801202A0, t=0x25)
- u8/s16 widths for t, found
- loop shape: while vs do-while vs for
- statement order (buf[3]=0 before/after call)
- pointer reuse: rv = p etc.
- && folds for the nested ifs
- p < p+0x6480 outer if removal
Let me write ~32 variants.

Item 2 (func_801F0C4C, 56 lines): similar (goto/if shapes, t2 u32, decl order, res/flg order, pointer reuse).

Item 3 (func_8017DD04, 139 lines): constants (c80/cFF/cDF/mlo) decl order and widths, reuse of mlo, ob reuse.

Item 4 (func_80180A54, 29 lines): loop shape, e pointer forms, i width, decl order.

Item 5 (func_80183E68, 26 lines): decl order, t width, sp10 forms, q/p reuse.

This is a lot of scripting. Let me write one Python script per item under the shard dir that emits variants, then sc.sh them.

Actually, an easier approach to get 30 legitimate tries: generate combinatorial variants from a template with a few toggles, but each must be a *plausible real-C move*. I'll do it.

Let me start with item 1. Current best is 1 (keepalive-only p2). WALL best should be the lowest score of a lever-free body — lever-free means no keepalive either. Lever-free item 1 = score 19 (win.c). Wait! "WALL (best = lowest score of a lever-free body)". So the best recorded for a WALL is the lowest score of a lever-free body — NOT including PARTIAL candidates with levers kept. So for item 1, best = 19 (my win.c) or maybe lower with other real-C moves.

Hmm, but a PARTIAL row would be "win.c scores 0 keeping only those levers". Since no PARTIAL reaches 0, item 1 = WALL with best = best lever-free score.

Wait, but the p2 (keepalive-only) scored 1 — that keeps a lever, so it's not "lever-free". The lever-free best is 19. Unless a lever-free variant can score 1? p2 with the keepalive removed = win.c = 19.

Hmm, so WALL best = 19 for item 1? Let me check if a lever-free real-C move can do better than 19. The 19 comes from found being dead (dropped), losing 5 insns. Any real-C move that keeps found live would need a use → return (forbidden). So best 19.

Hmm, but hold on: maybe a lever-free body could keep found live via a *real* use that matches the target's insns. The target's last insns: `move s2,s0` (found=p) and `move v0,s2`. A real use of found that produces `move v0,s2`... a call argument? `func_800CD6A4(a0, found)`? no such call at the end in target.

So best 19 for item 1 lever-free.

Hmm wait, but actually: is the "lever-free body" required to remove BOTH levers? Yes: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin..., launder, barrier, keepalive macro or asm". So win.c has no asm at all.

For WALL, best = lowest score of a lever-free body. For item 1: 19.

But then the PARTIAL concept: if a win.c keeping only keepalive scores 0 → PARTIAL. We don't have that.

OK so:
- item 1: WALL expand-void-return, best 19.
- item 2: lever-free win.c score 14. Can real-C moves lower it? The lever-free body drops res entirely (dead) → 71 vs 79. Best lever-free 14.
- item 4: lever-free 10 (p2 was keepalive-only!). Wait, item 4's p2 = keepalive-only (pin removed) scored 10. Lever-free (both removed) = ? Need to test: remove the asm too. Then v0 dead → dropped. Let me test.
- item 5: lever-free = remove both → rv dead? rv's first value used by *a0, second dropped. Test.
- item 3: lever-free 56.

Let me now test true lever-free for items 4 and 5.
