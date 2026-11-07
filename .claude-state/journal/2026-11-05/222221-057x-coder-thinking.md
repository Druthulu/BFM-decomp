---
ts: 2026-11-06T05:22:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7BqgZlUSSJyc6xZGLd4u
---
Still frame 0. So the clobber + global struct doesn't create a frame. Something else in the real function.

Wait — maybe the 16-byte frame in the real body comes from the `!FAKE` barrier being inside a block where a `struct` value is used? Let me look at the exact real source again: the body has `extern S_AE7BC_80175820_80175820 D_800AE7BC[];` etc. The types S_AE7BC... are defined in the includer TU. Maybe the struct is large and `D_800AE7BC[*q]` involves a struct temp? But nobar is the same and frame 0.

Hmm, the ONLY difference between orig and nobar is the two asm lines. And orig frame=16, nobar=0. My probe with a similar shape gives 0. So the real function has something that interacts with the asm to make a frame.

Let me bisect the real body: take orig and move the asm to different positions, and check frame. Let me test: asm at the very end of the function.

Actually, easier: let me look at the `-dl` (lreg) dump of orig for the function and see if there's a stack slot quantity. Search for "stack" in the lreg function region. Let me look at the greg dump for the function's stack slots: `(mem:SI (plus:SI (reg/f:SI 29)` or `(plus:SI (reg:SI 29)`. Let me grep the greg region for "29".
