---
ts: 2026-10-17T04:33:50.172Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5605ba96cc5ff027
model: claude-opus-5-5[1m]
effort: medium
turnId: 0c792287-f11f-4848-8566-c39a9bb058a0
---
I'm checking func_8016BCC0's short calls to func_8016BF50 and similar functions — since $a0 already holds param_1/arg0 unchanged, the call is effectively just passing that same value through, though the compiler might still need to preserve it in a saved register across the call.

For the dedup extension, I need to update the extern declarations to match the shared header's signature, but I'm realizing the function-pointer casts used for the short calls will still conflict with that change.

Checking the old gcc semantics — block-scope externs seem to persist to file scope, but since this compiles cleanly today, I'll trust the current behavior rather than second-guess it. Now I'm examining what the restruct callee operation does with the shared signature: since the header already defines func_8016BF50, the alias lookup path won't trigger because def_name isn't empty.

With a single matching definition, the tool would leave the signature as-is and instead rewrite every decl_site across the 132 includer files to the ANSI form, including any K&R-marked externs. That rewrite risks breaking short calls like `func_8016BF50();` into "too few arguments" compile errors, which would cause the whole batch to be refused — so I'm now checking whether ov_SC07_006/007/010/011 are excluded from that includer binary set since they don't actually include the header.

I'm trying to pin down the real deliverable: get a single ANSI prototype for func_8016BF50 applied consistently everywhere, replacing all K&R-style declarations and truncated calls across the ov_SC07_* files. Given these K&R sites are byte-verified, I suspect the tool will refuse automatic rewrites, so I want to test this manually first on ov_SC07_006's jr_8016AE5C site before attempting it broadly.

I'm updating the declarations to use the extern ANSI prototype with an explicit s32 parameter, fixing the short calls to pass the actual argument instead of calling with no arguments, and replacing the function-pointer cast calls with direct calls using the parameter. The alias definition stays as-is since it already matches, though its declaration will later get replaced once the include is extended.

I'll verify on one TU whether using ANSI declarations with explicit arguments preserves the expected bytes before applying the fix across the rest.
