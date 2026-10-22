---
ts: 2026-10-21T23:36:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_D9gxVRzfQjbrjghh5RWF
---
Good, the tool works. Score 17 for nopin (pin removed). Target uses $2 for the "1" constant (v0) and $3 for v1. Wait target: "li v1,9; beq a2,v1" and "li v0,1" — so target keeps v0 (the 1) in $2 (v0) and v1 in $3 (v1)? The register pairs say "v0->v1 x3": mine v0 corresponds to target v1. So in target, the const 9/17/41/10 lives in v1 ($3) and the "1" lives in v0 ($2).

Mine: li v0,9 etc. — the v1 variable got allocated $2, and v0 (the 1) got... "move v0,zero / li v0,9": hmm mine has v0 used for the constants, meaning mine allocated v1→$2 and v0→$3? Actually mine: `li v0,9; beq a2,v0` and target `li v1,9; beq a2,v1`. So mine's v1 got $2, target's v1 got $3.

The original (with pin) has v0 pinned to $2 and v1 as local → v1 gets $3. So the pin on v0 is what keeps v1 in $3! Without the pin, local-alloc gives v1 $2 (first come) and v0 $3.

Wait, in the original the pinned v0 = $2 is the "1" return value and v1 = constants in $3. Without the pin, the allocator assigns $2 to v1 and $3 to v0 (or something).

So the crack: make the "1" return value not a competing local, or make v1 get higher priority. Options:
- Return the constant 1 directly (`return 1;` instead of `v0 = 1; ... return v0;`)? But then v0 disappears entirely, and the target's structure: target has `li v0,1` once and returns it in 5 places. If we write `return 1;` the compiler would emit `li v0,1` at each return site? Actually gcc might CSE: `li v0,1` before each return → multiple sets of v0 → "flow-unused-result"-like issues. Hmm.

Look at target code order: target at [20:30]:
```
20  bnez v0,...
21  li v1,9
22  beq a2,v1
23  li v0,1
24  li v1,17
...
```
Hmm interesting: target has `li v0,1` in the middle, i.e. v0=1 computed before the v1 chain? Actually the target is:
```
beqz v0 -> ...
li v1,9
beq a2,v1 -> ...
li v0,1        <- hmm, wait
li v1,17
beq a2,v1
li v1,41
beq a2,v1
li v1,10
beq a2,v1 (if == -> return 1)
...
```
Hmm target shows at 23 `li v0,1` then 24 `li v1,17`. That suggests target computes v0=1 early (right after the first comparison?). Mine has `move v0,zero` at 21 and `li v0,9` at 22 — mine put v0=0? weird: "move v0,zero" — that's `return 0` path maybe. Hmm.

Actually mine[21] `move v0,zero` then mine[22] `li v0,9`: so mine uses v0 for the constants 9/17/41/10 and also has a `move v0,zero` for a return 0. And mine[32] `li v0,1`.

The mapping "v0->v1 x3" means mine's v0 register corresponds to target's v1 register in 3 places. So mine allocates the const-chain temp to $2 and target allocates it to $3.

So the difference: in target, the "1" is in $2 (v0) and the const chain in $3 (v1). In mine, const chain in $2 and "1" in $3.

To crack: make the "1" value have priority so it gets $2. The pin did that. Without the pin, how?

Ideas from moves.md:
- "do-while(0) around the tail gives the byte temp a loop-shaped live range, so local-alloc ranks it above the ret0 copy and it wins $2" (func_8017CE7C, G06) — a lever? do-while(0) with // !FAKE: do-while marker is allowed as "loop shape" real C move? The brief says `do{}while(0)` only with `// !FAKE: do-while`. But is a fake do-while a "new lever of any kind"? The constraint says levers of other kinds may stay but no new lever added. Hmm, do-while(0) is not a pin/launder/barrier/keepalive lever per se; moves.md used it in MATCHes (e.g., line 146, 67). And the worked example T10 used `do { r = p + i; } while (0);` to win the pin. So it's an accepted mechanism. It's "real C moves ... loop shape" per C0505 catalog. Good.

So for item 3: try giving the v0=1 value a boost. E.g., `v0 = 1` used in 5 returns → v0 has many refs but v1 chain also many.

Alternative approach: the real C move might be to give the constants their own variable of a different width, or reorder statements.

Let me think about local-alloc: it's about qty (quantity of refs?) and priority. In GCC MIPS, local-alloc assigns registers to pseudo-registers within a basic block based on the number of references (qty) and the "reg" preference.

Approach: give the const-chain temp more references so it wins $3? No wait — target wants const chain in $3 (v1) and 1 in $2 (v0). Mine gives const chain $2. If const chain gets more weight, it wins $2 (worse). We want the *1* value to win $2.

