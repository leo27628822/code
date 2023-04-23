-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus II 64-Bit"
-- VERSION "Version 13.1.0 Build 162 10/23/2013 SJ Web Edition"

-- DATE "04/23/2023 19:49:25"

-- 
-- Device: Altera EP3C16F484C6 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY ALTERA;
LIBRARY CYCLONEIII;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE CYCLONEIII.CYCLONEIII_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Counter_10927143 IS
    PORT (
	dout : BUFFER std_logic_vector(7 DOWNTO 0);
	clk : IN std_logic;
	rst : IN std_logic;
	en : IN std_logic;
	up : IN std_logic
	);
END Counter_10927143;

-- Design Ports Information
-- dout[0]	=>  Location: PIN_A10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- dout[1]	=>  Location: PIN_E11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- dout[2]	=>  Location: PIN_F11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- dout[3]	=>  Location: PIN_B13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- dout[4]	=>  Location: PIN_E13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- dout[5]	=>  Location: PIN_E12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- dout[6]	=>  Location: PIN_B14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- dout[7]	=>  Location: PIN_A13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- clk	=>  Location: PIN_A12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- up	=>  Location: PIN_A11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- en	=>  Location: PIN_B11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- rst	=>  Location: PIN_H11,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Counter_10927143 IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_dout : std_logic_vector(7 DOWNTO 0);
SIGNAL ww_clk : std_logic;
SIGNAL ww_rst : std_logic;
SIGNAL ww_en : std_logic;
SIGNAL ww_up : std_logic;
SIGNAL \clk~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \dout[0]~output_o\ : std_logic;
SIGNAL \dout[1]~output_o\ : std_logic;
SIGNAL \dout[2]~output_o\ : std_logic;
SIGNAL \dout[3]~output_o\ : std_logic;
SIGNAL \dout[4]~output_o\ : std_logic;
SIGNAL \dout[5]~output_o\ : std_logic;
SIGNAL \dout[6]~output_o\ : std_logic;
SIGNAL \dout[7]~output_o\ : std_logic;
SIGNAL \clk~input_o\ : std_logic;
SIGNAL \clk~inputclkctrl_outclk\ : std_logic;
SIGNAL \dout[0]~10_combout\ : std_logic;
SIGNAL \up~input_o\ : std_logic;
SIGNAL \dout[0]~11\ : std_logic;
SIGNAL \dout[1]~19_combout\ : std_logic;
SIGNAL \en~input_o\ : std_logic;
SIGNAL \dout[0]~15_combout\ : std_logic;
SIGNAL \dout[0]~16_combout\ : std_logic;
SIGNAL \dout[0]~17_combout\ : std_logic;
SIGNAL \rst~input_o\ : std_logic;
SIGNAL \dout[0]~13_combout\ : std_logic;
SIGNAL \dout[0]~12_combout\ : std_logic;
SIGNAL \dout[0]~14_combout\ : std_logic;
SIGNAL \dout[0]~18_combout\ : std_logic;
SIGNAL \dout[1]~reg0_q\ : std_logic;
SIGNAL \dout[1]~20\ : std_logic;
SIGNAL \dout[2]~21_combout\ : std_logic;
SIGNAL \dout[2]~reg0_q\ : std_logic;
SIGNAL \dout[2]~22\ : std_logic;
SIGNAL \dout[3]~23_combout\ : std_logic;
SIGNAL \dout[3]~reg0_q\ : std_logic;
SIGNAL \dout[3]~24\ : std_logic;
SIGNAL \dout[4]~25_combout\ : std_logic;
SIGNAL \dout[4]~reg0_q\ : std_logic;
SIGNAL \dout[4]~26\ : std_logic;
SIGNAL \dout[5]~27_combout\ : std_logic;
SIGNAL \dout[5]~reg0_q\ : std_logic;
SIGNAL \dout[5]~28\ : std_logic;
SIGNAL \dout[6]~29_combout\ : std_logic;
SIGNAL \dout[6]~reg0_q\ : std_logic;
SIGNAL \dout[6]~30\ : std_logic;
SIGNAL \dout[7]~31_combout\ : std_logic;
SIGNAL \dout[7]~reg0_q\ : std_logic;
SIGNAL \dout[0]~33_combout\ : std_logic;
SIGNAL \dout[0]~reg0_q\ : std_logic;

BEGIN

dout <= ww_dout;
ww_clk <= clk;
ww_rst <= rst;
ww_en <= en;
ww_up <= up;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\clk~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \clk~input_o\);

-- Location: IOOBUF_X16_Y29_N16
\dout[0]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \dout[0]~reg0_q\,
	devoe => ww_devoe,
	o => \dout[0]~output_o\);

