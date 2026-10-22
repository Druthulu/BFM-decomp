---
ts: 2026-10-21T23:44:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_9Gvnf1nnbNfs788hG4Vh
---
No ROM asm there. Let me find the ROM .s: maybe in .run/P36 or a "splat" dir. Search for files named *.s containing "func_8014C308" gave only scratch files in .run (probe files). Let me look at .run/uc3/splice_fix.s — scratch from another agent.

Alternatively, the psyq directory in the baseline: .run/P36/delever/baseline/psyq — maybe the ROM's disassembly! Let me check.

Actually, simpler: I can get the full ROM function bytes by using the masked_diff tool with the baseline object and my candidate object... but the tool's --try already prints the target insns.

You know what? The target instruction list I have IS the ROM function's instruction list as the scorer sees it (39 ins). The only confusion is the tail. Let me test the hypothesis "ins 37 = jr $ra, ins 38 = nop" by checking my own compiled candidate: score of a candidate that matches except for the tail... 

Alternative: let me look at what my nopin candidate produced at the tail: the diff showed "replace mine[36:37] target[34:35]: 36 j 6ac4 | j 6abc" and mine[31:33] deleted (j, li v0,1), plus mine 41 vs target 39.

My nopin compiled (41 ins) ends: ..., mine[36] `j 6ac4`, then equal region mine[37:40] == target[35:38].

OK here's a cleaner way to see the full picture: use `--try` with a candidate that is byte-identical to the pinned body except one instruction — then the diff shows exactly the neighborhood. E.g. take orig.c and change `v0 = 1;` to `v0 = 2;` → diff shows mine vs target around that point, revealing the tail structure of both. Meh.

Actually, the most useful thing: the ROM asm's exact bytes are what my compiled body must match, and the scorer tells me the score. I don't need to fully understand the semantics; I need to find a C that reproduces it.

So let me focus on the practical crack.

Observation from the diff (nopin vs target):
- Mine: const-chain temp in $2 (v0), the "1" value in $3 (v1). Target: "1" in $2, const chain in $3.
- Mine has 2 extra instructions: `j` + `li v0,1` (mine[31:33]) — because in mine, the "return 1" path needed a jump+li, whereas the target has a single `li v0,1` at ins 23 and branches to a shared block.

Hmm wait, that's interesting: mine[31] `j 6ac4` and mine[32] `li v0,1` — so in mine, the "return 1" is `j <block>` + delay slot `li v0,1`. In the target, the "li v0,1" is at ins 23 (in the middle of the chain) and branches to a shared block go directly.

The target's structure suggests: the "1" is set once (ins 23) and the four `beq` at 25,27,29 branch to the shared return block; and the branch at 22 (arg2==9) also branches there — with v0 = 0 (bug or deliberate). 

Hmm, but that means the target's semantics = "return 1 only for 17,41,10" — while the C says return 1 for 9 too. But the C compiles to the same bytes, so the C's `if (arg2 == v1) return v0;` with v1=9 must ALSO return 0 in the compiled code... meaning gcc's compiled version has v0 = 0 at that branch. How? Because gcc's `v0 = 1` assignment was sunk after the first compare (the li v0,1 at ins 23)! And the branch at 22 targets the shared return where v0 = the `and` result = 0.

So the ROM's behavior: arg2==9 → return 0 (v0=0). GCC's C reproduces this because the assignment `v0 = 1` is sunk to after the first compare (sched1 sinking) — a known gcc quirk: since the branch at 22 leads to a block where v0's value is used (return v0), gcc must ensure v0=1 there... unless the branch at 22 doesn't go to the shared return but to a different block. 

Ugh. Whatever: gcc produced it, my job is to reproduce the same bytes without the pin.

So the crux: without the pin, gcc puts the const-chain in $2 and the "1" in $3. With the pin (v0 → $2), gcc puts "1" in $2 and const chain in $3. Interesting: the pin forces v0 into $2, and then the const temp takes $3.

Without the pin, local-alloc chose: const temp → $2, "1"-value → $3. To flip, I need the "1" pseudo to have higher priority than the const temp.

The const temp (v1 in C) is set 4 times (9,17,41,10) and used 4 times → 8 refs, live across the whole chain. The "1" pseudo: 1 set + 5 uses (returns) → 6 refs.

