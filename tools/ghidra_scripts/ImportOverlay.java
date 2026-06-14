// ImportOverlay.java — headless postScript: load the T6b-proven resident blob + one location
// overlay into the program at their byte-verified vaddrs, so the overlay/resident code becomes
// disassemblable in Ghidra. The MCP tools cannot create memory blocks / bulk-load file bytes, so
// this is done headless (analyzeHeadless opens the project directly and saves on completion).
//
//   ~/ghidra_12.1_PUBLIC/support/analyzeHeadless ~/bfm-decomp/ghidra bfm \
//     -process SLUS_007.26 -noanalysis \
//     -scriptPath ~/bfm-decomp/tools/ghidra_scripts -postScript ImportOverlay.java
//
// Idempotent: re-runs write into the blocks created on the first run.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import java.io.ByteArrayInputStream;
import java.nio.file.Files;
import java.nio.file.Paths;

public class ImportOverlay extends GhidraScript {
    public void run() throws Exception {
        String home = System.getProperty("user.home");
        // {block name, vaddr, extracted file}
        String[][] targets = {
            {"residentBlob",  "0x800CEDF8", home + "/bfm-decomp/extracted/MAIN.CD.dir/FILE_010.dir/1.1"},
            {"ovl_tutForest", "0x80128158", home + "/bfm-decomp/extracted/SC01.CD.dir/FILE_077.dir/0.4.dec"},
        };
        Memory mem = currentProgram.getMemory();
        println("BFMOVL == existing memory blocks ==");
        for (MemoryBlock b : mem.getBlocks())
            println("BFMOVL   " + b.getName() + " " + b.getStart() + "-" + b.getEnd()
                    + " init=" + b.isInitialized());

        for (String[] t : targets) {
            String name = t[0];
            Address addr = toAddr(t[1]);
            byte[] bytes = Files.readAllBytes(Paths.get(t[2]));
            MemoryBlock existing = mem.getBlock(addr);
            if (existing == null) {
                mem.createInitializedBlock(name, addr, new ByteArrayInputStream(bytes),
                        bytes.length, monitor, false);
                println("BFMOVL CREATED " + name + " @ " + addr + " len=" + bytes.length);
            } else {
                println("BFMOVL into existing block '" + existing.getName()
                        + "' init=" + existing.isInitialized());
                if (!existing.isInitialized())
                    mem.convertToInitialized(existing, (byte) 0);
                mem.setBytes(addr, bytes);
                println("BFMOVL WROTE " + bytes.length + " bytes @ " + addr);
            }
        }
        // sanity: read back first 8 bytes at each vaddr
        for (String[] t : targets) {
            Address a = toAddr(t[1]);
            byte[] c = new byte[8];
            mem.getBytes(a, c);
            StringBuilder sb = new StringBuilder();
            for (byte x : c) sb.append(String.format("%02x", x));
            println("BFMOVL VERIFY " + a + " first8=" + sb);
        }
        println("BFMOVL done.");
    }
}
