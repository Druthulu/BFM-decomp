---
ts: 2026-10-21T23:43:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_xjfkoGI1D9LiK76QcikF
---
Those .s files in .run are scratch. Let me check the corpus dir: decomp-architect/corpus might have the ROM disassembly. Let me grep for "8014C308" in decomp-architect/ (maybe a .s or .asm).

Actually — maybe more efficient: use `tools/masked_diff.py <a.o> <b.o|.s> [fn]` as a spot-check: it might print both functions' insns. But I need the object path.

Let me get the object path from recipes.json via grep (allowed). The recipes.json is JSON with indent=1; entries look like {"src": "...", "obj": "...", "pipeline": "..."}. Let me grep -A 6 for the src of one includer.

But which includer is rec[0]? Let me instead grep for the header's includers list order... simpler: grep recipes.json for '"src": "src/ov_SC03_099/ov_SC03_099_after.c"' with -A 8 to see the obj path, then objdump that baseline object via masked_diff? masked_diff needs two objects.

Alternative plan to see the ROM asm: write a candidate whose compiled body is identical to the ROM except for one instruction, so the diff prints the whole target... that's what probe did — and it printed 39 target instructions. The last three are "move v0,zero; nop; nop". So the ROM's last 3 instructions of this function per the tool are those.

Hmm OK, so what does that mean? Let's think again about the ROM layout: maybe the function's epilogue is:
```
+0x90: move v0,zero
+0x94: jr $ra
+0x98: move v0,$2
```
and the tool's dump... prints "nop"?? Let me verify by checking another function's known-good body: the pinned body scores 0 → 39 ins both. So my compiled body also ends with the same 3 instructions. Let me look at what my compiled body looks like — I can see it in the diff of nopin (the "mine" lines): mine[36] `j 6ac4`, and the tail wasn't shown (equal region).