Options to flip the priority:
(a) Reduce the const temp's refs: inline the constants (`if (arg2 == 9) return v0;` etc.) → then each constant gets its own pseudo with 1 set + 1 use; but they'd be 4 pseudos instead of 1. The compiler would then need registers for each; likely all in $3 (or different). Hmm, and "the 1" pseudo would then get $2. Worth trying!

(b) Increase the "1" pseudo's refs: e.g. `v0 = 1;` used in more places (the 5 returns). Can't easily increase.

(c) Use `v0` in a way that makes it live longer / higher qty.

(d) Change widths: e.g. declare the const temp as s16 → HImode copies might change allocation. Or the "1" var as u16/s16.

(e) Statement order: move `v0 = 1;` after the first compare (i.e., restructure the C):
```c
v1 = 9;
if (arg2 == v1) return 1;   // hmm, that changes semantics/bytes
```
No — must keep the same semantics? Actually the goal is byte-match, not semantic match. But the C must be a faithful decomp... The brief says lever-free body that scores 0; real C moves only. Changing `return v0` to `return 1` would alter the bytes (each return would set v0).

Hmm, but wait: in the target, `li v0,1` appears ONCE, and the returns branch to a shared block. So the C must keep a single variable holding 1 and returning it. ✓ (v0 = 1; ... return v0;).

