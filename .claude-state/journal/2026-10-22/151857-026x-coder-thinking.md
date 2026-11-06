---
ts: 2026-10-22T21:18:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MSkKiErcHGVdNFGyP1uZ
---
Target item2 (34 insns):
```
0  addiu sp,sp,-48
1  sw s0,40(sp)
2  move s0,a1
3  sw ra,44(sp)
4  lhu v0,2(s0)
5  nop
6  sh v0,16(sp)
7  lhu v0,6(s0)
8  nop
9  sh v0,18(sp)
10 lhu v0,10(s0)
11 addiu a1,sp,16
12 sh v0,20(sp)
13 lw a0,32(a0)
14 addiu a2,sp,32
15 jal func_8012F14C
16 addiu a0,a0,52
17 addiu a0,sp,32        <- m2 rematerialised (mid at sp+32)
18 jal func_8012EFB8
19 addiu a1,sp,24
20 lhu v0,24(sp)         <- out.f0 loaded from sp+24
21 nop
22 sh v0,2(s0)
23 lhu v0,26(sp)
24 nop
25 sh v0,6(s0)
26 lhu v0,28(sp)
27 nop
28 sh v0,10(s0)
29 lw ra,44(sp)
30 lw s0,40(sp)
31 addiu sp,sp,48
32 jr ra
33 nop
```

Mine (lever-free) 33 insns: has s1 (extra save/restore) and does the out stores as: lhu v0,26(sp)... Actually mine:
```
3d80 lhu v0,2(s0); nop; sh v0,16(sp)
3d8c lhu v0,6(s0); nop; sh v0,18(sp)
3d98 lhu v0,10(s0)
3d9c addiu a1,sp,16
3da0 sh v0,20(sp)
3da4 lw a0,32(a0)
3da8 addiu a2,sp,32
3dac jal
3db0 addiu a0,a0,52
3db4 move a0,s1     <- mid held in s1
3db8 jal
3dbc addiu a1,sp,24
3dc0 lhu v0,26(sp)  <- first store is out.f2 to 6(s0)! out.f0 store missing
3dc4 nop
3dc8 sh v0,6(s0)
3dcc lhu v0,28(sp)
3dd0 nop
3dd4 sh v0,10(s0)
```
Wait, mine stores to 6(s0) and 10(s0) but where's 2(s0)? And the target has three stores starting at 24(sp). Mine only 2 stores visible plus... hold on, mine at 3dc0 reads 26(sp) then 28(sp) — only two. And the missing `sh v0,2(s0)`? The diff said "insert mine[21:21] target[20:23]: lhu v0,24(sp); nop; sh v0,2(s0)". So mine lacks the out.f0 store entirely?! That's a bug? No wait — maybe mine stored out.f0 earlier. Look at mine 3d80-3da0: those are the `in` loads/stores. Hmm.

Actually wait, mine's `move a0,s1` where s1 never set — this smells like the objdump of cand.o where s1 was set but got... Let me recount mine's asm. There are 33 instructions. Actually maybe the `sh v0,2(s0)` exists but out of order, and the diff aligns differently. The diff only showed regions. Let me just diff mine vs tgt directly with structured_diff to see full picture.

Hmm, but the `move a0,s1` with no set of s1 is a red flag. Possibly the candidate object I disassembled was for a different TU... it's ov_MAIN_012 which is the primary. Hmm, but the body I compiled was nopin.c, and the in-place write to the header... could there be a race? Whatever.

Wait — actually maybe the issue: `move a0,s1` at 3db4 is the delay slot of the jal at 3db8? No, jal is at 3db8, so 3db4 executes before. Hmm, but actually delay slots: the instruction after jal (3dbc addiu a1,sp,24) is the delay slot.

Hold on. Maybe s1 IS set: at 3da8 `addiu a2,sp,32` — what if the register is s1 and the disassembly named it a2 because... no.

Let me recheck by disassembling again, maybe I truncated. Let me look at the raw words. Alternatively use a different approach: I'll write candidates and score them; the score tells.

