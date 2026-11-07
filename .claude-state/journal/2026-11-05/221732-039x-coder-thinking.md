---
ts: 2026-11-06T05:17:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zSQ1VdOS703jJE7oym65
---
The minimal probe shows frame 0 for both g and h — so a bare `__asm__("" ::: "memory")` does NOT create a frame. So the 16-byte vars in func_80175820 comes from something else!

What else differs? The body has struct-typed externs `S_AE7BC_80175820_80175820 D_800AE7BC[]` and `S_AF634_...`. Those are structs; maybe passing struct members by value creates temps? But nobar has the same decls and frame 0.

Hmm, so what does the asm change to create vars=16? In the orig body, the asm is `__asm__("" ::: "memory");`. In nobar, removed. Everything else identical. Yet orig frame=16, nobar=0.

Wait — maybe the difference isn't the asm but the *line numbers/scheduling*: the frame size is computed before scheduling, so no.

Unless: the asm memory clobber forces some pseudo to be spilled → 16 bytes vars! Yes! A memory clobber makes all memory-backed values need reloading; it may increase register pressure such that some pseudos spill. But `vars=16` and no loads/stores to sp? Let me re-check the orig asm for stack accesses: in the disassembly of the object, I saw `addiu sp,sp,-16` and `addiu sp,sp,16` but no `sw/lw` at 0(sp)... Let me look at the orig .s again: after `subu $sp,$sp,16`, the code uses `$3` (v1), `$2`, `$4`. No stack load. So the 16 bytes are unused.

Hmm, could it be `current_function_outgoing_args_size`? The .frame comment: `vars= 16, regs= 0/0, args= 0, extra= 0`. So vars=16.

Wait, maybe the frame is reserved for the asm's memory operand? The asm is `__asm__("" ::: "memory")` — no operands. 

Hmm, let me look at the RTL for the function. Let me find the function in orig.i.rtl by looking for the asm_operands/v ("") ("") with a `(mem/s:SI` store right before. Let me search for asm_operands/v ("") ("") occurrences.

Actually a better approach: compare the orig and nobar RTL dumps around the function. Let me extract the function's insns. The RTL dump doesn't label functions clearly? It might have `;; Function func_80175820`. Let me grep.
