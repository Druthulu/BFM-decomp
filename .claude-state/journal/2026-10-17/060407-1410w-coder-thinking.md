---
ts: 2026-10-17T12:04:07.293Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
I'm thinking about what it means for two references to point to the same symbol versus different offsets or expressions targeting the same underlying address, like comparing a direct symbol reference against an arithmetic variant such as a symbol plus or minus a constant.

I check whether a constant integer address would compile to the same instruction bytes, but the ori vs addiu mismatch rules that out. That leads me to consider expand_call: if the argument is a constant passed in a hard register, it's loaded directly at the call site rather than through a pseudo, so after the call the register gets clobbered, and the later store to D_801D59F0 would need a fresh pseudo for cse to track.

Looking at b.c's actual output, gcc precomputes the symbol into a pseudo (lui/addiu into s0, then move into a0) rather than loading directly into a0, which lets cse later substitute the cheaper pseudo register for the repeated constant address. So I'm hunting for a natural source construct that would force gcc to create that shared pseudo -- maybe passing the array's address directly as a memset argument, or accessing a struct field at offset 0 within D_801D59F0.

I'm also wondering if the original code used a pointer variable assigned to the symbol, since cse would merge that assignment with later references to the same address, or whether a label breaking the basic block could be what prevents cse from substituting in other cases.

After about six attempts in this class, I'm considering cheap tricks: maybe a contrived expression like subtracting then forcing back to the same address counts as a "lever" per the brief's definition. Another natural option is that the original call might have cast the argument to a different integer type, which would still produce the identical symbol_ref rtx and thus not break cse.

I'll test the lever variant and skip reordering the struct assignments before the memset since that would clobber the data.
