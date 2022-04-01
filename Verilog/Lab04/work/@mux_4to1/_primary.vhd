library verilog;
use verilog.vl_types.all;
entity Mux_4to1 is
    port(
        in0             : in     vl_logic;
        in1             : in     vl_logic;
        in2             : in     vl_logic;
        in3             : in     vl_logic;
        \out\           : out    vl_logic;
        sel             : in     vl_logic_vector(1 downto 0)
    );
end Mux_4to1;
