---
ts: 2026-11-06T03:28:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PfwjTGcd7i9eWrwwpZKG
---
canon_hash for MEM: hashes based on the address and sets `hash_arg_in_struct` (a global flag) — but the hash value itself doesn't include MEM_IN_STRUCT_P. And `exp_equiv_p` (the first grep found nothing for MEM?) — let me look at exp_equiv_p's MEM handling. The grep returned nothing for the exp_equiv_p section (maybe the function name differs). Let me search "exp_equiv_p (x, y" and look at MEM.

Actually, the hash includes the MEM code and address; the in_struct flag is tracked separately via hash_arg_in_struct for invalidation. So a struct-typed load and a non-struct load of the same address hash the same → cse merges. So the struct-typed second access won't help.

Hmm.

Let me try the local-pointer variants (t1/t2) and a few others, then likely WALL. Time: item 5 at ~25 min.

Actually — maybe the key is different: the barrier is a memory clobber; without it, cse merges the global loads. But maybe the original C had the *second* load as part of a different expression that cse couldn't merge: e.g., the target's second load at 52d4-52e0 is `lui v0; lw v0; lhu v0,18(v0)` and the store `sh v0,42(s0)` is in the bnez delay slot. The first load at 52b4-52c0. Both are the same expression.

What if the original C's second use was `*(u16*)((u8*)D_80126B78 + 0x12)` where D_80126B78 is loaded *after* the store in the source, which it is. cse forwards because it thinks the store doesn't clobber the global.

To make cse think the store clobbers, the store must set all=1 (address not PLUS, not in-struct). We found cse folds pointer variables into PLUS. Hmm, but does it? The s1 dump showed the store address as... let me actually look at s1's store RTL properly. My earlier grep was confusing. Let me directly grep for the store to (reg q) in s1's .rtl.

Let me dump s1 fresh and print the region around the store.