Key difference to fix: m1/m2/mtx launders. In the target, `mid` (sp+32) is used for both calls: a2 = sp+32 for call 1, a0 = sp+32 for call 2, both rematerialised. In the lever-free body, the compiler holds mid in a callee-saved register (s1) across the first call, which costs frame +2 insns... but wait, it should be rematerialisable (sp+32 is a constant). The reason the launder mattered: it broke the cse equivalence so the two address computations weren't shared, hence... hmm.

Actually in the launder-free body: `m1 = mid;` then call(mtx+0x34, pin, m1); then `m2 = mid;` call(m2, &out). Since m1 and m2 both equal &mid (same cse value), and m1 is live across the call, the register allocator keeps &mid in s1 across the call. But the target computes addiu a2,sp,32 before the first call and addiu a0,sp,32 before the second call — i.e., it recomputes. That's the rematerialization the launder caused (the launder made m1 a hard-reg pseudo so cse's equivalence between m1 and m2 broke, and reload rematerialized).

So lever-free: I need m2 = &mid not to be cse-equivalent to m1. Options from the moves catalog: a real second set, pointer reuse, or use different expressions. Ideas:
- Declare mid as a struct/array and use different spellings? cse would still equate.
- `m2 = (s32 *)((char *)mid + 0)`? Identity spelling — not allowed (identity-statement launders don't count).
- Make m2 derived from a different expression: e.g. `m2 = &mid[0];` — cse equates.
- Use `m2 = mid;` where mid is not a local array but obtained differently, e.g. pass `&mid[0]` and `mid`... same.

Hmm. But wait — what about the real fix: the target uses `addiu a0,sp,32` right before the second call, i.e., m2's value is computed at the second call (a fresh addiu), not held. And it also doesn't hold `pin`... pin = &in = sp+16, used as a1: target `addiu a1,sp,16` — one use only, computed. Fine.

So target: no value crosses the first call in a callee-saved reg except mtx? mtx = *(s32*)(param_1+0x20) loaded into a0 at 13 then addiu a0,a0,52 in the delay slot. So actually the target has NO callee-saved reg except s0 (the p2 arg). Frame 48.

So the lever-free body must avoid keeping &mid live across the call. How? If m1's value (a2=sp+32) is dead after the first call (i.e., the compiler doesn't reuse it), and m2's value is computed fresh before call 2, then no cross-call live value. The problem is cse equates m1 and m2 → the address pseudo is live from before call 1 to call 2 → held in s1.

Wait, but if cse equates them, the value is still needed for call 2 and it's a rematerialisable constant... the allocator chose to hold it. To break the equivalence in plain C, use different values that happen to be the same address:
- `m1 = mid;` (s32*), and `m2 = (s32*)((char*)mid + 0)` → identity, not allowed.
- Make m2 point to a different but equal-address location: e.g. `m2 = &mid[0];` vs `m1 = mid + 0;`? cse sees through.
- Real C moves per C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse.

Idea: use a separate variable for the second call's pointer that is derived from a different base: e.g., since mid is `s32 mid[2]` at sp+32 and out is Vec3 at sp+24... hmm.

Alternative: kill cse by giving m1 a different offset. What if I reorder the declarations so mid/out have different stack offsets? The target offsets: in at 16, out at 24, mid at 32. My decl order: Vec3 in; Vec3 out; s32 mid[2]; → sp+16, sp+24, sp+32. Good, same.

So the only issue is the address live across call. What if I don't use a temp variable at all for the second call: `((void (*)(s32*, Vec3*))func_8012EFB8)(mid, &out);` — then mid's address is computed directly at the call site, and m1 for call 1 also computed at call site. cse would still equate both address expressions (same REG_EQUAL) and might still keep it... but with two uses at two call sites, cse would keep one value in a pseudo → same problem? Let's just test.

Let me test several variants:
a2: m1/m2 temps removed, pass mid directly in both calls.
a3: pass mid directly in second call only.
a4: keep temps but drop the mtx launder only (to see the mtx effect).

Let me do it.
