library verilog;
use verilog.vl_types.all;
entity counter_4bit is
    port(
        dout            : out    vl_logic_vector(3 downto 0);
        rst             : in     vl_logic;
        clk             : in     vl_logic
    );
end counter_4bit;
