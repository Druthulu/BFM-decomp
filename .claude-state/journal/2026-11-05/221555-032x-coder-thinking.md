---
ts: 2026-11-06T05:15:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ntb98ZDozSKghbOADuip
---
Now I see: `.frame $sp,16,$31 # vars= 16, regs= 0/0, args= 0, extra= 0`. And `subu $sp,$sp,16` right at the `#APP #NO_APP` asm position. Wait, but vars=16. So there's a 16-byte local variable area, but the prologue doesn't do `subu sp,sp,16` at the top; instead it's placed at the asm? Hmm, that's odd. Actually maybe the function's frame is 16 (vars=16) and the `subu sp,sp,16` is the prologue adjustment, but it got *scheduled* down to the asm position! And the epilogue's `addu sp,sp,16` at the end.

Why vars=16? Because... the asm with memory clobber? No, vars=16 means 16 bytes of stack variables. But the C function has no locals besides pointers. Hmm.

Wait — maybe the barrier asm creates a 16-byte "var" area as an artifact. That's bizarre but plausible in GCC 2.7.2: an asm with a memory clobber might make `get_frame_size` nonzero? Hmm.

Actually! I bet the `.frame vars=16` is because the function needs a place for the asm's memory clobber? No...

Hold on, let me reconsider. Maybe hdump's replaced body has the extern declarations inside the function, and the struct types... no.

OK here's another thought: maybe the current source body, when inlined into the includer TU, has the `extern` decls and the compiler... no.

Let me test directly: does an empty asm with memory clobber alone produce a 16-byte frame? Let me write a tiny test C and compile it with the project's compiler? We don't have a direct compiler command allowed (must go through bin/sc.sh). Hmm, but hdump.sh compiles a TU with tools/cc1_dumps_tu.sh. I could create a tiny .c and use cc1_dumps_tu.sh? That's a shared helper allowed (tools/cc1_dumps_tu.sh). It takes a .c. Let me do that in my scratch dir.

Actually, this is a rabbit hole. Let me focus: the key artifact is `subu sp,sp,16` around the asm. Since it's the *prologue* adjustment scheduled late (vars=16), it means the function has a 16-byte frame. Why? Let me check the barrier-free .frame: let me dump the nobar body too. If nobar has frame 0 and barrier has frame 16, then the asm creates 16 bytes of vars. Then no C can reproduce... unless we declare a 16-byte local that gets spilled? No — a local array that is unused would be eliminated; one that's used would need stores.

Hmm, but wait: maybe the 16 bytes are `current_function_args_size`? The comment says args=0, vars=16.

Let me look at the RTL for the asm insn to see if there's a stack slot. Search for "asm_operands" near the function in orig.i.rtl — line 28418. Let me look at that region.
