---
ts: 2026-10-22T20:09:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vPWJSHsOMxDG2l9kvFL2
---
Target:
- s1 = self, s0 = obj.
- Frame 64. m at sp+16.
- The copy from D_800AE620: target does `lui/addiu a1` then lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); sw to sp+16,20,24; then more... So the source pointer is held in a1 (arg reg!) — not callee-saved. And the dest address sp+16 is rematerialized as addiu a1,sp,16 in each call delay slot.

Key: the target's m-address is not held in a register at all. My candidate holds it in s1 (callee-saved), which forces the extra save/restore.

Why does mine keep the address in a reg? Because the candidate does `RotMatrixX(..., (void *)m)` etc. and `*(Mat32 *)(obj + 0x34) = *(Mat32 *)m;`. The m array address used multiple times; gcc's movstr/address handling picks a pseudo and since it's live across calls, it gets a callee-saved reg. Target rematerializes `addiu a1,sp,16` in each call's delay slot, meaning the address pseudo is a "constant" rematerializable and it dies at each call (because the target doesn't use the address in between; each call sets a1 separately, and the m copy is loaded right before the calls).

Actually in the target, the copy to m happens first (loads from a1 then stores to sp), then calls each with a1=sp+16. The address m+0 (sp+16) is not kept alive across calls: at each call the pseudo is recreated. In my candidate, gcc chose to hold sp+16 in s1 across the calls (as `move a1,s1`). Difference: the pseudo's live range. In the target the address is computed inside the call-arg setup, each time fresh; the target's m is a `Mat32` variable, and calls take `(void *)m`. Hmm.

Actually the key difference in the target: the m array isn't referenced after the copy? It is: after 3 calls, the target does `lw v0,16(sp)...` loads and stores to obj. So m is used after calls. But the address of m for the loads is folded into sp-relative lw offsets, not a register. So the address pseudo only appears as a call argument (3 times). Each use: `addiu a1,sp,16` in the delay slot. So gcc treats the address as rematerializable (sp+16 = frame address constant) and doesn't keep it in a reg. In my candidate, gcc's movstr? Hmm.

The CARRY says: "residual = movstr dest-address pseudo sp+16 held in s1, target rematerialises it per call". And best 19 with `*(Mat32 *)m = D_800AE620;` (a struct copy). The movstr expansion (block move) uses the dest address pseudo; that pseudo remains live across the calls because... maybe because after the movstr the address is reused for the calls? In the target, the movstr of 32 bytes from D_800AE620 to m is expanded inline (loads/stores) — the copy is done as an inline sequence, and the address for the calls is separate.

Hmm, but in my candidate the same expression `*(Mat32 *)m = D_800AE620;` presumably expands inline too, but the address pseudo for the calls got CSE'd with the copy destination address, creating one pseudo live from copy to last call.

Idea: separate the address spells so cse doesn't merge them, e.g., use `m` in the copy and `&m[0]` in the calls? Or cast differently: copy via `*(Mat32 *)m = D_800AE620;` and calls via `(void *)(m + 0)`. That's an identity spelling — "identity address spellings do NOT count as a crack" — but that's about counting as a crack of a launder, not about being allowed. Actually the constraint says identity-statement launders do NOT count as a crack — meaning if I claim MATCH via an identity spelling that's just a lever rename, it doesn't count. Hmm, it means such tricks aren't acceptable as the crack. But we want score 0 with no launder lever. Using different spellings of the same address is arguably a real C difference (it changes cse), but the note says identity address spellings do not count as a crack. So avoid.

Better: figure out the actual C difference that makes the target keep the address rematerialized. Target's m copy: note the loads use a1 as the source pointer and the copy order is 3 loads then 3 stores, repeated. This is the movstr pattern? Actually gcc for `*(Mat32 *)m = D_800AE620;` where Mat32 is a 32-byte struct — expand_block_move generates loads into regs then stores. The order: lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); sw v0,16(sp); sw v1,20(sp); sw a0,24(sp); then next 3... That's exactly block move.

