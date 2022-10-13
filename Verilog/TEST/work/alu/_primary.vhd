library verilog;
use verilog.vl_types.all;
entity alu is
    port(
        ctl             : in     vl_logic_vector(2 downto 0);
        a               : in     vl_logic_vector(31 downto 0);
        b               : in     vl_logic_vector(31 downto 0);
        result          : out    vl_logic_vector(31 downto 0);
        shamt           : in     vl_logic_vector(4 downto 0)
    );
end alu;
