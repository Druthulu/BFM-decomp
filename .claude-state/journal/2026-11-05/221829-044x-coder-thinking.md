---
ts: 2026-11-06T05:18:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6ZpKIpDAn942ve9B59CS
---
No virtual stack refs in either. So no stack variables in RTL. Then why vars=16? The .frame comment "vars=16" comes from `get_frame_size()` which is the stack slot area. If no virtual-stack-vars in RTL, frame should be 0. Unless the asm's `(mem:BLK (scratch))` causes `get_frame_size` to be nonzero? No...

Wait, maybe the .s I looked at was for a *different* func_80175820 instance? The header is included at MANY sites, and hdump replaced the include in one TU — but the TU might include the header multiple times (dedup: the same header instantiated at multiple member sites). The .frame at line 4106 is for the specific instance. The orig.c body has `.file 117` — one instantiation. Hmm, but if the header is included once in this TU, fine.

Hmm, the .frame `vars=16` — let me look again at the actual .s for func_80175820 in orig: line 4106 says `.frame $sp,16,$31 # vars= 16, regs= 0/0, args= 0, extra= 0`. And the function has `subu $sp,$sp,16` at the asm position. But no stack accesses. Weird.

OH WAIT. I bet the `subu sp,sp,16` is not the frame adjustment but the asm's expansion! GCC 2.7.2 models `(clobber (mem:BLK (scratch)))`... no.

Hmm, hold on: maybe it's the *prologue* being scheduled late, and `vars=16` because... let me look at the end of the function in orig.s to see the epilogue and whether there's a `addiu sp,sp,16` there. Earlier I saw `subu $sp,$sp,16` at 4130 (mid) and `addu $sp,$sp,16` at 3da4 (mid). The function has no ra save, so the frame is a leaf frame. The prologue `subu sp,sp,16` and epilogue `addu sp,sp,16` were *scheduled* to those positions — that's allowed for leaf frames? Actually reorg/sched can move the sp adjustment if there are no stack accesses! Yes — with no stack accesses, the prologue sp decrement and epilogue sp increment are independent and get scheduled down to the middle. So the .frame says vars=16, meaning the frame IS 16 bytes.

So why vars=16? There must be a stack slot. But no RTL virtual refs... Let me check the *nobar* .s .frame: it said 0. So the asm adds 16 bytes of frame.

Hypothesis: GCC 2.7.2 allocates 16 bytes for the asm's "scratch" memory clobber? Hmm, `(mem:BLK (scratch))` — scratch is `const_int 0`? Not a stack slot.

Let me check GCC 2.7.2 source: `expand_asm_insn` — when there's a clobber of memory, it builds `(clobber (mem:BLK (scratch)))`. And in `function.c`, maybe `assign_stack_local` for `(scratch)`? No.

Alternatively, `-dS` (sched) or `-dL` (lreg) might show. Let me grep the orig .lreg or .sched for "sp" or the frame.

Actually — the `-df` (flow) or `-dg` (greg) dumps show `Frame size`? Let me grep the orig dumps for "frame".
