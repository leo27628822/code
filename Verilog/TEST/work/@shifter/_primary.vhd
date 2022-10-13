library verilog;
use verilog.vl_types.all;
entity Shifter is
    port(
        dataA           : in     vl_logic_vector(31 downto 0);
        dataB           : in     vl_logic_vector(4 downto 0);
        dataOut         : out    vl_logic_vector(31 downto 0)
    );
end Shifter;