-- Location: IOOBUF_X21_Y29_N23
\dout[1]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \dout[1]~reg0_q\,
	devoe => ww_devoe,
	o => \dout[1]~output_o\);

-- Location: IOOBUF_X21_Y29_N30
\dout[2]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \dout[2]~reg0_q\,
	devoe => ww_devoe,
	o => \dout[2]~output_o\);

-- Location: IOOBUF_X21_Y29_N9
\dout[3]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \dout[3]~reg0_q\,
	devoe => ww_devoe,
	o => \dout[3]~output_o\);

-- Location: IOOBUF_X23_Y29_N16
\dout[4]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \dout[4]~reg0_q\,
	devoe => ww_devoe,
	o => \dout[4]~output_o\);

-- Location: IOOBUF_X21_Y29_N16
\dout[5]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \dout[5]~reg0_q\,
	devoe => ww_devoe,
	o => \dout[5]~output_o\);

-- Location: IOOBUF_X23_Y29_N30
\dout[6]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \dout[6]~reg0_q\,
	devoe => ww_devoe,
	o => \dout[6]~output_o\);

-- Location: IOOBUF_X21_Y29_N2
\dout[7]~output\ : cycloneiii_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \dout[7]~reg0_q\,
	devoe => ww_devoe,
	o => \dout[7]~output_o\);

-- Location: IOIBUF_X19_Y29_N1
\clk~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_clk,
	o => \clk~input_o\);

-- Location: CLKCTRL_G14
\clk~inputclkctrl\ : cycloneiii_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \clk~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \clk~inputclkctrl_outclk\);

-- Location: LCCOMB_X22_Y28_N4
\dout[0]~10\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~10_combout\ = \dout[0]~reg0_q\ $ (VCC)
-- \dout[0]~11\ = CARRY(\dout[0]~reg0_q\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \dout[0]~reg0_q\,
	datad => VCC,
	combout => \dout[0]~10_combout\,
	cout => \dout[0]~11\);

-- Location: IOIBUF_X19_Y29_N15
\up~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_up,
	o => \up~input_o\);