For the address pseudo: in the target, `a1` holds &D_800AE620 during the copy (source address). Then at each call, `addiu a1,sp,16`. So the dest address is rematerialized.

In my candidate, the dest address is in s1. Why? Possibly because I declare `int m[8]` and pass `(void *)m` — same as target presumably. Hmm, the difference might be in how the candidate writes the copy: `*(Mat32 *)m = D_800AE620;` — same as the target? The target probably wrote the copy as a loop or via int assignments. Wait — the target's source (src) has the launder with src[0..7] loads and m assignments (that's the current src body, which scores... the launder version presumably scores 0 by construction, since it's the existing "NEEDED DIFFERS" body). Let me check what score the current src body gives — it should be 0 (it's the baseline that matches, with levers). Actually the levers were added because the function needed them; the src def is the cracked version with levers, so it should score 0.

So in the src body (score 0), the copy is done with src[0..7] scalar loads and m[0..7] assignments, with `src` pinned to $5 and laundered. The address of m appears only in the calls and the final `*(Mat32 *)(obj + 0x34) = *(Mat32 *)m;`. In the target, the copy is a block move from a symbol — not scalar loads. Hmm wait, target loads lw v0,0(a1) ... 3 at a time then stores — that's block move pattern. src's scalar version would give lw v0,0(a1); sw v0,16(sp); lw... alternating. Unless gcc's scheduler groups them (sched1/sched2 may interleave). Actually with sched, the 3 loads may be grouped. Hmm.

Anyway, the prior coder found `*(Mat32 *)m = D_800AE620;` gives best 19, residual is the address in s1. The movstr (block move) dest-address pseudo is held in s1 because... In gcc's movstr expand, the dest address pseudo is generated and remains as a value; if the same address value is later needed for calls, cse merges.

How to prevent: use a distinct expression for the copy destination vs the call args, but not an "identity address spelling". Options:
1. Copy via a pointer variable: `Mat32 *mm = (Mat32 *)m; *mm = D_800AE620;` then calls with `(void *)m`. That's a separate pseudo but cse could still merge.
2. Make m a local struct: `Mat32 m;` then calls `(void *)&m` and `*(Mat32 *)(obj+0x34) = m;`. Hmm, same.
3. Have the address in a variable that is set just before the calls (reassignment), e.g., `mp = (int *)m;` after the copy. Then cse: mp = &m, and the calls use mp. But the movstr's dest pseudo is separate from mp; cse could still merge them since &m is a constant expression (address of local). In the target it clearly didn't merge, or it did merge but rematerialization was chosen.

Actually the residual in mine: `addiu s1,sp,16` once, `move a1,s1` 3 times. The target: `addiu a1,sp,16` 3 times. Both have the same value; the difference is register pressure/remat decision. GCC rematerializes a value if it's "rematerializable" and the cost model says so. The pseudo here is an address-of-local constant, which is rematerializable. Whether it's kept in a register depends on local-alloc/global-alloc: if it's live across calls, global-alloc assigns a callee-saved reg (s1) — because the pseudo was created before the calls and live through them. The target must have the pseudo created fresh at each call (3 separate pseudos), each dying at its call, so local-alloc gives each a1 (hard arg reg).

How does the target get 3 separate pseudos? If the C writes each call with a different spelling: `RotMatrixX(x, m); RotMatrixZ(z, m); RotMatrixY(y, m);` — each use of `m` decays to address; cse merges them into one pseudo normally. Unless cse doesn't merge addresses of locals across calls? Hmm, cse does merge address constants.

Wait, maybe the target's source is different: perhaps it passes `m` as `(void *)m` but the copy is done with a separate function-like or through a different object, so that the address pseudo used by calls is not live across the calls... Actually consider: the address pseudo's live range in target: created before the first call, used at call 1, call 2, call 3, and maybe the final loads are sp-relative. If cse merged all three call uses into one pseudo, its live range spans 3 calls → would be allocated a callee-saved reg, not rematerialized each time... unless global-alloc decides to rematerialize because it's cheap and pressure is high. GCC (2.8 era) does rematerialize address constants when the pseudo doesn't get a hard reg or when it's live across calls? The behavior "move a1,s1" vs "addiu a1,sp,16" is about whether the pseudo got a register.

