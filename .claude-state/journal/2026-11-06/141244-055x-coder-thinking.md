---
ts: 2026-11-06T21:12:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SN6eVHKz61xouNBwUqVR
---
-greg not supported. OK. 

Let me take a totally empirical approach and generate many variants, scoring them. The score is cheap (one compile each). Let me think of real-C moves that raise e's refs.

Actually, here's an idea I haven't tried: use `e` in the lim load WITHOUT changing the address, by loading lim through a *different* typed pointer but referencing e via a comparison or something. No.

Alternative: raise e's refs by using it as the base for the condition load TWICE with a store in between? No store.

Wait — maybe I can use a union or a struct so the "symbol address" is materialized once into e and used twice via two different member accesses that cse keeps separate? 

Hmm, what about this: make the two halves of the || condition read through e but at different types so cse doesn't merge:
- first: `*(s16 *)((u8 *)e + off + 2) == 0`
- second: `((s16*)((u8*)e + off))[1]` — same.

What if we read it as a u16 and then as s16? The value is compared ==0 and passed to a function. Different modes might not merge. But it changes the load type (lhu vs lh). Target uses lh (sign-extend). So no.

Let me reconsider the whole approach. The target was generated from a C body with barrier+launder. We need a *different* C body (real C) that compiles to the same object. This is a "crack". Sometimes the crack is a structural rewrite.

Maybe the right crack is to restructure so e naturally has more refs. For example, split the condition into two separate ifs:
```
if (t < lim) {
    if (*(s16 *)((u8 *)e + off + 2) == 0) {
        idx = -1;
    } else if ((((s32(*)(s32))func_80029178)(*(s16 *)((u8 *)e + off + 2)) & 0xFF) == 0) {
        idx = -1;
    }
}
```
This changes the control flow (target has a single || with a branch). Probably changes code.

What about assigning e to a second variable that's used for the lim load, so e has 2 refs:
```
s16 *e2;
e = (s16 *)D_801E8F78;
e2 = e;               // copy, e used here (2nd ref)
lim = ((s16(*)[2])e2)[idx][0];
... condition uses e ...
```
Hmm, this makes e used twice (def, use in copy) and e2 used for lim. But combine would propagate e2=e, and then lim via e → address sharing (146). 

Alternatively:
```
e = (s16 *)D_801E8F78;
lim = D_801E8F78[idx][0];
... condition uses e ...
```
e has 1 use. To add a 2nd use that doesn't affect code: use e in a comparison that's always true and folded? Folded away → no ref.

Hmm.

What if we make e's assignment depend on `idx` so it's not REG_EQUIV, e.g.:
```
e = (s16 *)D_801E8F78;
```
can't.

Let me look at this from a completely different angle: maybe the REG swap can be fixed by changing the *order of the a0/a1 preference* through a copy preference. Global-alloc has "preferences" from copies. If we introduce a copy that prefers e→a0, the allocator would give e a0. E.g., if e is copied to/from a0 somewhere. But we can't pin.

What about the fact that `func_80029178` takes its arg in a0. The condition's loaded value (reg 108) is moved to a0 at insn 99 before the call. That's a copy preference for reg 108→a0. Not e.

Hmm.

Let me try the simplest structural thing: assign `e` AFTER the `if (t < lim)` check but the condition uses it... no.

Wait, actually — what if we move `off = idx * 4;` to AFTER `e = ...` and the lim load, i.e., right before the condition? Then off's birth is later (shorter live), higher priority → off gets a0 (worse). No.

What if we move `off = idx*4` to the very top, before the call? idx not available.

Let me try making off's live range longer by using off in the `if (idx >= 0)` branch in a folded way. For example, `p = D_801E8F98[idx];` — could write `p = *(void **)((u8*)D_801E8F98 + off)`? No, that uses off as the index for D_801E8F98 (different array), changes code.

Alternatively, use off in a `if (off < 0) {}` after the block — dead but flow might keep? Flow removes it (off known >= 0? maybe not). Actually `if (off < 0)` on an s32 that's idx*4 where idx is from u8 (0..255) → known non-negative? idx is s16 loaded via lbu (zero-extend) → 0..255. off = idx*4 → 0..1020, known >= 0. Flow/jump might fold `off < 0` to false. If not folded, it adds a branch. Bad.

Hmm.

Let me look at the actual global-alloc decision mechanism to understand why off wins. Since -greg is unavailable, maybe I can add a temporary printf to global.c? No, I can't modify tools/.

Wait — maybe I can build a modified cc1? No, that's out of scope and tools are read-only.

Let me instead use the .greg dump's ";; Register dispositions" — the .greg dump file (cand.i.greg) might include the dispositions at the end. Let me grep.
