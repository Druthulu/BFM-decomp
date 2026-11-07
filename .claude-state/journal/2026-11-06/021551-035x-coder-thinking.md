---
ts: 2026-11-06T09:15:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JPy8pdmWtD3XUpI0btV5
---
In w1 mine, the andi writes t0 (in place, destroying bVar1) and is scheduled early (65), and then `subu v0,v0,v1` uses v0/v1 swapped. Target: andi v0,t0,0x10 right before beqz, and subu v1,v0,v1.

So the keepalive forces bVar1 to remain live in t0 through the division computation; thus the andi must produce a new reg (v0), and scheduling places it at its use (69) rather than early (65). Real-C: make bVar1 used after the &0x10 test.

Real use: the next code is `fc = *(s16 *)(param_1 + 0xc);` and the if/else. bVar1 is not used there. But the original source could be restructured: e.g., combine the two bVar1 tests into a single computed value used later? Hmm.

What if we keep `bVar1` live by using it in the second bVar1 test after the 0xa computation — i.e., move the `if ((bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0)` block after the 0xa block? That changes codegen order of the stores for +8 and +0xa. Target order: store +8 twice (with &8, &0x60/&0x80 tests) then +0xa. So no.

Alternative: make the &0x10 test consume a *computed* value of bVar1 that is used again later? But bVar1 isn't used later in the source.

Hmm. Wait: maybe we can change the *spelling* so bVar1's pinned register isn't clobberable: e.g., use `bVar1` (the variable) in the condition, which is what it does. The problem is bVar1 is dead after line 39 (the &0x60 test). Actually wait: line 39-40 uses bVar1 (&0x60, &0x80) — that's the last real use before line 44 (&0x10). So after the &0x60/&0x80 test, bVar1 is dead; the &0x10 test at line 44 reloads bVar1? bVar1 is a register var (pinned t0); the compiler keeps it in t0; the andi at 44 reuses it. In target, andi goes to v0 because... hmm, target at 69 does `andi v0,t0,0x10`, so bVar1 IS in t0 at that point. So in target bVar1 is live in t0 until the &0x10 test and the andi result goes to v0 (a fresh pseudo), not overwriting t0.

Why does the compiler choose v0 vs in-place? If bVar1's pseudo is dead after the andi, cse/combine can substitute t0 with the andi destination (combine: `(and (reg t0) 0x10)` -> dest t0 allowed since t0 dies). With the keepalive, t0 doesn't die, so a new reg v0.

Real-C way to keep bVar1's pseudo live past the andi: use bVar1 after line 44 in real code. Is there any later code where bVar1 could legitimately be used? Looking at the source: after the &0x10 test, `fc = ...` and the call `func_8013AA24(iVar11, param_1)`. No bVar1 use.

But hold on: the *outer* code after the inner block: `} else { ... }` uses nothing of bVar1. Hmm.

Could we restructure so that the &0x10 test is done earlier/later differently? E.g., compute `u8 f10 = bVar1 & 0x10` at the top and use it later — that introduces a temp but the target's andi is at 69. Actually if we write `if ((bVar1 & 0x10) != 0)` where bVar1 is a *u8 register var*... 

Alternative: change the &0x60/&0x80 test to keep bVar1 live: the condition `(bVar1 & 0x60) == 0 || (bVar1 & 0x80) != 0`. Target uses `andi v0,t0,0x10` after. If we instead write the second test as `(bVar1 & 0xE0) ...`? No, semantics differ.

Hmm. What about making the &0x10 test use a copy: `u8 t = bVar1; if ((t & 0x10) != 0) ...`? Then t is a new pseudo, and bVar1 stays live? No, bVar1 would still be dead after the copy; the copy would be a move. Target has no extra move.

Wait, maybe better: the pinned register bVar1 is $8. The keepalive `__asm__("" :: "r"(bVar1))` says bVar1 is used (read) at that point. Real C: use bVar1 in the store value? E.g. `*(s16 *)(param_1 + 8) = -sVar5;` — no.

