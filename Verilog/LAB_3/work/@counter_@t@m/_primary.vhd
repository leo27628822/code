library verilog;
use verilog.vl_types.all;
entity Counter_TM is
    generic(
        WIDTH           : integer := 8;
        bit_width       : integer := 256;
        t               : integer := 10;
        th              : vl_notype
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of WIDTH : constant is 1;
    attribute mti_svvh_generic_type of bit_width : constant is 1;
    attribute mti_svvh_generic_type of t : constant is 1;
    attribute mti_svvh_generic_type of th : constant is 3;
end Counter_TM;