-- Location: LCCOMB_X22_Y28_N6
\dout[1]~19\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[1]~19_combout\ = (\up~input_o\ & ((\dout[1]~reg0_q\ & (!\dout[0]~11\)) # (!\dout[1]~reg0_q\ & ((\dout[0]~11\) # (GND))))) # (!\up~input_o\ & ((\dout[1]~reg0_q\ & (\dout[0]~11\ & VCC)) # (!\dout[1]~reg0_q\ & (!\dout[0]~11\))))
-- \dout[1]~20\ = CARRY((\up~input_o\ & ((!\dout[0]~11\) # (!\dout[1]~reg0_q\))) # (!\up~input_o\ & (!\dout[1]~reg0_q\ & !\dout[0]~11\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100100101011",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \up~input_o\,
	datab => \dout[1]~reg0_q\,
	datad => VCC,
	cin => \dout[0]~11\,
	combout => \dout[1]~19_combout\,
	cout => \dout[1]~20\);

-- Location: IOIBUF_X19_Y29_N22
\en~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_en,
	o => \en~input_o\);

-- Location: LCCOMB_X22_Y28_N26
\dout[0]~15\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~15_combout\ = (\dout[1]~reg0_q\ & (\up~input_o\ & (\dout[2]~reg0_q\ & \dout[0]~reg0_q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \dout[1]~reg0_q\,
	datab => \up~input_o\,
	datac => \dout[2]~reg0_q\,
	datad => \dout[0]~reg0_q\,
	combout => \dout[0]~15_combout\);

-- Location: LCCOMB_X22_Y28_N24
\dout[0]~16\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~16_combout\ = (\dout[4]~reg0_q\ & (\dout[6]~reg0_q\ & (\dout[5]~reg0_q\ & \dout[3]~reg0_q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \dout[4]~reg0_q\,
	datab => \dout[6]~reg0_q\,
	datac => \dout[5]~reg0_q\,
	datad => \dout[3]~reg0_q\,
	combout => \dout[0]~16_combout\);

-- Location: LCCOMB_X22_Y28_N2
\dout[0]~17\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~17_combout\ = ((\dout[7]~reg0_q\ & (\dout[0]~15_combout\ & \dout[0]~16_combout\))) # (!\en~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1101010101010101",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \en~input_o\,
	datab => \dout[7]~reg0_q\,
	datac => \dout[0]~15_combout\,
	datad => \dout[0]~16_combout\,
	combout => \dout[0]~17_combout\);

-- Location: IOIBUF_X19_Y29_N29
\rst~input\ : cycloneiii_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_rst,
	o => \rst~input_o\);

-- Location: LCCOMB_X22_Y28_N22
\dout[0]~13\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~13_combout\ = (!\dout[3]~reg0_q\ & (!\dout[6]~reg0_q\ & (!\dout[5]~reg0_q\ & !\dout[4]~reg0_q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \dout[3]~reg0_q\,
	datab => \dout[6]~reg0_q\,
	datac => \dout[5]~reg0_q\,
	datad => \dout[4]~reg0_q\,
	combout => \dout[0]~13_combout\);

-- Location: LCCOMB_X22_Y28_N28
\dout[0]~12\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~12_combout\ = (!\dout[1]~reg0_q\ & (!\up~input_o\ & (!\dout[2]~reg0_q\ & !\dout[0]~reg0_q\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \dout[1]~reg0_q\,
	datab => \up~input_o\,
	datac => \dout[2]~reg0_q\,
	datad => \dout[0]~reg0_q\,
	combout => \dout[0]~12_combout\);

-- Location: LCCOMB_X22_Y28_N0
\dout[0]~14\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~14_combout\ = (!\dout[7]~reg0_q\ & (\dout[0]~13_combout\ & \dout[0]~12_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \dout[7]~reg0_q\,
	datac => \dout[0]~13_combout\,
	datad => \dout[0]~12_combout\,
	combout => \dout[0]~14_combout\);

-- Location: LCCOMB_X22_Y28_N20
\dout[0]~18\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~18_combout\ = ((!\dout[0]~17_combout\ & !\dout[0]~14_combout\)) # (!\rst~input_o\)

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111100111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \dout[0]~17_combout\,
	datac => \rst~input_o\,
	datad => \dout[0]~14_combout\,
	combout => \dout[0]~18_combout\);

-- Location: FF_X22_Y28_N7
\dout[1]~reg0\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk~inputclkctrl_outclk\,
	d => \dout[1]~19_combout\,
	sclr => \dout[0]~33_combout\,
	ena => \dout[0]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \dout[1]~reg0_q\);

-- Location: LCCOMB_X22_Y28_N8
\dout[2]~21\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[2]~21_combout\ = ((\dout[2]~reg0_q\ $ (\up~input_o\ $ (\dout[1]~20\)))) # (GND)
-- \dout[2]~22\ = CARRY((\dout[2]~reg0_q\ & ((!\dout[1]~20\) # (!\up~input_o\))) # (!\dout[2]~reg0_q\ & (!\up~input_o\ & !\dout[1]~20\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011000101011",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \dout[2]~reg0_q\,
	datab => \up~input_o\,
	datad => VCC,
	cin => \dout[1]~20\,
	combout => \dout[2]~21_combout\,
	cout => \dout[2]~22\);

-- Location: FF_X22_Y28_N9
\dout[2]~reg0\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk~inputclkctrl_outclk\,
	d => \dout[2]~21_combout\,
	sclr => \dout[0]~33_combout\,
	ena => \dout[0]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \dout[2]~reg0_q\);

-- Location: LCCOMB_X22_Y28_N10
\dout[3]~23\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[3]~23_combout\ = (\up~input_o\ & ((\dout[3]~reg0_q\ & (!\dout[2]~22\)) # (!\dout[3]~reg0_q\ & ((\dout[2]~22\) # (GND))))) # (!\up~input_o\ & ((\dout[3]~reg0_q\ & (\dout[2]~22\ & VCC)) # (!\dout[3]~reg0_q\ & (!\dout[2]~22\))))
-- \dout[3]~24\ = CARRY((\up~input_o\ & ((!\dout[2]~22\) # (!\dout[3]~reg0_q\))) # (!\up~input_o\ & (!\dout[3]~reg0_q\ & !\dout[2]~22\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100100101011",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \up~input_o\,
	datab => \dout[3]~reg0_q\,
	datad => VCC,
	cin => \dout[2]~22\,
	combout => \dout[3]~23_combout\,
	cout => \dout[3]~24\);

-- Location: FF_X22_Y28_N11
\dout[3]~reg0\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk~inputclkctrl_outclk\,
	d => \dout[3]~23_combout\,
	sclr => \dout[0]~33_combout\,
	ena => \dout[0]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \dout[3]~reg0_q\);

-- Location: LCCOMB_X22_Y28_N12
\dout[4]~25\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[4]~25_combout\ = ((\up~input_o\ $ (\dout[4]~reg0_q\ $ (\dout[3]~24\)))) # (GND)
-- \dout[4]~26\ = CARRY((\up~input_o\ & (\dout[4]~reg0_q\ & !\dout[3]~24\)) # (!\up~input_o\ & ((\dout[4]~reg0_q\) # (!\dout[3]~24\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011001001101",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \up~input_o\,
	datab => \dout[4]~reg0_q\,
	datad => VCC,
	cin => \dout[3]~24\,
	combout => \dout[4]~25_combout\,
	cout => \dout[4]~26\);

-- Location: FF_X22_Y28_N13
\dout[4]~reg0\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk~inputclkctrl_outclk\,
	d => \dout[4]~25_combout\,
	sclr => \dout[0]~33_combout\,
	ena => \dout[0]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \dout[4]~reg0_q\);

-- Location: LCCOMB_X22_Y28_N14
\dout[5]~27\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[5]~27_combout\ = (\dout[5]~reg0_q\ & ((\up~input_o\ & (!\dout[4]~26\)) # (!\up~input_o\ & (\dout[4]~26\ & VCC)))) # (!\dout[5]~reg0_q\ & ((\up~input_o\ & ((\dout[4]~26\) # (GND))) # (!\up~input_o\ & (!\dout[4]~26\))))
-- \dout[5]~28\ = CARRY((\dout[5]~reg0_q\ & (\up~input_o\ & !\dout[4]~26\)) # (!\dout[5]~reg0_q\ & ((\up~input_o\) # (!\dout[4]~26\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100101001101",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \dout[5]~reg0_q\,
	datab => \up~input_o\,
	datad => VCC,
	cin => \dout[4]~26\,
	combout => \dout[5]~27_combout\,
	cout => \dout[5]~28\);

-- Location: FF_X22_Y28_N15
\dout[5]~reg0\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk~inputclkctrl_outclk\,
	d => \dout[5]~27_combout\,
	sclr => \dout[0]~33_combout\,
	ena => \dout[0]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \dout[5]~reg0_q\);

-- Location: LCCOMB_X22_Y28_N16
\dout[6]~29\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[6]~29_combout\ = ((\dout[6]~reg0_q\ $ (\up~input_o\ $ (\dout[5]~28\)))) # (GND)
-- \dout[6]~30\ = CARRY((\dout[6]~reg0_q\ & ((!\dout[5]~28\) # (!\up~input_o\))) # (!\dout[6]~reg0_q\ & (!\up~input_o\ & !\dout[5]~28\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1001011000101011",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \dout[6]~reg0_q\,
	datab => \up~input_o\,
	datad => VCC,
	cin => \dout[5]~28\,
	combout => \dout[6]~29_combout\,
	cout => \dout[6]~30\);

-- Location: FF_X22_Y28_N17
\dout[6]~reg0\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk~inputclkctrl_outclk\,
	d => \dout[6]~29_combout\,
	sclr => \dout[0]~33_combout\,
	ena => \dout[0]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \dout[6]~reg0_q\);

-- Location: LCCOMB_X22_Y28_N18
\dout[7]~31\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[7]~31_combout\ = \dout[7]~reg0_q\ $ (\up~input_o\ $ (!\dout[6]~30\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0110100101101001",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \dout[7]~reg0_q\,
	datab => \up~input_o\,
	cin => \dout[6]~30\,
	combout => \dout[7]~31_combout\);

-- Location: FF_X22_Y28_N19
\dout[7]~reg0\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk~inputclkctrl_outclk\,
	d => \dout[7]~31_combout\,
	sclr => \dout[0]~33_combout\,
	ena => \dout[0]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \dout[7]~reg0_q\);

-- Location: LCCOMB_X22_Y28_N30
\dout[0]~33\ : cycloneiii_lcell_comb
-- Equation(s):
-- \dout[0]~33_combout\ = (\dout[0]~17_combout\) # ((!\dout[7]~reg0_q\ & (\dout[0]~12_combout\ & \dout[0]~13_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111111101000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \dout[7]~reg0_q\,
	datab => \dout[0]~12_combout\,
	datac => \dout[0]~13_combout\,
	datad => \dout[0]~17_combout\,
	combout => \dout[0]~33_combout\);

-- Location: FF_X22_Y28_N5
\dout[0]~reg0\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk~inputclkctrl_outclk\,
	d => \dout[0]~10_combout\,
	sclr => \dout[0]~33_combout\,
	ena => \dout[0]~18_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \dout[0]~reg0_q\);

ww_dout(0) <= \dout[0]~output_o\;

ww_dout(1) <= \dout[1]~output_o\;

ww_dout(2) <= \dout[2]~output_o\;

ww_dout(3) <= \dout[3]~output_o\;

ww_dout(4) <= \dout[4]~output_o\;

ww_dout(5) <= \dout[5]~output_o\;

ww_dout(6) <= \dout[6]~output_o\;

ww_dout(7) <= \dout[7]~output_o\;
END structure;


