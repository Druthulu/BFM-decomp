---
ts: 2026-11-06T11:35:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FUrOm9k3QHc6AZfcKBgV
---
I can disassemble the target object. But the object contains many functions. Let me objdump the object and extract func_80188778. The target object is the compiled source? Wait build/ is the build from src — which for a matched function equals the target. Actually the "target" is the original game object, and build/ is compiled from src. Hmm, delever_search compares candidate against "the function in build/". So build/src/ov_SC04_018/...o is the reference = compiled from current src = byte-identical to target for matched functions. So the .o's func_80188778 is the target.

Let me disassemble it to see the exact insns. Use mips objdump. What's the toolchain? Let me check tools. There's likely `mips-linux-gnu-objdump` or similar. Let me look for the disassembler used elsewhere. Search HOW_WE_WORK tools? Or just try `objdump -d`. Actually the target is MIPS. Let me check tools/ for objdump.

Let me grep HOW_WE_WORK.md for objdump. Or just try common names. Let me look at the bin dir.

Actually, I can get the target insn list from delever_search's diff itself — it prints insn text. The diff already shows the relevant lines with insn numbers and text. I have enough:
- target[60] li v0,3; mine[60] nop
- target[73] beqz v0,1010 vs mine beqz v0,100c (offset shift by 4)
- target[83] beqz v0,ff8 + target[84] addiu v0,s1,1 (delay slot); mine[83] beqz v0,ff0, no delay slot insn? mine[84] absent. Wait the diff says replace mine[83:84] target[83:85]: mine has 1 insn (beqz), target has 2 (beqz + addiu). So mine's beqz delay slot is a nop (not shown as it's the next). Hmm.

Actually the "ins" count: mine 143, target 144. Target has one more insn: the addiu v0,s1,1 duplicated in delay slot (target[84]). Mine doesn't have it there.

- target[93] bnez v0,fc0 at 94 vs mine at 93: offset shift.
- store moved.

So to reach 0, I need:
(1) the li v0,3 copy in the outer bne delay slot
(2) the addiu v0,s1,1 in the inner beqz delay slot
(3) the store ordering

These correspond to levers 3/4, 5, 6. Levers 3/4 and 5 relate to reorg delay-slot fill. Lever 2 (pin n) apparently wasn't needed in this lever-free version? Wait, the diff shows only these; the pin n removal didn't add a diff? Interesting — maybe pin n was load-bearing only in combination. Actually the header says lever 2 changes reorg's choice for the inner bne delay slot. In my lever-free version, maybe the other diffs mask it.

Let me try targeted real-C moves:

For (1): The `n = 3` constant load. Use HImode copy trick: declare `s16 n`? Then `n = 3` might still be li. Or use `s16 n; ... n = 3;` Hmm. Actually the known trick: make a temp of HImode: `s16 t = 3; n = t;`? The HImode copy escapes cse. Let me think: target has `li v0,3` (word). If I write `s16 k = 3; n = k;` then n=k is a sign-extend of an HImode value; gcc would emit `li v0,3` then... hmm, s16 3 -> sign extend -> still 3. It might produce li v0,3 directly.

Better: try declaring `n` as s16. The target's `li v0,3` — for s16 n, assignment n=3 gives li v0,3 (word constant in reg). The comparison `i < cnt` where cnt=n. Hmm.

Let me just experiment quickly with variants and use sc.sh to score multiple candidates at once.

Let me think about (2): the duplicated `addiu v0,s1,1` (i++). In target, the beqz (D_80115158[i].h != 0 check) has delay slot `addiu v0,s1,1` (the i++), and after the call `addiu v0,s1,1` appears again. Wait the comment: "the `beqz` slot is filled from the branch TARGET instead — the duplicated `addiu $v0,$s1,1` the target has in both the delay slot and after the call." So i++ is computed twice: once in the delay slot (speculative) and once after the call (because the call clobbers?). Actually it's the same source `i++` scheduled into the delay slot and re-emitted after? Hmm, reorg duplicates an insn from the fall-through/target into the delay slot. The insn is `addiu v0,s1,1` (i+1 into v0). The target has it in the delay slot AND after the call. Without the barrier, reorg fills the slot from the fall-through by stealing `addu a0,s0,zero` (per lever 5 comment). 

To get reorg to fill from the branch target without asm, need `stop_search_p` to stop — it stops on asm/jump/label. So if the instruction right after the beqz (in the fall-through) is a jump or label, reorg won't scan past. Real C: make the if-body's first thing a... hmm. The branch is `if (D_80115158[i].h != 0) { ... }`. The fall-through is the else (i++; w++). If we restructure so that the branch is inverted or there's a label... 

Alternatively, use a `goto`? The target's structure: `if (cond) { call }` then `i++; w++;`. Reorg's fill_simple_delay_slots scans forward from the branch for an insn to move into the slot, avoiding insns that aren't safe. `stop_search_p` returns true on asm, jump, label, etc. So if the insn immediately after the branch were a label or jump... 

What if I write it as:
```
do {
    if (D_80115158[i].h == 0) goto skip;
    ot = call(...);
skip:
    i++;
    w++;
} while (i < cnt);
```
Then after the branch (`beqz` on ==0) the fall-through is the call, and the branch target is `skip:` label (i++). Hmm, reorg would scan the fall-through (call) — it can't move a call into a delay slot. Then it might look at the target. Actually fill_simple_delay_slots: for a branch, it tries to fill from the fall-through (try_fill_simple_delay_slots). If the fall-through's first insn is a call (not eligible), it stops. Then it tries the target? There's also `fill_slots_from_thread` for the taken branch... Hmm.

This is getting deep. Let me look at how reorg.c works and maybe the exact mechanism. But time budget.

Let me try quick experiments. Create variant bodies:
- v1: n declared s16.
- v2: use `s16 three = 3; n = three;` in both arms? 
- v3: invert branch + goto.
- v4: struct-typed D_801151D0.

Let me be systematic but fast. I'll generate a few variants and run sc.sh (one score line each). Then inspect best.

Actually, let me reconsider the whole approach. These two SC03 siblings are documented as requiring 6 levers, each byte-verified. The odds of cracking all three remaining diffs with real C are low but the moves catalog has shown HImode tricks crack opaque copies. Score 9 is close. Let me give it a solid try within budget.

Let me first get the full target disassembly to know exactly what's at each insn, so my variants target the right thing. Let me find the objdump tool. Let me check `tools/` for a disassembler script.