Hmm — the difference could be that in the target, the pseudo holding sp+16 dies before the calls? No, it's used in the delay slots.

Key insight: the target frame is 64 with s1=self, s0=obj; two callee-saved regs. Mine has s1=address, s2=self? Actually residual says mine has s2 where target has s1 — mine uses s0=obj, s1=addr, s2=self: three callee-saved regs. So the address is the extra one. If the address weren't live across calls, no extra reg.

So how did the target avoid it? In the target, the address value sp+16 is a *constant* pseudo. GCC's global-alloc can "rematerialize" constants instead of spilling them. But it wouldn't assign a callee-saved reg at all if the pseudo is only live between... Hmm.

Alternatively, maybe in the target's C the calls use `&m[0]`, `&m[1]`... no, all sp+16.

Let me think about gcc's behavior: `addiu a1,sp,16` in each delay slot means the pseudo was *not* assigned a register; each use reloads the constant. That's rematerialization in reload: the pseudo is an address constant (frame pointer + const) and reload rematerializes it at each use, likely because it was NOT allocated a hard register (spilled) or because it's an "eliminable" address. If a pseudo is live across a call and global-alloc spills it, reload would rematerialize the address at each use. Yes! That's it: the pseudo is live across calls, global-alloc could not give it a callee-saved reg (or chose to spill it), and reload rematerializes it. In my candidate global-alloc gave it s1.

So the difference is register pressure/allocation priority. Target has 2 callee-saved regs (s0,s1) plus the address pseudo spilled. Mine has 3. Why did mine allocate a callee-saved reg? Because... global-alloc counts refs; the address pseudo has 4 refs (3 calls + copy?). Hmm.

Wait: in the target, does the movstr use the address pseudo? Target's block move stores go to `16(sp)`, `20(sp)` etc. — direct sp-relative stores, no dest-address pseudo (block move stores use sp offsets). And the final Mat32 store to obj loads from sp+16.. so no address pseudo. So the address pseudo appears ONLY as call args (3 uses). Live from before call 1 to call 3 (across calls). With 3 uses and live across calls, global-alloc would want a callee-saved reg... but target spills it. Hmm, maybe because there are other more important pseudos and the address is "cheap" (rematerializable), global-alloc's `allocno` priority or `REG_N_CALLS_CROSSED`... 

In my candidate, why 4 refs? The copy `*(Mat32 *)m = D_800AE620;` — maybe in my candidate gcc expands the struct copy as movstr (call to memcpy? no, inline) using the dest address pseudo: loads into regs, stores via the address pseudo (addiu base then sw 0(base)...). Actually the diff showed my insn 9: `addiu s1,sp,16` right at the start of the if — before the copy loads? Let me look at my candidate's disassembly. Let me use cand.sh to get it.

Then the address pseudo has uses in the copy (8 stores?) plus 3 calls = many refs → wins s1.

So the fix: make the copy not use the m-address pseudo while the calls do. The target's block move uses sp-relative stores directly (no base reg), which happens when the dest is a local array accessed by constant offsets — movstr expansion with constant dest offsets. That's what `*(Mat32 *)m = D_800AE620;` should do if the dest is known to be at a fixed frame offset. But in my candidate, the frame offset is known only after reload... movstr emits `(mem:BLK (reg))` with a pseudo address; then reload/flow... Hmm, target's stores are direct sp offsets, so movstr used the frame address directly.

Difference: in my candidate I declared `int m[8]` and cast to Mat32*. Maybe declaring `Mat32 m;` (struct type) makes the address an ADDRESSOF of a struct → different handling. Let me check what Mat32 is.

Actually, let's look at the variants tried. c_struct.c uses `int m[8]` + `*(Mat32 *)m = D_800AE620;`. The gen_* files are old. Let me look at c_d1..c_d5 (latest).