So boost v0's priority: e.g. make v0 = 1 set before the const chain in source order (statement order move). In the target, `li v0,1` appears at position 23 (after li v1,9 / beq). Hmm, in target v0=1 is set after the first beq. Actually the target's `li v0,1` at 23 might be the "v0 = 1" hoist: gcc hoisted the v0=1 assignment to the block start? It's after "beq a2,v1" which is the `if (arg2 == 9) return v0;` test → the v0=1 assignment is in the fallthrough path of that test. So in target, source order = v0 = 1; v1 = 9; if (arg2 == v1) return v0; ... That's exactly the source order in the header! v0=1 comes before v1=9.

But mine compiled to `move v0,zero` at 21?? That's odd. Actually mine[21] `move v0,zero` — hmm, wait: maybe alignment of the diff isn't 1:1; the diff is a sequence alignment. Mine[20] `bnez v0,...` matches target[20]. Then mine[21] move v0,zero vs target[21] li v1,9. The alignment says "replace mine[20:30] target[20:30]" 10 vs 10 lines, and register pairs v0->v1 x3. So mine[21] `move v0,zero` is a return-0 path (mine has extra `move v0,zero` where target has `li v1,9`?). Hmm confusing but roughly: mine has extra instructions (41 vs 39 ins): mine has `move v0,zero` + `j` + `li v0,1` extra in the tail.

Interesting: mine's tail at 31-33: `j 6ac4` / `li v0,1` deleted vs target --. So mine has an extra jump and li.

Honestly, iterating with the tool is the way. The previous coder left helper scripts (gen*.py, sweep*.py) in G08 — they did sweeps over widths (c_A_*.c, t_*.c, c_B_*.c, c_D_*.c families). Those were probably for item 1 (the width sweep with s16/u8 etc.). The names c_A_s16_s16_s32v1_u32v14 suggest combos of widths for 2 vars.

Since these prior sweeps exist for item 1 only, I'll do my own for items 3-9.

Let me now check the target assembly for item 3 to understand. The tool has --explain and the build/ dir has the target .s? "compares with the function in build/". Let me find the target asm file.

Actually the diff output already gives me the target instructions. Good enough.

Strategy per item: The pin is `register s32 v0 __asm__("$2")`. The goal: produce equivalent C where gcc naturally allocates $2 to that variable. Levers: statement order, temps, widths, decl order, init at decl, etc.

Idea for item 3: since v0 = 1 is used 5 times (returns), and v1 chain, maybe declare v0 as s16? A HImode copy escapes cse. Hmm but the value 1 returned as s32 → `li v0,1`.

Alternative: split the returns: `if (arg2 == 9) return 1;` directly (constant) — then v0 disappears, and each return site has its own `li v0,1`? gcc would generate `li v0,1` before each return → 5 sets of v0, but the target has one set at 23 and returns v0 in 5 arms... wait target's structure:

target[23] li v0,1 — then how does it return? Let's get the full target listing. Let me look at build/ asm for this function.

Let me find the target asm. The tool compares with the function in build/. Let's locate it.

Let me use `--explain`? Or find build dir files.

Let me check the structure of the repo build dir for the ov function.

I'll grep for func_8014C308 in build.

Also, I should consider using the delever_search --plan/--run machinery? Probably overkill; the previous coder used custom sweeps.

Given 7 items and ~20-30 min budget each, that's a lot. Let me be efficient: for each item, I'll write a sweep script that generates variants (widths, order permutations, decl moves, do-while boosts) and scores them in parallel, then inspect the best.

But first, understand the scoring tool better and see the target asm.

Let me look at how many includers each header has (for the header constraint). tryinc.py k=0..n-1. The header items are included by many TUs; the score must be 0 on every includer. That's a big burden: the same body must match at every includer site?! Interesting — in moves.md line 141: "141/141 includers 0". So yes, headers have ~141 includers, and the body must score 0 at each. Wow. That means the body must be such that gcc generates identical code at every includer site (the includers differ in surrounding code but the function body compiles the same). Since the function is the same, the compilation is essentially identical... unless context (like preceding code) affects register allocation? The function is separate; gcc compiles per function, so the body should compile identically at each site, except that macro/type definitions could differ per includer (e.g. different `register` declarations or types). Actually likely identical → checking one includer may be enough, but the check requires all.

How does --try with a TU header work? It found the header and compiled at each includer? The output "src/shared/ov/func_8014C308.h:func_8014C308: score 17" — it probably compiles the function in the context of each includer TU and compares to the target. Let's see how many includers: tryinc.py prints "[includer k/N: src]". So I can run tryinc.py 0 to see N.

Let me check the target build and the includer count.
