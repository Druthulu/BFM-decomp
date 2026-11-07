---
ts: 2026-11-06T21:24:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KPNeVgM0iUbrAHKn2i2L
---
p_only: mine uses s0 where target uses s2, and s2 where target uses s0. So the pin $18 (s2) forces `base` into s2, and without the pin, base goes to s0. The target has base in s2 (due to pin) and buf/tp in s0.

So removing the pin shifts base from s2 to s0. To crack the pin with real C: we need `base` to get s2 (callee-saved $18). Why s2? Because it's live across calls and gets a callee-saved reg. Without the pin, it gets s0. To make it s2, we'd need the allocator to pick s2. That's a callee-saved order issue.

Hmm. And the launders (with pin removed) keep the count at 206. So if I could fix the base→s2 assignment, p_only would be 0? No, p_only still has the launders (row kinds). I need them gone.

So two problems:
1. base must land in s2 without the pin.
2. tp must stay in s0 without the launder (and ap must rematerialize).

Given the p_only diff shows the whole function is a s0↔s2 swap, maybe there's a real-C way to make base prefer s2. E.g., declaration order of locals, or the order of first use.

Actually, wait. Let me reconsider. Maybe with the launders removed AND the pin removed, the register assignment could naturally match if I restructure. The f1 result (212 ins) had s0/s2 swapped too plus tp rematerialization.

This is a hard 2-lever item. Given the WALL threshold (≥20 min, ≥30 tries), I need to either crack it or put in the effort.

Let me try a promising approach for the tp launder: since target keeps tp in a reg, and the known crack for "keep const addr in reg" is raising refs via a real 2nd set. For a pointer, the "v = (s16)v" trick: declare tp as `s16 tp`? No, it's an address.

What if tp is declared as `void *tp` and we do `tp = (void *)((u32)tp & 0xFFFFFFFF);`? folded.

Hmm, what about `tp = (s32)D_801274F0_8017CF48; ... tp = tp + (buf[0] & 0);` — buf[0] is runtime but &0 folds.

What about `tp = (s32)D_801274F0_8017CF48;` then `tp = (s32)((u8*)tp);`? no-op.

OK here's a thought: the v-cast trick works because it's a *subreg* truncation that combine doesn't remove (it changes the mode). For tp (s32 address), a truncation would lose bits. But what if we cast to `u16` and back with the low bits preserved? The address D_801274F0 is 0x801274F0; truncating to 16 bits gives 0x74F0, wrong.

Alternatively, cast the pointer to a `s16*` and back: `tp = (s32)(s16 *)tp;` — pointer-to-pointer, same mode, no-op. Might be dropped.

What about `tp = (s32)(u32)tp;` — same.

Hmm. Let me try the "real 2nd set" where the second set is a genuine store: the code does `*(Blk8*)tp = *(Blk8*)buf;`. What if we write it as a pointer increment chain: 
```
tp = (s32)D_801274F0...;
*(Blk8*)tp = *(Blk8*)buf;
```
No.

Let me look at the target.s to understand exactly what tp is and how many uses. Maybe tp is kept in s0 because of the final call `func_8017D280(a0, (s16*)(tp-8))` where tp-8 is an argument — that requires tp in a reg at that point. And the store base. 

Actually, maybe the crack is to compute `tp` once and pass `tp - 8` as a computed pointer used throughout:
```
u8 *tp = (u8*)D_801274F0...;
u8 *tp8 = tp - 8;
*(Blk8*)tp = *(Blk8*)buf;
t0 = func(*(s16*)tp8, buf[0], 4, 1);
...
```
That introduces tp8 = tp-8 (addiu), which target doesn't have (target uses displacements -8/-6/-4). So no.

Let me try a completely different angle: maybe I should NOT remove the pin/launders by rewriting, but find that the function has a twin that was already cracked. Let me check if there's a twin in the codebase (same shape). grep src for D_801274F0 and similar.

Actually, the moves log line 191 gives the exact trick for launders on a *sign-extended s16*: `v = (s16)v;`. Our ap and tp are pointers/addresses, not s16.

