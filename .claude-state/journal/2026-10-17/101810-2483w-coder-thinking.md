---
ts: 2026-10-17T16:18:10.410Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac899e71a72e1a646
model: claude-opus-5-5[1m]
effort: medium
turnId: 7b755c42-d9e9-446c-8f08-faa68444d116
---
I'm comparing branch structures between my version and the target, noticing the compiler seems to be reorganizing the then/else branches into a delay-branch optimization where the bnez instruction absorbs the addiu into its delay slot.

In the target, the then-block loads into v0, copies to v1, then subtracts to produce v0 again — two instructions instead of my single addiu, which suggests register allocation created a separate pseudo for the copy rather than reusing the same register directly. I'm trying to figure out why gcc would introduce this extra move: it implies the loaded pseudo and the result pseudo can't share a register, likely because the loaded value stays live past the point where the result is computed.

Maybe the original source is something like `if (v0 = this->unk104) v0 = v0 - 1`, where the test and the decrement involve values spanning blocks in a way that local/global register allocation doesn't coalesce into one register.

Alternatively, if both branches independently assign to the same struct field, a crossjump optimization might merge the duplicate stores into a shared join block, which could explain the jump-to-store pattern I'm seeing in the target code, something like decrementing the field if nonzero or otherwise setting it to a random value offset by 8.
