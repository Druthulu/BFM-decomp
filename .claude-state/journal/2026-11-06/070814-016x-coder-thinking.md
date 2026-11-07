---
ts: 2026-11-06T14:08:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YVmW9Glta5M9pv8rN4n4
---
Now I understand the loop. Registers:
- $9 = src (u16*)
- $11 = dst
- $10 = i
- $12 = n
- $7 = px
- $16 = s0v, $25 = t9v, $24 = t8v
- $14 = 0x66666667 (division by 2560 magic)
- $13 = arg0+12
- $15 = arg0

The two keepalives are `__asm__("" :: "r"(src))` and `__asm__("" :: "r"(i))`.

The comment says:
- src keepalive: "+2 refs on src (depth-2): keeps src above i, below the mfhi temp"
- i keepalive: "+3 refs on i (depth-3): lifts i over dst in the $t2 race"

So in sched1/greg, the number of references affects priority. We need real C that produces the same.

Note: the asm statements produce `#APP #NO_APP` in the assembly (they appear in the output as comments). Interesting: the target asm shows `#APP #NO_APP` after `lw $9,0($13)` and after `mult $6,$24`. These are the asm statements! The target itself (byte-identical) includes those #APP/#NO_APP markers. Wait — this dump is the current body with keepalives, which scores 0 = byte-identical to target. So the TARGET ITSELF contains these #APP/#NO_APP markers? That can't be — the target is the original game binary; the compiled object must match it byte for byte, and asm statements produce no bytes... Actually `__asm__("")` with no output produces no instructions, but gcc may emit `#APP`/`#NO_APP` comments in the assembly file. Comments don't produce object bytes. So the object is byte-identical regardless. The #APP/#NO_APP are just asm comments in the .s listing, not in the object. OK.

So score 0 = object matches target. The keepalives affect scheduling/register allocation but emit no code, hence they can match.

Now, to remove them and keep score 0, I need real C changes that reproduce the same schedule/regalloc.

What do the keepalives do exactly? They add references to `src` and `i` pseudo-registers. In gcc 2.7.2, sched1 uses REG_N_REFS (number of references) in its priority calculation. Adding refs raises priority, so the pseudo gets scheduled earlier / gets a better register.

Let me think about the "races":
1. "$t2 race": The register $2 (v0) is used as the mfhi temp / division. i, dst, src... Let me map:
   - $10 = i, $11 = dst, $9 = src. These are caller-saved temps.
   - $2 is used for many things.
   
2. Comment: "+2 refs on src (depth-2): keeps src above i, below the mfhi temp". "above" maybe means higher priority than i, lower than mfhi temp.

3. "+3 refs on i (depth-3): lifts i over dst in the $t2 race".

So i has 3 more refs than src... Actually both refs added at their asm site.

Real C ways to add refs: use the variable more times in real computation. But we must not change behavior. Adding uses means dead code. Hmm, but real C that changes nothing semantically... We could restructure the loop so that the same number of refs arise naturally.

Actually wait. Let me reconsider. The task says lever-free = no keepalive macro or asm. But we can use "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)".

The classic approach in these shards: replace keepalive with a real computation that uses the variable. E.g., from the moves.md: "keepalive replaced by return v0", "keepalive: obase set right after pbase and used for the first load too", "keepalive: continue->goto next_j + j++ in 2 nested do-while(0)", "keepalive: do-while ref weight cracked", etc.

Let me look at how keepalive was cracked before. Let me grep moves.md for keepalive MATCH entries and read a couple of worked examples. Let me grep more specifically.

Actually, the key question: what are the ref counts in the current code and how can real C increase refs on src and i?

In gcc, sched1 priority uses REG_N_REFS (weighted by loop depth: refs in loops count more). The asm statements are in the loop (depth 2 for src, depth 3 for i? Actually the loop is depth 1 inside function... hmm "depth-2" might refer to the asm ref being at loop depth 2 because it's in the do-while inside the if inside the while? The while is depth 1, the do-while is depth 2?).

Hmm. Let me think about loop depth: The `while ((arg0->cmd & 0xFFFF) != 0xFF)` is a loop (depth 1). Inside, `do { } while (i < n)` is another loop (depth 2). The asm for src is before the do-while (depth 1)? No, it's after `src = arg0->data;` and before `dst = src + n;`, i.e., outside the do-while but inside the while — depth 1. The comment says "depth-2". Maybe the function has an outer loop? No. Hmm, maybe "depth-2" means the asm adds 2 refs (at loop depth 1 -> weighted 2?).

Actually, gcc's REG_N_REFS is incremented by LOOP_DEPTH... In gcc 2.7.2, `REG_N_REFS (reg) += loop_depth` maybe. Let me check: in flow.c, `REG_N_REFS (i) += 1;` in mark_regs... and in loop.c? Let's not guess; the comment says "+2 refs" and "+3 refs" — probably literally the weighted count added (the asm is inside the do-while for i at depth 2? weighted 3?). Hmm.

Anyway, the practical approach: experiment. Let me look at how previous keepalive MATCHes were done. Read moves.md entries around keepalive MATCH. Let me grep.