So gcc emits for the pinned body: ... `move v0,zero` + `nop` + `nop`? That means the epilogue `jr $ra` is missing?! Unless the object is a fragment ("tail.data.o") where the epilogue was moved elsewhere (the ROM's ov functions are split into "tail" objects; maybe the jr $ra lives in a different fragment!).

Look: build/asm/ov_SC03_099/data/tail.data.o, tail2.data.o... The ov TU is split into multiple object fragments, each with its own .text; the function's instructions might be split across fragments?! That would explain a missing epilogue.

Hmm, but the score compares only the instructions the tool extracts for that function from that object. If the epilogue is in another fragment, the comparison ignores it. Fine — not my problem.

Key insight: the score is instruction-level on the extracted function, and the ROM bytes are the ground truth. I just need to match.

Now, back to the actual crack for item 3.

The target: the "1" value in $2 (v0) and the const-chain in $3 (v1); also the ROM's structure: `li v0,1` appears once at ins 23, AFTER the first compare (ins 21-22). And branches to +0x94 for all four "return 1" arms?? Wait no: branches at 22, 25, 27, 29 go to +0x94 which I hypothesized is the epilogue-ish block. If the "li v0,1" at 23 sets v0=1 and then branches to +0x94 return v0... but branch 22 (before ins 23) also goes to +0x94 with v0=0 (the `and` result). That contradicts "return 1" semantics.

Unless the `and` result isn't 0: at ins 19 `and v0,v0,v1` — we're in the branch where (s16 & (u16)arg3) == 0, so v0 = 0 → bnez v0 not taken → so at ins 21+, v0 = 0. Then beq a2,v1(=9) → +0x94 → returns v0=0. That means the ROM returns 0 when arg2==9?!

Hmm, so the ROM's semantics differ from the C source? But the pinned body scores 0 → the pinned C compiles to these bytes. So the C source is "correct" in the sense of byte-matching, but the branch at 22 jumping to the "return 0" block means the C's `if (arg2 == v1) return v0;` compiles to a branch to the return-0 block?! That can't be, unless the block at +0x94 returns v0 (=1 set at ins 23 in the fallthrough path). Let's re-examine: maybe the block at +0x94 is NOT "move v0,zero".

Address mapping: maybe ins 36 `move v0,zero` is at +0x8C, not +0x90, if some instructions have 8 bytes (e.g. lui with reloc? no, still 4). Hmm, all 4 bytes.

But wait: the branch at ins 10 `beq v0,a2,6ab8` = +0x90 → that's ins 36 = `move v0,zero` → "return 0" (matches C: `if (*(u16*)(arg1+0x5E) != arg2)` → if equal, skip the block → return 0 at the end). ✓.

And branch at 20 `bnez v0,6ab8` → also to ins 36 `move v0,zero` → "return 0" (matches C: if the mask test != 0 → return 0). ✓

And branches at 22,25,27,29 → 6abc = +0x94 → ins 37 = `nop`?? That must be the block where the function returns v0=1... but ins 37 is "nop" and ins 38 "nop".

Hmm! Unless the block at +0x94 is `jr $ra` + delay slot `move v0,$2` and the tool prints... Let me recheck the tail of the probe output:

```
       34  --    | j	6abc <func_8014C308+0x94>
       35  --    | sltu	v0,zero,v0
       36  --    | move	v0,zero
       37  --    | nop
       38  --    | nop
```
Hmm wait, maybe the listing order is off: the objdump prints instructions in address order; the diff prints mine/target indices. The last line of the insert opcode was target[36] = "nop"? Let me recount the printed target indices in the insert block: 0..37? The opcode said "insert mine[0:0] target[0:37]" → 37 lines printed, indices 0..36. Then "replace mine[1:2] target[38:39]" → target index 38 printed, and target[37] is missing from printing?!

Looking at the printed list: 0,1,2,...,36 — the last printed index in the insert block is 36 (`move v0,zero`)? Let me recount the output lines:

```
 0 lhu v0,0(a1)
 1 nop
 2 beqz v0,6abc
 3 move v0,zero
 4 lw v0,88(a1)
 5 nop
 6 beqz v0,6abc
 7 move v0,zero
 8 lhu v0,94(a1)
 9 nop
10 beq v0,a2,6ab8
11 li v1,0x8000
12 lw v0,92(a1)
13 nop
14 andi v0,v0,0xc100
15 bne v0,v1,6abc
16 move v0,zero
17 lh v0,174(a1)
18 andi v1,a3,0xffff
19 and v0,v0,v1
20 bnez v0,6ab8
21 li v1,9
22 beq a2,v1,6abc
23 li v0,1
24 li v1,17
25 beq a2,v1,6abc
26 li v1,41
27 beq a2,v1,6abc
28 li v1,10
29 beq a2,v1,6abc
30 nop
31 lw v0,376(a0)
32 nop
33 xor v0,v0,a1
34 j 6abc
35 sltu v0,zero,v0
36 move v0,zero
```
then "replace mine[1:2] target[38:39]": "1 move v0,zero | nop" → target[37] is not printed (it's the "equal"?? no...). Hmm, the diff opcodes: insert target[0:37] (indices 0-36), then some equal region covering target[37], then replace target[38:39].

Wait, that can't be: after the insert of 37 target insns, mine has 1 ins ("move v0,zero" = my probe's return 0). The alignment: insert target[0:37] with mine[0:0] (nothing), then "replace mine[1:2] target[38:39]" — hmm, that skips target[37]. Unless the insert was target[0:37] = indices 0..36, then equal target[37:38] vs mine[0:1]? But mine[0] is "move v0,zero" and target[37] is "nop" — not equal. Hmm, but masked_word might treat "move v0,zero" and "nop" as equal? masked_word masks reloc operands; "move v0,zero" vs "nop" differ.

Unless the probe's compiled body is: `move v0,zero; nop`? Actually my probe compiles to: `move v0,zero` then `jr $ra`? Wait — the target's function has NO jr $ra either. Hmm, my probe compiled body would be: move v0,zero; jr $ra; nop. The tool's insns_from_object for my candidate: 2 ins ("mine 2 ins") → so my probe compiled to exactly 2 instructions: "move v0,zero" and "nop"?? That means the `jr $ra` is missing from my object too!

So the extraction is missing the final `jr $ra`. Why? Because the ov "tail" object splits the function: the last fragment contains the epilogue? Or the objdump's -j .text with the function label... hmm, "mine 2 ins" for a function that should be 3 ins (move, jr, nop).

OH WAIT. Maybe the ROM code and my compile both end with:
```
move v0,zero
jr $ra
nop
```
and the tool prints... no, it printed "nop" for target[37]?? Actually I haven't seen target[37]; the replace opcode shows target[38]="nop" and mine[1]="move v0,zero" (my probe's first ins is "move v0,zero"?? and my probe's 2 ins are [0]="move v0,zero", [1]="nop"). So mine[1] = "nop" — but the printout says mine[1] = "move v0,zero" and target[38]="nop". Hmm, that means mine[0]="?" (equal to target[37]) and mine[1]="move v0,zero" vs target[38]="nop".

So mine = [X, "move v0,zero"] where X == target[37] (unknown, printed as equal so not shown) and target[37] == target[36]?? no, equal to mine[0].

So: target[37] == mine[0], and my probe's insns are [target[37], "move v0,zero"]. My probe body `return 0;` compiles to: "move v0,zero" then "jr $ra"... so mine[0] should be "move v0,zero" and mine[1]="jr $ra". Then the printed replace line "1 move v0,zero | nop" would mean mine[1]="move v0,zero" — contradiction.

Unless the printed format is: f"{i1+k:4d} {m_:34s} | {t_}" where m_ = mine[i1+k] and t_ = target[j1+k]. For "replace mine[1:2] target[38:39]": k=0 → mine[1] and target[38]. It printed "1 move v0,zero | nop". So mine[1] = "move v0,zero" and target[38] = "nop".

So mine = [?, "move v0,zero"] and target[36]="move v0,zero", target[37]=?, target[38]="nop".

So my probe compiled to 2 instructions: [something, "move v0,zero"]. If the first is "jr $ra"?? and the second "move v0,zero"?? That's a delay-slot order thing? No.

Hmm, maybe the tool's extraction takes the LAST n instructions? Or the object's .text for the ov TU is a "tail" fragment where functions are emitted in reverse?

You know what? This doesn't matter much. What matters: the target's 39 instructions as printed, and my job is to match them. The "missing jr $ra" affects both sides equally.

Let me re-derive the ROM's tail semantics with the printed list (which has 39 entries: 0..38 where 37 unknown and 38 = nop):
- The last printed: 34 `j 6abc(+0x94)`, 35 `sltu v0,zero,v0`, 36 `move v0,zero`, 37 ?, 38 `nop`.

Hmm, if 37 = "jr $ra" and 38 = "nop"... but then what's my probe's mine[0]? "jr $ra" — equal to target[37] ✓ and mine[1] = "move v0,zero"?? My probe `return 0` → "move v0,zero; jr $ra" — order is move then jr. Unless the probe compiled to "jr $ra" then... no.

Hold on: maybe mine[0] = "move v0,zero" is equal to target[37]... then target[37] = "move v0,zero" and target[36]="move v0,zero" too? Both move v0,zero? That would mean the ROM has two "move v0,zero" in a row (at +0x90 and +0x94)?

Hmm, the equal opcode covers target[37:38] vs mine[0:1]: mine[0] == target[37]. My probe body: `s32 f(...) { return 0; }` compiles to:
```
move v0,zero
jr $ra
nop
```
= 3 instructions, but "mine 2 ins" says 2. So the extraction dropped one. Which one? If it dropped the LAST (nop) → mine = ["move v0,zero", "jr $ra"], then mine[0]="move v0,zero" == target[37] → target[37]="move v0,zero"?? but then target[38]="nop" and mine[1]="jr $ra" ≠ "nop" → the replace line shows mine[1]="move v0,zero" — contradiction again.

If it dropped the FIRST → mine = ["jr $ra", "nop"]: mine[0]="jr $ra" == target[37] → target[37]="jr $ra" ✓, mine[1]="nop" vs target[38]="nop" → they'd be equal, not "replace". But the printed replace says mine[1]="move v0,zero"...

Hmm, so printed "1 move v0,zero | nop" — maybe the columns are swapped?! In the earlier diffs, "replace mine[36:37] target[34:35]" printed "36 j 6ac4 | j 6abc" — mine on the left. So columns are (mine, target). So mine[1]="move v0,zero", target[38]="nop".

Then target[37] == mine[0]. If mine = ["move v0,zero"(=probe's return), ...] no wait mine[1]="move v0,zero" means the second instruction of my probe is "move v0,zero". So my probe compiled to [?, "move v0,zero"]. With `return 0;` the first ins should be "move v0,zero"...

Unless the probe's function is the FIRST in the object and the extraction... ugh.

New idea: maybe my probe compiled to: "jr $ra" is missing and the compiler emitted "move v0,zero" twice? No.

Let me stop. The exact tail doesn't matter: what matters is matching the instruction sequence. Let me use a different approach for verification: just compare scores.

Actually, hold on. It DOES matter for understanding: the ROM's `beq a2,v1,6abc` where 6abc = +0x94 = ins 37 = "jr $ra"?? If ins 37 = "jr $ra" and ins 38 = "nop" (delay slot), then the branch to +0x94 jumps to the jr $ra, returning v0 — and v0 at that point: for the branch at 22, v0 = 0 (from the `and`)! So `if (arg2 == 9) return v0;` would return 0 — but the C intends 1.

Hmm, unless v0=1 is set BEFORE (the `li v0,1` at ins 23 is AFTER). So the ROM returns 0 for arg2==9?? That's semantically odd but the ROM is ground truth and the pinned C matches it byte-wise... which means the pinned C also has that behavior? The pinned C: `v0 = 1; v1 = 9; if (arg2 == v1) return v0;` — the compiler would emit `li v0,1` before the compare if v0 is live... but the ROM has li v0,1 after the first beq. Hmm, so in the ROM, the branch at 22 goes to +0x94 returning v0 — where v0 = 1 must have been set BEFORE ins 21. But there's no `li v0,1` before ins 21! Unless v0's value at ins 21 is... the `and` result = 0.

So the ROM returns 0 when arg2==9 (i.e. the "return 1" case is broken?) OR the branch target 6abc is not the return.

Hmm, hold on: maybe the branch target +0x94 is a "return 1" block: `jr $ra` with delay slot `move v0,$2`? no, that returns v0 as-is.

Alternatively the block at +0x94 might be: ins 37 = "jr $ra", ins 38 = "nop" — a shared return. Then all those branches return v0 as it is. For branch 22 (arg2==9) v0=0 → returns 0. For branch 25 (arg2==17) v0=1 (set at ins 23) → returns 1! For 27, 29: v0=1 → returns 1.

So the ROM: arg2==9 → returns 0?! and arg2∈{17,41,10} → returns 1. Weird but that's the ROM. And the C source (which compiles to the same bytes) has the same quirk: gcc evaluated `if (arg2 == v1) return v0;` with v0 not yet assigned?? No — in the C, v0=1 is assigned before the compares, so gcc would set v0=1 before ins 21. But the ROM has li v0,1 at 23 (after the first beq).

Hmm, that means the C's `v0 = 1;` was scheduled by gcc to after the first compare — gcc can do that if the first compare's branch doesn't need v0... but the branch at 22 (arg2==9 → return v0) DOES need v0! Unless gcc's reordering moved the li v0,1 after the beq because the beq is on the path where v0 is not yet needed... but the branch target uses v0.

Unless the branch at 22 targets a block that sets v0=1 (i.e. the branch goes to a "return 1" block, not the shared return). Ugh, addresses.

OK here's the thing: +0x94 = ins 37. If ins 37 = "jr $ra", branches to it return v0 as-is. If ins 37 = "nop" and the real return is elsewhere, the function falls through.

I think there IS a subtlety: the "tail" fragments. The ov TU's .text is split across tail*.data.o fragments; the function's epilogue might live in a different fragment. When the tool extracts "the function's instructions" from ONE object, it might miss the epilogue if the epilogue is in another fragment — but the tool compares per object, so both sides miss it equally.

Given the confusion, let me get the actual ROM asm. Where can I get it? The corpus dir: decomp-architect/corpus — maybe contains the ROM disassembly (.s splat files). Let me look for a directory with the game's asm.

Let me check: ls decomp-architect/corpus | head. And search for a file containing "8014C308" in decomp-architect (maybe .asm or .txt).

That's worth one call.
