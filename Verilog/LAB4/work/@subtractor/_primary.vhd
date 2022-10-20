library verilog;
use verilog.vl_types.all;
entity Subtractor is
    port(
        X               : in     vl_logic_vector(3 downto 0);
        Y               : in     vl_logic_vector(3 downto 0);
        Z               : in     vl_logic;
        D               : out    vl_logic_vector(3 downto 0);
        B               : out    vl_logic_vector(3 downto 0)
    );
end Subtractor;