Let me step back and consider time. I've spent ~18 min on item 3. To record a WALL I need ≥20 min and ≥30 tries. I have ~10 tries. I could spend 10 more minutes doing 20 quick variants to meet the threshold, or genuinely try to crack.

Let me think about the tp launder differently: the launder is `__asm__("" : "=r"(tp) : "0"(tp))`. It forces tp to be *materialized* (a real def) and tied. In RTL terms, it's `(set (reg tp) (reg tp))` via asm. This is a copy. The real-C equivalent of a self-copy that survives: `tp = tp;`? Flow removes self-copies? Let me test `tp = tp;` — maybe combine/flow keeps it as a 2nd set! Actually, a self-assignment `tp = tp` is typically optimized away by the front-end or cse. But let me test.

Also `tp = (s32)tp;` and `ap = (void*)ap;`.

Let me test these cheaply. If `tp = tp;` survives as a 2nd set (reg_n_sets=2), it might prevent rematerialization.

Let me build f4: f1 + `tp = tp;` after the assignment. And f5: `tp = (s32)tp;`.

Actually, the identity cast is explicitly prohibited as a launder: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". So `tp = tp` / `tp = (s32)tp` is an identity launder — NOT a crack. So even if it scores 0, it's disallowed. Good to know.

So I can't use identity tricks. I need a real 2nd set.

Hmm. For tp, is there a real operation? The code uses tp as an address and does `tp-8`, `tp-6`, `tp-4`. What if I compute `tp = (s32)D_801274F0_8017CF48;` and then use `tp` in the store and reloads. There's no real arithmetic to split.

What about the `ap` launders? Target rematerializes buf (addiu sp,16). The crack per line 198 is a dead-reset `ap = 0;` after each call. But target uses `addiu a0,sp,16` inline, which is rematerialization — so a dead-reset would produce that! Wait, let me re-read: "DEAD-RESET CSE-BREAKER: pb=&buf; call(pb); pb=0; ... cse's &buf address class breaks, so all 6 sites rematerialise addiu aN,sp,56 and no callee-saved reg parks the address".

So for the ap launder, replace with: `ap = buf;` use it; then `ap = 0;` after, so the next site rematerializes. That's a real move (dead reset) and could reproduce target's inline addiu.

So the ap launder → dead-reset crack is promising! Let me apply:
```
ap = buf;
func_8017D418((s16*)ap, (s16*)base);   // but if ap=0 after, the first call...
```
Actually target's first call uses `addiu a0,sp,16` = ap inline. So maybe:
```
ap = buf;
if (func_8017D418((s16*)ap, (s16*)base)) goto L164;
ap = 0;
...
ap = buf;
if (func_8017D418((s16*)ap, (s16*)base)) goto L164;
ap = 0;
```
Hmm, but the dead-reset must be placed so cse breaks the class. Let me look at the original structure: `ap = buf; asm(ap); base=...; call1; ...7 calls...; ap = buf; asm(ap); base+=0x80; call; goto`. The two ap launders are at the start of each base segment. The dead-reset version: after the first call? The moves say "pb=&buf; call(pb); pb=0;" before every site. So:
```
ap = buf; call1(ap); ap = 0;
...
ap = buf; call(ap); ap = 0;
```

But the target's calls all use `addiu a0,sp,16` (buf) directly for the FIRST argument, so ap isn't kept in a reg. A dead-reset after the call would break the class so the address rematerializes for the next use. But the next uses are `buf` directly (not ap) for calls 2-8. Hmm.

Wait, target's calls 2-8 pass `buf` as a0? Let me re-read the source: calls are `func_8017D418(buf, (s16*)(base+0x10))`, etc. — they use `buf` directly. Only call 1 uses `ap`. So why does the target rematerialize `addiu a0,sp,16` for calls 2-8 instead of keeping buf in a reg? Because cse broke the class (the launder/dead-reset). 

So the dead-reset on `ap` (or buf) would break the &buf class, making all `buf` address uses rematerialize `addiu sp,16`. 

Actually, the target shows `addiu a0,sp,16` for the buf argument at each call. Without the launder, mine hoists `addiu s0,sp,16` once. So a dead-reset that breaks the class is exactly the crack.

