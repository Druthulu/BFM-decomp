---
ts: 2026-11-06T10:02:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WztY88aeldb8YVIfixKi
---
This is the .lreg (local alloc done). The debug lines "Register 74 used 4 times across 8 insns in block 2; dies in 2 places" — that's the global-alloc dump (-dl? no). Hmm, actually these "Register N used X times across Y insns in block Z" lines are global-alloc's allocno dump (-dg). And .lreg has local-alloc output.

Anyway: Register 74 = t? "used 4 times across 8 insns in block 2; dies in 2 places". Register 75 used 2 times across 8 insns in block 2. These are global allocnos?! That means t and tb are treated as global (not block-local) because they're used in block 2 only but the dump says "in block 2" for global alloc. Hmm.

Wait, these are from global-alloc (-dg) which is appended to .lreg? The .lreg dump is written by local-alloc (pass -dl) and .greg by global. Hmm.

Let me look at the actual local-alloc dump file for -dl. Which file? The list: dl.i.combine, .cse, .cse2, .dbr, .flow, .greg, .jump, .jump2, .loop, .lreg, .rtl, .sched, .sched2. And the suffix -dl writes .lreg. So dl.i.lreg = RTL after local-alloc. The "Register 72 used 16 times..." lines near the top might be from global-alloc? No, they appear at line 3485+ which is the function dump.

Let me search in dl.i.lreg for the block containing the loads (76(s0), 84(s0)). The RTL is verbose. Let me grep for "76" and "84" in the function region.

Actually, more efficient: the local-alloc debug output with qtys is printed to stderr when -dl is given? It was empty. In GCC 2.7.2, `-dl` sets `local_alloc_dump`; block_alloc prints to `rtl_dump_file` if `local_alloc_dump`. Hmm, the qty table isn't printed.

Let me instead directly reason via the .lreg RTL: find the insns with (reg:SI 74) etc. and their assigned hard regs. Actually the dump after local-alloc shows `(reg:SI 74)` replaced? No, reg_renumber is applied at final.

Alternative approach: skip the deep analysis. I have a working 7-score. Let me try more C variants to flip t/tb:
- Swap which variable gets unk4C vs unk54: e.g., assign tb first then t? That changes code order.
- Make t's declaration `s32 t = ...` init at decl? Init at decl for a local in a block.
- Try `s32 tb;` declared before `s32 t;`.
- Try making the values `u16` (widths).
- Try `volatile`? no, that's a barrier-ish lever (not allowed? volatile is not in the kinds list but it's a "launder"? The kinds are barrier,pin; volatile would be a new lever of another kind — forbidden "no new lever of any kind").

Let me think about what flips v0/v1 in local-alloc. qty priority: shorter life → higher priority → v0. In nopin, t got v1, tb v0. So tb has higher priority than t, i.e., tb is "shorter-lived" or more refs. tb: 2 refs, life 5. t: 4 refs, life 7.

pri = floor_log2(nrefs)*nrefs*size/life:
tb: floor_log2(2)=1 → 1*2*1/5 = 0.4
t: floor_log2(4)=2 → 2*4*1/7 = 1.14
t higher. But observed t=v1. So my model is wrong, OR t and tb are not block-local qtys (they're global allocnos!). The dump said "Register 74 used 4 times across 8 insns in block 2" — that's a global allocno. If t/tb are GLOBAL (because the compiler put them in different blocks?), then global-alloc decides.

Why would they be global? Because the `if ((cnt & 7) == 0)` block... they're only in that block. Unless the compiler duplicated the block (e.g., due to the `if` structure) or the variable is live across the block boundary.

Hmm, actually maybe t is used across blocks because `t` is assigned in the block and... no.

Wait — "block 2" in global-alloc dump means the allocno is confined to block 2 but still a global allocno (allocated by global-alloc) because it's a pseudo that local-alloc couldn't handle? Local-alloc only handles pseudos with reg_qty == -2 (local). Pseudos used in multiple blocks or with certain properties are global.

Let me check: is block 2 the `if ((cnt&7)==0)` body? The function has blocks 0..N. Likely.

Global-alloc order: allocno_compare by refs*size/live_length. t: nrefs=4, live 8 → 4*1/8=0.5; tb: nrefs=2, live 8 → 0.25. t higher → gets lower reg. But observed t=v1...

Unless "used 4 times across 8 insns" for register 74 and "2 times across 8 insns" for 75. So t=74 (4 refs), tb=75 (2 refs). Global-alloc should give t the lower reg among {v0,v1}? But v0/v1 are caller-saved and global-alloc may not allocate caller-saved to long-lived... 

Hmm wait, these could be different variables. Let me look at the global-alloc dump section for this function to map pseudo→var. The lines "Register 72 used 16 times..." — 72 is `s0`? s0 crosses 2 calls (used across 2 calls) → yes, s0 = reg 72 (16 times, crosses 2 calls). reg 73 used 2 times across 5 insns — maybe `p`? no p used more. Hmm.

Let me look at the greg dump which is the final global allocation with "Register X in Y".

Actually, let me use tools/alloc_table.py which the brief mentions ("tools/cc1_dumps_tu.sh + tools/alloc_table.py (TU dumps)"). Let me check its usage.
