library verilog;
use verilog.vl_types.all;
entity counter_sel is
    port(
        sel             : in     vl_logic;
        dout            : out    vl_logic_vector(3 downto 0);
        rst             : in     vl_logic;
        clk             : in     vl_logic;
        a               : in     vl_logic_vector(3 downto 0);
        b               : in     vl_logic_vector(3 downto 0)
    );
end counter_sel;