Let me reconsider: perhaps a different real-C restructuring produces the same insns without needing bVar1 live: e.g., make the &0x10 test part of a larger expression so combine doesn't fold it in place. In target, andi dest v0, then beqz v0. That's exactly what you get if the value is used twice (cse can't clobber) or if the reg is not dead. If the test value were needed elsewhere... 

Idea: `if ((bVar1 & 0x10) != 0) { ... }` — what if we write it as `u32 m = bVar1 & 0x10; if (m) ...`? That's a temp used once — combine will merge it back.

What if the &0x10 test is moved *before* the &0x60 test? Then bVar1 live? No.

Alternative approach: instead of keeping bVar1 live, cause the andi result to be in a fresh pseudo because bVar1 is read *after* the andi by real code. Since no such code exists semantically, maybe use a reordering where the &0x10 test happens *before* the &0x60/&0x80 test? Then bVar1 is used after the &0x10 andi (by the &0x60 test), so the andi cannot write t0. And the &0x10 test applies to param_1+0xa (the second sVar5), while &0x60 applies to +8. Reordering would swap the instruction order of the two store groups — but maybe the target order actually has the &0x10 andi after the &0x60 test... yes target: 65-73 shows the 0x2a computation, andi v0,t0,0x10 at 69, then the +0xa stores; before that at 55-57 the +8 stores. So target order is source order.

Hmm, so reordering breaks order.

Wait — actually look again at target: the andi v0,t0,0x10 at 69 is *after* the division computation (mult/mfhi), i.e. scheduled late. If bVar1 were used after, the andi couldn't write t0. But how would real C keep bVar1 live past line 44? 

Maybe the answer: bVar1 is used in the *second* sVar5 computation! Line 42: `sVar5 = (short)((int)((int)*(s16 *)(iVar11 + 0x2a) * (uVar2b & 0xffff)) / 0x2a);` — no bVar1.

Alternatively, the pinned register var bVar1 might be kept live by the *pin itself* in some other way. Hmm, the register-asm pin (register u8 bVar1 __asm__("$8")) — in GCC 2.7.2, a register variable is a local reg; it has its own pseudo. The `__asm__("" :: "r"(bVar1))` marks it used at that point. If we remove the asm, the last use is the &0x10 test, and the pseudo dies there.

Real C that uses bVar1 after the &0x10 test without changing behavior: e.g., rewrite the &0x10 condition to be evaluated lazily later... Or compute the +0xa negation as a select using bVar1 twice:

```
if ((bVar1 & 0x10) != 0) {
    *(s16 *)(param_1 + 0xa) = -sVar5;
}
```
What if instead:
```
*(s16 *)(param_1 + 0xa) = (bVar1 & 0x10) ? -sVar5 : sVar5;
```
Then bVar1 is used in the condition; still one use.

What about: `if ((bVar1 & 0x10) != 0) { *(s16 *)(param_1 + 0xa) = -sVar5; }` — no.

Hmm, maybe keep bVar1 live via the *later* block: the else branch (uVar2 == 1) doesn't use bVar1. But what about the outer `if (uVar2 != 1) { if (sVar2 != 0 && sVar2 < 7) { ... } }` — bVar1 loaded before. After the inner block, function returns. No.

Alternative: since we can move statements, move the `bVar1 = *(u8 *)(iVar11 + 0x22);` load later? The load is at line 17 before the `if (uVar2 != 0 && uVar2 < 7)`. Target has it loaded early (need to check). If we moved the bVar1 load to just before its first use, the register pressure changes... but the target loads it early at line 17? Let me look at the insn listing from the start.

Actually maybe simpler: the whole issue is the &0x10 andi being combined into t0. If we make the &0x10 test's operand not bVar1 but a *new variable assigned from bVar1 at a point where bVar1 is still live later*... no.

Let me think about what real C code would naturally keep bVar1 live: a use of bVar1 in the fc branch. The fc branch:
```
fc = *(s16 *)(param_1 + 0xc);
iVar7 = fc + zr;   // zr pinned $0
if (fc < *(s16 *)(param_1 + 0xe)) { ... } else if (...) { ... }
__asm__("" :: "r"(fc));
func_8013AA24(iVar11, param_1);
```
The keepalive for fc forces fc live to the call. Why? fc is used in the conditions; after the if/else, fc is dead. The keepalive keeps it live to the call, so local-alloc/global-alloc assigns it a callee-saved or keeps it in a register across... target insns show a1/a0/v1/v0 usage. Let me see what fc's keepalive does: w3 diff.

Let me look at w3's insns.

Actually let me step back and consider the approach for all three keepalives: they were added in Phase 36 "NEEDED DIFFERS" and the original body before keepalives presumably scored >0. The task is to find real C. This could be hard; each item has a 20-30 min budget and may end WALL. Three items; total maybe 60-90 min. Let's work efficiently.

Let me get the full instruction listing of the target function to understand register roles. Print 0-204 for target with orig. Then reason.

Let me print all target insns (mine==target for orig).
