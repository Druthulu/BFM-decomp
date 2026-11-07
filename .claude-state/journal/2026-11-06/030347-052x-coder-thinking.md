---
ts: 2026-11-06T10:03:47Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8uRPsrbEKCyX69yYbzbT
---
Key: "Register 75 used 2 times across 7 insns in block 0; crosses 1 call". So r75 is in block 0 (local-alloc eligible) AND crosses a call. Local-alloc assigns it s0 (16). 

Block 0: insn 4..60. The call is inside block 0! So the call does NOT split the block here. Wait, line 446 said a block starts after a call. But block 0 spans insn 4-60 and "crosses 1 call". Hmm, so the call is within block 0 and does not end it? Let me re-read flow.c lines 440-460.

Actually line 446-450:
```
/* A basic block starts at label, or after something that can jump. */
if (code == CODE_LABEL
    || (code == INSN && ...)
    || (prev_code == JUMP_INSN)
    || (prev_code == CALL_INSN)
    ...)
```
Hmm, so after a call a new block starts. But the dump says block 0 has insns 4..60 with a call inside. Maybe the call is a `CALL_INSN` but the *basic block* boundary logic in this version only splits after calls in certain conditions? Let me look at lines 440-465.
