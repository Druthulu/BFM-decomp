---
ts: 2026-10-22T21:19:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vjyPEBOrwkneWIuXcfEG
---
In w2, arm1 is at 144c-145c: sh 32; li 1536; sh 34; j 14c4; li -80 (delay). Then at 14c4 the rest: sh zero,36; sh zero,46; sh v0,48.

So cross-jump DID merge the *tails* (the last 3 stores: sh zero,36; sh zero,46; sh v0,48) between arm1 and arm3 — a partial merge (cross-jump merges the maximal common suffix). Because arm3's last store is `(subreg:HI (reg:SI k))`... wait no, if that differed, the suffix would only be sh zero,36; sh zero,46 — hmm, it merged 3 insns: sh zero,36; sh zero,46; sh v0,48. So the final store patterns must still be equivalent (k's SI reg renamed). Hmm, cross-jump's rtx_renaming allows reg-to-reg mapping but not reg-to-const. In arm1 the last store is a const (movhi_internal2 with const), in arm3 it's a reg (movhi_internal). Those should NOT be equivalent... unless by jump2 time, cse2/combine folded k into a const in HImode.

Wait: with `s32 k = -0x50`, the store `unk30 = k` where k is SI → truncation to HI. Combine may fold `(subreg:HI (reg:SI k))` where k's value is known... hmm.

Let me instead look at what arm3 looks like in w2's dump: at 14c4 region. Let me see lines 72-95.
