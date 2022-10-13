library verilog;
use verilog.vl_types.all;
entity Comparator is
    port(
        A               : in     vl_logic_vector(3 downto 0);
        B               : in     vl_logic_vector(3 downto 0);
        A_gt_B          : out    vl_logic;
        A_eq_B          : out    vl_logic;
        A_lt_B          : out    vl_logic
    );
end Comparator;
