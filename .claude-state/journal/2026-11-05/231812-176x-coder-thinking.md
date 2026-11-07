---
ts: 2026-11-06T06:18:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fhJwpj8wCjSvnCyzCHVM
---
s5's global allocnos: 72 in $16 (s0), 73 in $2.

reg72 = the parameter (in s0). reg73 = a local value (in $2).

So there's only ONE callee-saved allocno (reg72 = the parameter). Good.

The unk100 load uses reg72 (in $16). But the asm shows `lh v0,256(a0)`. Hmm! So reg72 is in $16 but the load uses a0?

Wait — maybe the load at 2938 uses a0 because a *different* pseudo (a copy) is used. Let me look at the RTL around the last block.

Actually, maybe the `move a0,s0` is a copy of reg72 into a0 for the call, and gcc's regmove rewrote the load's base to a0.

Let me look at the s5 .rtl for the last block.
