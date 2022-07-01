library verilog;
use verilog.vl_types.all;
entity MUX_ALU_1bit is
    port(
        dataOut         : out    vl_logic;
        e1              : in     vl_logic;
        e2              : in     vl_logic;
        e3              : in     vl_logic;
        e4              : in     vl_logic;
        sel             : in     vl_logic_vector(1 downto 0)
    );
end MUX_ALU_1bit;