But where to put the dead-reset? The cse class for &buf. `ap = buf; ap = 0;` would break the &buf class if ap and buf share the class. Actually `ap = buf` creates REG_EQUAL/REG_EQUIV linking ap to &buf. Then `ap = 0` kills ap's class. Hmm.

The moves example: "pb=&buf; call(pb); pb=0; before every site". So:
```
ap = buf;
call1(ap);
ap = 0;
```
Let me try applying this to the two ap sites. And for tp, maybe a similar dead-reset? But target KEEPS tp in a reg, so no.

Let me focus: apply dead-resets for ap (2 sites), keep tp launder? No, must remove tp launder too.

Ugh, tp is the blocker.

Let me reconsider tp: target keeps tp in s0. Without launder, rematerialized. Is there a real 2nd set? What if `tp` is used in a real pointer arithmetic that's needed: the final call passes `(s16 *)(tp - 8)`. What if we compute `tp8 = (s16 *)(tp - 8);` and pass tp8, and use tp8[0], tp8[1], tp8[2] for the loads/stores? Then tp8 = tp-8 is a real addiu, and the loads use displacements 0,2,4 from tp8. That changes the code (target uses -8/-6/-4 from tp). But maybe the register allocation then keeps tp8 in a reg naturally, producing `lh a0,0(s0)` instead of `lh a0,-8(s0)` — different encoding (offset 0 vs -8) but same instruction count! The target has offset -8. So no.

What if we keep tp but add `tp = tp - 8;`? Then uses become tp[0], tp[2], tp[4]... offsets 0,2,4 vs target -8,-6,-4. Different.

Hmm.

OK, let me look at the actual target.s for the tp region to be sure.

Actually, let me reconsider: maybe with the ap dead-resets, the register pressure changes and tp naturally gets a callee-saved reg (because the buf address no longer parks in s0). That could fix BOTH! Because the ap launder's removal frees up s0, which tp can then take. That's plausible: the extra instructions in l_only were because s0 was used for buf, leaving no reg for tp. If the dead-reset makes buf rematerialize (no s0), then tp can take s0.

Wait, but in l_only (launders simply removed), mine used s0 for buf and rematerialized tp. If I add dead-resets to break the buf class, buf rematerializes and s0 frees up → tp could go to s0!

Let me test this. Build f6:
- pin removed (base plain)
- ap sites: dead-reset pattern
- tp launder removed, no replacement (rely on freed reg)

Structure for ap:
```
L00C:
    ap = buf;
    base = (s32)&D_80185FF0;
    if (func_8017D418((s16 *)ap, (s16 *)base)) goto L164;
    ap = 0;
    if (func_8017D418(buf, ...)) ...
```
Hmm, but the dead-reset should be after the call that uses ap. Let me put `ap = 0;` right after the first call. Then the subsequent `buf` uses rematerialize.

Second ap site:
```
    ap = buf;
    base = base + 0x80;
    if (func_8017D418((s16 *)ap, (s16 *)base)) goto L164;
    ap = 0;
    goto L174;
```
Wait, but the target's second segment call uses `addiu a0,sp,16` too. Let me just try.

Actually, the dead-reset might be better placed BEFORE the ap assignment to break the previous class. Let me follow the moves example literally: "pb=&buf; call(pb); pb=0; before every site". So the reset is after the call, and the assignment before the next site.

Let me build f6 and score.

Also, I realize the first call `func_8017D418((s16*)ap, (s16*)base)` — with ap=buf. Then `ap=0`. The other calls use `buf` directly. The cse class for &buf: `ap=buf` makes ap equal &buf; `ap=0` sets ap to 0, which doesn't necessarily kill the &buf class (buf is still sp+16). Hmm. But in the moves example, pb=&buf; pb=0 — the reset is on pb, and the class is the address. Maybe cse treats `pb=0` as a store to pb which... Actually the dead reset breaks the REG_EQUAL for pb, but buf itself is still &buf.

Hmm, but the target rematerializes &buf at each call even though `buf` is a local array whose address is constant. Why? Because the compiler would normally hoist it. The dead-reset on ap apparently breaks it. Let me just test empirically.

Let me build f6.