So option (a): inline the constants. Let me think about what gcc does with:
```c
v0 = 1;
if (arg2 == 9) return v0;
if (arg2 == 0x11) return v0;
if (arg2 == 0x29) return v0;
if (arg2 == 0xA) return v0;
return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
```
gcc: for each comparison, it needs a register for the constant: `li v?,9; beq a2,v?,...`. With 4 separate pseudos each set once and used once, local-alloc may assign them all $3 (since they're not simultaneously live) — or $3,$4,$5... The target has all four in $3 (v1). If gcc assigns them $3,$4,$5,$6, the bytes differ.

Hmm, but the target has them all in v1=$3 — consistent with a single pseudo reused (as the current C does). If gcc reused the same pseudo for 4 separate constants, that's a "reuse" optimization (combine) — plausible.

Option (e): make the const temp a *different width* so its qty/life changes: e.g. `s16 v1` — the constants 9,17,41,10 fit in s16 → `li` with HImode → different instructions (ori). No.

Option (f): use `u16 v1`? Constants as u16 → HImode → ori. No.

Option (g): Keep the const temp but make the "1" pseudo have more refs: e.g. `v0 = 1; v0 = v0;`? Silly.

Option (h): The "1" value: what if I use a *constant* in the returns but with the same single set? e.g.
```c
v0 = 1;
...
```
The pseudo's qty = refs. In local-alloc, the priority is based on... let me think about gcc 2.7.2 MIPS local-alloc: it allocates registers to pseudos in order of "qty" (number of references) within a block, and the ordering is by "reg" preference. Actually in local-alloc (final.c), the allocation order within a block is determined by `allocno_compare`? No, that's global-alloc. local-alloc allocates hard regs to pseudos by scanning: for each block, it sorts the pseudos by "qty" descending? Let me recall final.c: local_alloc() → for each block, `alloc_no`... The MIPS local-alloc (`mips_local_alloc`? no, `targetm.local_alloc`) iterates over the block's live pseudo regs and assigns in order of `qty` (references count) — actually `local_alloc` in final.c uses `qrys` sorting by `reg` (the "preferred reg" ordering) — hmm.

In GCC's final.c `local_alloc`: it processes `reg` numbers: for each pseudo in the block sorted by `qty` (via `qsort` on `qty`?) hmm.

Rather than theorize, let me experiment. Cheap experiments (each ~15-30s):

E1: inline the constants (drop the v1 temp).
E2: v0 declared as s16/u16 (widths).
E3: v1 declared as s16/u16 (widths) — the constants would be ori... no.
E4: move the `v0 = 1;` assignment after the first compare (statement order) — i.e., restructure:
```c
v1 = 9;
if (arg2 == v1) return v0;   // v0 undefined here! not valid C
```
No.

E5: swap decl order (v1 before v0) — decl order affects local-alloc order.
E6: init at decl: `s32 v0 = 1;`? But v0=1 must be inside the if-block. Could do `s32 v0 = 1;` at the top of the block? Same thing.
E7: do-while(0) boost to give the const temp MORE refs (wrong direction) or the "1" more refs.

Wait, actually — think again about which pseudo should get $2. The target has "1" in $2 (v0) and const temp in $3 (v1). The const temp is used more. In the *pinned* version, the pin forced v0→$2 regardless.

Without the pin, gcc chose const→$2, "1"→$3. So gcc's priority favors the const temp. To flip, I need to lower the const temp's priority or raise the "1"'s.

Idea: make the const temp live-across fewer blocks or have fewer refs: e.g. use FOUR separate temps (one per constant) — each with 1 set/1 use = 2 refs. Then "1" (6 refs) wins $2. And each temp is used immediately → local-alloc may give them $3 each (or $3,$4,$5,$6). Since the target needs all four in $3, gcc would need to coalesce them into one pseudo (combine) — with the same value? No, different constants → different pseudos, but they can share a register since not simultaneously live. GCC's local-alloc assigns hard regs to pseudos in a block; two pseudos live at different times can share a hard reg only if they're not live simultaneously — local-alloc does handle that (it allocates per-block with a "conflict" notion).

So E1 is plausible: four separate constant pseudos, all in $3.

Let me also consider: maybe simply declaring the const temp AFTER the "1" var or changing the order of statements in the block (e.g. `v0 = 1;` first is already first).

Another idea: the "1" pseudo's live range: it's set at ins 23 and used at 4-5 return sites. The const temp is set 4 times.

Let me try a batch of variants and score them in parallel (multiple Bash calls in one turn).

Let me write variants for item 3:
- v1_consts_inline.c: constants inlined, v0 kept.
- v0_u16.c: v0 as u16? But v0 = 1 then `return v0` → the return value would be sign/zero-extended; u16 → 1 ✓ but the return type s32 → zero-extend (no change for 1). HImode copy escapes cse (per moves.md). Might change allocation.
- v0_s16.c: v0 as s16 → return v0 sign-extends → li v0,1 fine.
- v1_s16.c: const temp as s16 → `li` of 9/17/41/10 as HImode → different bytes (ori v1,zero,9). ✗ probably.
- decl_swap.c: v1 declared before v0.
- v0_init.c: `s32 v0 = 1;`? can't (must be inside the block).
- v0_dowhile.c: `do { v0 = 1; } while (0);` — loop-weighted ref boost for v0! (moves.md G06: "do-while(0) around the tail gives the byte temp a loop-shaped live range, so local-alloc ranks it above the ret0 copy and it wins $2"). This boosts v0's priority. But is a fake do-while a "new lever"? It's a loop-shape move; the brief allows do-while(0) with the `// !FAKE: do-while` marker. Hmm, "no new lever of any kind" — I'd rather first try plain C moves; keep do-while as a fallback (and note it in the log with the marker).

Let me write 4-5 variants and score them in parallel.

Variant A (inline constants):
```c
s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 v0;
    if (*(u16 *)((u8 *)arg1 + 0x0) == 0) return 0;
    if (*(s32 *)((u8 *)arg1 + 0x58) == 0) return 0;
    if (*(u16 *)((u8 *)arg1 + 0x5E) != arg2) {
        if ((*(s32 *)((u8 *)arg1 + 0x5C) & 0xC100) != 0x8000) return 0;
        if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
            v0 = 1;
            if (arg2 == 9) return v0;
            if (arg2 == 0x11) return v0;
            if (arg2 == 0x29) return v0;
            if (arg2 == 0xA) return v0;
            return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
        }
    }
    return 0;
}
```
Careful: I must keep the original brace/statement shape (the `if (...) { return 0; }` blocks) because statement order/shape affects the code. Actually the braces with a single statement are equivalent; but to minimize risk let me keep the original formatting exactly and only change what I test.

Variant B: v0 as s16.
Variant C: v0 as u16.
Variant D: decl order swap (v1 then v0).
Variant E: const temp as u8? no (41 > 255 ok, but 0x29=41 fits) — u8 would make `li v1,41` = ori. ✗.

Let me write A-D and score them in parallel (4 Bash calls in one turn). Note each call ~20-40s.

Also note: the `nopin.c` from the previous run is exactly my baseline (score 17).

Let me write thefiles.
