---
ts: 2026-10-22T15:51:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2qIIxtPwFua6x7A4tDNs
---
The scratch has ov_MAIN_012.c and inc/shared. The header was copied into inc/shared/ov/func_8012B4B8.h with my body. Let me dump RTL on ov_MAIN_012.c with DUMP_ROOT under my item dir. The cc1_dumps_tu.sh expects a .c file; -Isrc/shared and its own dir.

But first let me see if the header inside inc has my body. Let me just run the dump.

Actually, before diving into RTL (costly), let me try more empirical candidates. The key insight I want: how to make &m rematerialized. Since the address has 5 uses (copy dest + 3 calls + the Mat32 copy out `*(Mat32*)m`), and target rematerializes it, maybe the target C has *fewer* uses of a single address expression because the last `*(Mat32 *)(obj + 0x34) = *(Mat32 *)m;` uses m as a source (lw from sp) — also the same address.

Hmm what if the target C uses a *different object* for the outgoing copy: `*(Mat32 *)(obj + 0x34) = *(Mat32 *)m;` — that's the same m.

OK let me look at the RTL. It will tell me whether cse created a reg for the address or whether local-alloc did.

Actually — wait. Maybe it's not cse but the *block move itself*: expand_block_move for the destination may need the address in a register if the destination is a MEM and the source is also a MEM... no, it emits stores with `(mem (plus (reg sp) (const 16+k)))`.

Let me just dump and grep. Use DUMP_ROOT=<itemdir>/dumps. Then read the .cse2 and .lreg files, grep for 'D_800AE620' or 's1'/'16'.

The dumps could be big; I'll grep rather than read whole. Delete after.

Let me run.
