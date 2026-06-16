// DefineFunctions.java — headless: disassemble + create a function at each address listed in
// ~/bfm-decomp/.run/<prog>_funcs.txt (one 0xADDR per line). Raw-binary auto-analysis (no entry
// points) finds only the reachable subset of functions; splat's linear sweep finds them all, so
// this seeds the Ghidra program with splat's VALIDATED boundaries — mechanical, NOT manual RE.
// Used in Phase 10 to complete the `resident` program (23 auto-found -> all 143). analyzeHeadless
// commits + saves on a clean exit (run WITHOUT -readOnly).
//
//   analyzeHeadless ~/bfm-decomp/ghidra bfm -process <prog> -noanalysis \
//     -scriptPath ~/bfm-decomp/tools/ghidra_scripts -postScript DefineFunctions.java
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class DefineFunctions extends GhidraScript {
    public void run() throws Exception {
        String prog = currentProgram.getName();
        Path in = Paths.get(System.getProperty("user.home"), "bfm-decomp", ".run", prog + "_funcs.txt");
        if (!Files.exists(in)) { println("DefineFunctions: no list at " + in); return; }
        List<String> lines = Files.readAllLines(in);
        int created = 0, existed = 0, failed = 0;
        for (String ln : lines) {
            ln = ln.trim();
            if (ln.isEmpty()) continue;
            long off = Long.parseLong(ln.replaceFirst("(?i)^0x", ""), 16);
            Address a = toAddr(off);
            try {
                if (getFunctionAt(a) != null) { existed++; continue; }
                if (getInstructionAt(a) == null) disassemble(a);
                Function f = createFunction(a, null);
                if (f != null) created++; else { failed++; println("  no-func @ " + a); }
            } catch (Exception e) { failed++; println("  fail @ " + a + ": " + e.getMessage()); }
        }
        println("BFMDEF created=" + created + " existed=" + existed + " failed=" + failed
                + " total_listed=" + lines.size()
                + " program_funcs_now=" + currentProgram.getFunctionManager().getFunctionCount());
    }
}
