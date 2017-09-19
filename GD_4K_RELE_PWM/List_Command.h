//----------------------------------------- List_Command.h ---------------------------------------

__root __flash const unsigned char ver_00[]="GD-1\n\r\0";
__root __flash const unsigned char NRZ_00[]="\n\r\0";

__root __flash const unsigned char command_00[]="\0*00";
__root __flash const unsigned char command_01[]=" test\0*01";
__root __flash const unsigned char command_02[]=" reset\0*02";
__root __flash const unsigned char command_03[]=" ver\0*03";
__root __flash const unsigned char command_04[]=" run\0*04";
__root __flash const unsigned char command_06[]=" var\0*06";
__root __flash const unsigned char command_07[]=" read\0*07";
__root __flash const unsigned char command_08[]=" tab\0*08";
__root __flash const unsigned char command_09[]=" rxd\0*09";
__root __flash const unsigned char command_10[]=" tbk\0*10";

__root __flash const unsigned char command_end[]="99 \n\0";

__root __flash const unsigned char error_00[]="!!! Error !!!\n\r\0";
__root __flash const unsigned char error_01[]="Bad command\n\r\0";
__root __flash const unsigned char Ok_00[]="  Ok!\n\r\0";

__root __flash const unsigned char test_00[]="Programm of the Test GD\n\r\0";
__root __flash const unsigned char test_01[]="Quit[Q]\n\r\0";
__root __flash const unsigned char test_02[]="off/on  RELE[r], GAS[g], MUZD[m]\n\r\0";
__root __flash const unsigned char test_03[]="off/on  Kl[1], K2[2], K3[3], K[4]\n\r\0";
__root __flash const unsigned char test_04[]="Taxometer [t], Akselerator[a]\n\r\0";
__root __flash const unsigned char test_on[]="ON \n\r\0";
__root __flash const unsigned char test_off[]="OFF \n\r\0";
__root __flash const unsigned char test_true[]="nondefective\0";
__root __flash const unsigned char test_false[]="fail\0";

__root __flash const unsigned char Start_hello_01[]="Serial = \0";
__root __flash const unsigned char Start_hello_02[]="SMotor_K1 = \0";
__root __flash const unsigned char Start_hello_03[]="Kp_Gain_2 = \0";
__root __flash const unsigned char Start_hello_04[]="idling motor = \0";
__root __flash const unsigned char Start_hello_05[]="High Level PID = \0";
__root __flash const unsigned char Start_hello_06[]="Low Level PID = \0";
__root __flash const unsigned char Start_hello_07[]="Faza[15] = \0";
__root __flash const unsigned char Start_hello_08[]="Flag Duo/Mono = \0";
__root __flash const unsigned char Start_hello_09[]="Pressure offset = \0";
__root __flash const unsigned char Start_hello_10[]="Pressure Koeff = \0";
__root __flash const unsigned char Start_hello_11[]="Zapazdivanie po oborotam = \0";
__root __flash const unsigned char Start_hello_12[]="Low level Idling = \0";
__root __flash const unsigned char Start_hello_13[]="Step[15] = \0";
__root __flash const unsigned char Start_hello_14[]="Motor Step Offset = \0";
__root __flash const unsigned char Start_hello_15[]="Mahovik tooth = \0";
__root __flash const unsigned char Start_hello_16[]="Error = \0";
__root __flash const unsigned char Start_hello_17[]="Temp_Gain_1 = \0";
__root __flash const unsigned char Start_hello_18[]="Temp_Gain_2 = \0";
__root __flash const unsigned char Start_hello_19[]="Temp. pred collector = \0";
//__root __flash const unsigned char Start_hello_20[]="Temp. pred reduktor = \0";
__root __flash const unsigned char Start_hello_20[]="D_min = \0";
__root __flash const unsigned char Start_hello_24[]="D_max = \0";
__root __flash const unsigned char Start_hello_21[]="High Level GAS for temperature = \0";
__root __flash const unsigned char Start_hello_22[]="END PAKET \0";
__root __flash const unsigned char Start_hello_23[]="PEDAL \0";


__root __flash const unsigned char OTV_1[]="var K0 \0";
__root __flash const unsigned char OTV_2[]="var K1 \0";
__root __flash const unsigned char OTV_3[]="var K2 \0";
__root __flash const unsigned char OTV_4[]="var K3 \0";
__root __flash const unsigned char OTV_5[]="var K4 \0";
__root __flash const unsigned char OTV_6[]="var Tc \0";
__root __flash const unsigned char OTV_7l[]="var Dl \0";
__root __flash const unsigned char OTV_7h[]="var Dh \0";
__root __flash const unsigned char OTV_8[]="var Id \0";
__root __flash const unsigned char OTV_9[]="var Mo \0";
__root __flash const unsigned char OTV_10[]="var To \0";
__root __flash const unsigned char OTV_11[]="var Tk \0";
__root __flash const unsigned char OTV_12[]="var Tm \0";
__root __flash const unsigned char OTV_13[]="var Mt \0";
__root __flash const unsigned char OTV_14[]="var Pl \0";
__root __flash const unsigned char OTV_15[]="var Pi \0";


__root __flash const unsigned char OTV_RUN_GD[]="run_GD \0";
__root __flash const unsigned char OTV_STOP_GD[]="stop_GD \0";
__root __flash const unsigned char OK_RUN_GD[]="ok_run_GD \0";
__root __flash const unsigned char ERROR_GD[]="error_GD \0";


__root __flash const unsigned char DT_11[]="tab DT11 \0";
__root __flash const unsigned char DT_11_END[]="DT_11_END \0";
__root __flash const unsigned char DT_12[]="tab DT12 \0";
__root __flash const unsigned char DT_12_END[]="DT_12_END \0";
__root __flash const unsigned char DT_13[]="tab DT13 \0";
__root __flash const unsigned char DT_13_END[]="DT_13_END \0";
__root __flash const unsigned char DT_14[]="tab DT14 \0";
__root __flash const unsigned char DT_14_END[]="DT_14_END \0";
__root __flash const unsigned char DT_15[]="tab DT15 \0";
__root __flash const unsigned char DT_15_END[]="DT_15_END \0";
__root __flash const unsigned char DT_16[]="tab DT16 \0";
__root __flash const unsigned char DT_16_END[]="DT_16_END \0";


__root __flash const unsigned char DT_21[]="tab DT21 \0";
__root __flash const unsigned char DT_21_END[]="DT_21_END \0";
__root __flash const unsigned char DT_22[]="tab DT22 \0";
__root __flash const unsigned char DT_22_END[]="DT_22_END \0";
__root __flash const unsigned char DT_23[]="tab DT23 \0";
__root __flash const unsigned char DT_23_END[]="DT_23_END \0";
__root __flash const unsigned char DT_24[]="tab DT24 \0";
__root __flash const unsigned char DT_24_END[]="DT_24_END \0";
__root __flash const unsigned char DT_25[]="tab DT25 \0";
__root __flash const unsigned char DT_25_END[]="DT_25_END \0";
__root __flash const unsigned char DT_26[]="tab DT26 \0";
__root __flash const unsigned char DT_26_END[]="DT_26_END \0";


__root __flash const unsigned char DT_27[]="tab DT27 \0";
__root __flash const unsigned char DT_27_END[]="DT_27_END \0";
__root __flash const unsigned char DT_28[]="tab DT28 \0";
__root __flash const unsigned char DT_28_END[]="DT_28_END \0";
__root __flash const unsigned char DT_29[]="tab DT29 \0";
__root __flash const unsigned char DT_29_END[]="DT_29_END \0";
__root __flash const unsigned char DT_30[]="tab DT30 \0";
__root __flash const unsigned char DT_30_END[]="DT_30_END \0";
__root __flash const unsigned char DT_31[]="tab DT31 \0";
__root __flash const unsigned char DT_31_END[]="DT_31_END \0";
__root __flash const unsigned char DT_32[]="tab DT32 \0";
__root __flash const unsigned char DT_32_END[]="DT_32_END \0";
__root __flash const unsigned char DT_33[]="tab DT33 \0";
__root __flash const unsigned char DT_33_END[]="DT_33_END \0";
__root __flash const unsigned char DT_34[]="tab DT34 \0";
__root __flash const unsigned char DT_34_END[]="DT_34_END \0";
__root __flash const unsigned char DT_35[]="tab DT35 \0";
__root __flash const unsigned char DT_35_END[]="DT_35_END \0";

__root __flash const unsigned char DT_41[]="tab DT41 \0";
__root __flash const unsigned char DT_41_END[]="DT_41_END \0";


__root __flash const unsigned char tb1_01[]="tb1 DT01 \0";
__root __flash const unsigned char tb1_02[]="tb1 DT02 \0";
__root __flash const unsigned char tb1_03[]="tb1 DT03 \0";
__root __flash const unsigned char tb1_04[]="tb1 DT04 \0";
__root __flash const unsigned char tb1_05[]="tb1 DT05 \0";
__root __flash const unsigned char tb1_06[]="tb1 DT06 \0";
__root __flash const unsigned char tb1_07[]="tb1 DT07 \0";
__root __flash const unsigned char tb1_08[]="tb1 DT08 \0";
__root __flash const unsigned char tb1_09[]="tb1 DT09 \0";
__root __flash const unsigned char tb1_10[]="tb1 DT10 \0";
__root __flash const unsigned char tb1_11[]="tb1 DT11 \0";
__root __flash const unsigned char tb1_12[]="tb1 DT12 \0";
__root __flash const unsigned char tb1_13[]="tb1 DT13 \0";
__root __flash const unsigned char tb1_14[]="tb1 DT14 \0";
__root __flash const unsigned char tb1_15[]="tb1 DT15 \0";


__root __flash const unsigned char tb2_01[]="tb2 DT01 \0";
__root __flash const unsigned char tb2_02[]="tb2 DT02 \0";
__root __flash const unsigned char tb2_03[]="tb2 DT03 \0";
__root __flash const unsigned char tb2_04[]="tb2 DT04 \0";
__root __flash const unsigned char tb2_05[]="tb2 DT05 \0";
__root __flash const unsigned char tb2_06[]="tb2 DT06 \0";
__root __flash const unsigned char tb2_07[]="tb2 DT07 \0";
__root __flash const unsigned char tb2_08[]="tb2 DT08 \0";
__root __flash const unsigned char tb2_09[]="tb2 DT09 \0";
__root __flash const unsigned char tb2_10[]="tb2 DT10 \0";
__root __flash const unsigned char tb2_11[]="tb2 DT11 \0";
__root __flash const unsigned char tb2_12[]="tb2 DT12 \0";
__root __flash const unsigned char tb2_13[]="tb2 DT13 \0";
__root __flash const unsigned char tb2_14[]="tb2 DT14 \0";
__root __flash const unsigned char tb2_15[]="tb2 DT15 \0";


__root __flash const unsigned char tb3_01[]="tb3 DT01 \0";
__root __flash const unsigned char tb3_02[]="tb3 DT02 \0";
__root __flash const unsigned char tb3_03[]="tb3 DT03 \0";
__root __flash const unsigned char tb3_04[]="tb3 DT04 \0";
__root __flash const unsigned char tb3_05[]="tb3 DT05 \0";
__root __flash const unsigned char tb3_06[]="tb3 DT06 \0";
__root __flash const unsigned char tb3_07[]="tb3 DT07 \0";
__root __flash const unsigned char tb3_08[]="tb3 DT08 \0";
__root __flash const unsigned char tb3_09[]="tb3 DT09 \0";
__root __flash const unsigned char tb3_10[]="tb3 DT10 \0";
__root __flash const unsigned char tb3_11[]="tb3 DT11 \0";
__root __flash const unsigned char tb3_12[]="tb3 DT12 \0";
__root __flash const unsigned char tb3_13[]="tb3 DT13 \0";
__root __flash const unsigned char tb3_14[]="tb3 DT14 \0";
__root __flash const unsigned char tb3_15[]="tb3 DT15 \0";


__root __flash const unsigned char tb4_01[]="tb4 DT01 \0";
__root __flash const unsigned char tb4_02[]="tb4 DT02 \0";
__root __flash const unsigned char tb4_03[]="tb4 DT03 \0";
__root __flash const unsigned char tb4_04[]="tb4 DT04 \0";
__root __flash const unsigned char tb4_05[]="tb4 DT05 \0";
__root __flash const unsigned char tb4_06[]="tb4 DT06 \0";
__root __flash const unsigned char tb4_07[]="tb4 DT07 \0";
__root __flash const unsigned char tb4_08[]="tb4 DT08 \0";
__root __flash const unsigned char tb4_09[]="tb4 DT09 \0";
__root __flash const unsigned char tb4_10[]="tb4 DT10 \0";
__root __flash const unsigned char tb4_11[]="tb4 DT11 \0";
__root __flash const unsigned char tb4_12[]="tb4 DT12 \0";
__root __flash const unsigned char tb4_13[]="tb4 DT13 \0";
__root __flash const unsigned char tb4_14[]="tb4 DT14 \0";
__root __flash const unsigned char tb4_15[]="tb4 DT15 \0";


__root __flash const unsigned char tb5_01[]="tb5 DT01 \0";
__root __flash const unsigned char tb5_02[]="tb5 DT02 \0";
__root __flash const unsigned char tb5_03[]="tb5 DT03 \0";
__root __flash const unsigned char tb5_04[]="tb5 DT04 \0";
__root __flash const unsigned char tb5_05[]="tb5 DT05 \0";
__root __flash const unsigned char tb5_06[]="tb5 DT06 \0";
__root __flash const unsigned char tb5_07[]="tb5 DT07 \0";
__root __flash const unsigned char tb5_08[]="tb5 DT08 \0";
__root __flash const unsigned char tb5_09[]="tb5 DT09 \0";
__root __flash const unsigned char tb5_10[]="tb5 DT10 \0";
__root __flash const unsigned char tb5_11[]="tb5 DT11 \0";
__root __flash const unsigned char tb5_12[]="tb5 DT12 \0";
__root __flash const unsigned char tb5_13[]="tb5 DT13 \0";
__root __flash const unsigned char tb5_14[]="tb5 DT14 \0";
__root __flash const unsigned char tb5_15[]="tb5 DT15 \0";


__root __flash const unsigned char tb6_01[]="tb6 DT01 \0";
__root __flash const unsigned char tb6_02[]="tb6 DT02 \0";
__root __flash const unsigned char tb6_03[]="tb6 DT03 \0";
__root __flash const unsigned char tb6_04[]="tb6 DT04 \0";
__root __flash const unsigned char tb6_05[]="tb6 DT05 \0";
__root __flash const unsigned char tb6_06[]="tb6 DT06 \0";
__root __flash const unsigned char tb6_07[]="tb6 DT07 \0";
__root __flash const unsigned char tb6_08[]="tb6 DT08 \0";
__root __flash const unsigned char tb6_09[]="tb6 DT09 \0";
__root __flash const unsigned char tb6_10[]="tb6 DT10 \0";
__root __flash const unsigned char tb6_11[]="tb6 DT11 \0";
__root __flash const unsigned char tb6_12[]="tb6 DT12 \0";
__root __flash const unsigned char tb6_13[]="tb6 DT13 \0";
__root __flash const unsigned char tb6_14[]="tb6 DT14 \0";
__root __flash const unsigned char tb6_15[]="tb6 DT15 \0";


__root __flash const unsigned char tb7_01[]="tb7 DT01 \0";
__root __flash const unsigned char tb7_02[]="tb7 DT02 \0";
__root __flash const unsigned char tb7_03[]="tb7 DT03 \0";
__root __flash const unsigned char tb7_04[]="tb7 DT04 \0";
__root __flash const unsigned char tb7_05[]="tb7 DT05 \0";
__root __flash const unsigned char tb7_06[]="tb7 DT06 \0";
__root __flash const unsigned char tb7_07[]="tb7 DT07 \0";
__root __flash const unsigned char tb7_08[]="tb7 DT08 \0";
__root __flash const unsigned char tb7_09[]="tb7 DT09 \0";
__root __flash const unsigned char tb7_10[]="tb7 DT10 \0";
__root __flash const unsigned char tb7_11[]="tb7 DT11 \0";
__root __flash const unsigned char tb7_12[]="tb7 DT12 \0";
__root __flash const unsigned char tb7_13[]="tb7 DT13 \0";
__root __flash const unsigned char tb7_14[]="tb7 DT14 \0";
__root __flash const unsigned char tb7_15[]="tb7 DT15 \0";


__root __flash const unsigned char tb8_01[]="tb8 DT01 \0";
__root __flash const unsigned char tb8_02[]="tb8 DT02 \0";
__root __flash const unsigned char tb8_03[]="tb8 DT03 \0";
__root __flash const unsigned char tb8_04[]="tb8 DT04 \0";
__root __flash const unsigned char tb8_05[]="tb8 DT05 \0";
__root __flash const unsigned char tb8_06[]="tb8 DT06 \0";
__root __flash const unsigned char tb8_07[]="tb8 DT07 \0";
__root __flash const unsigned char tb8_08[]="tb8 DT08 \0";
__root __flash const unsigned char tb8_09[]="tb8 DT09 \0";
__root __flash const unsigned char tb8_10[]="tb8 DT10 \0";
__root __flash const unsigned char tb8_11[]="tb8 DT11 \0";
__root __flash const unsigned char tb8_12[]="tb8 DT12 \0";
__root __flash const unsigned char tb8_13[]="tb8 DT13 \0";
__root __flash const unsigned char tb8_14[]="tb8 DT14 \0";
__root __flash const unsigned char tb8_15[]="tb8 DT15 \0";


__root __flash const unsigned char tb9_01[]="tb9 DT01 \0";
__root __flash const unsigned char tb9_02[]="tb9 DT02 \0";
__root __flash const unsigned char tb9_03[]="tb9 DT03 \0";
__root __flash const unsigned char tb9_04[]="tb9 DT04 \0";
__root __flash const unsigned char tb9_05[]="tb9 DT05 \0";
__root __flash const unsigned char tb9_06[]="tb9 DT06 \0";
__root __flash const unsigned char tb9_07[]="tb9 DT07 \0";
__root __flash const unsigned char tb9_08[]="tb9 DT08 \0";
__root __flash const unsigned char tb9_09[]="tb9 DT09 \0";
__root __flash const unsigned char tb9_10[]="tb9 DT10 \0";
__root __flash const unsigned char tb9_11[]="tb9 DT11 \0";
__root __flash const unsigned char tb9_12[]="tb9 DT12 \0";
__root __flash const unsigned char tb9_13[]="tb9 DT13 \0";
__root __flash const unsigned char tb9_14[]="tb9 DT14 \0";
__root __flash const unsigned char tb9_15[]="tb9 DT15 \0";


__root __flash const unsigned char tb10_01[]="tba DT01 \0";
__root __flash const unsigned char tb10_02[]="tba DT02 \0";
__root __flash const unsigned char tb10_03[]="tba DT03 \0";
__root __flash const unsigned char tb10_04[]="tba DT04 \0";
__root __flash const unsigned char tb10_05[]="tba DT05 \0";
__root __flash const unsigned char tb10_06[]="tba DT06 \0";
__root __flash const unsigned char tb10_07[]="tba DT07 \0";
__root __flash const unsigned char tb10_08[]="tba DT08 \0";
__root __flash const unsigned char tb10_09[]="tba DT09 \0";
__root __flash const unsigned char tb10_10[]="tba DT10 \0";
__root __flash const unsigned char tb10_11[]="tba DT11 \0";
__root __flash const unsigned char tb10_12[]="tba DT12 \0";
__root __flash const unsigned char tb10_13[]="tba DT13 \0";
__root __flash const unsigned char tb10_14[]="tba DT14 \0";
__root __flash const unsigned char tb10_15[]="tba DT15 \0";


__root __flash const unsigned char tb11_01[]="tbb DT01 \0";
__root __flash const unsigned char tb11_02[]="tbb DT02 \0";
__root __flash const unsigned char tb11_03[]="tbb DT03 \0";
__root __flash const unsigned char tb11_04[]="tbb DT04 \0";
__root __flash const unsigned char tb11_05[]="tbb DT05 \0";
__root __flash const unsigned char tb11_06[]="tbb DT06 \0";
__root __flash const unsigned char tb11_07[]="tbb DT07 \0";
__root __flash const unsigned char tb11_08[]="tbb DT08 \0";
__root __flash const unsigned char tb11_09[]="tbb DT09 \0";
__root __flash const unsigned char tb11_10[]="tbb DT10 \0";
__root __flash const unsigned char tb11_11[]="tbb DT11 \0";
__root __flash const unsigned char tb11_12[]="tbb DT12 \0";
__root __flash const unsigned char tb11_13[]="tbb DT13 \0";
__root __flash const unsigned char tb11_14[]="tbb DT14 \0";
__root __flash const unsigned char tb11_15[]="tbb DT15 \0";


__root __flash const unsigned char tb12_01[]="tbc DT01 \0";
__root __flash const unsigned char tb12_02[]="tbc DT02 \0";
__root __flash const unsigned char tb12_03[]="tbc DT03 \0";
__root __flash const unsigned char tb12_04[]="tbc DT04 \0";
__root __flash const unsigned char tb12_05[]="tbc DT05 \0";
__root __flash const unsigned char tb12_06[]="tbc DT06 \0";
__root __flash const unsigned char tb12_07[]="tbc DT07 \0";
__root __flash const unsigned char tb12_08[]="tbc DT08 \0";
__root __flash const unsigned char tb12_09[]="tbc DT09 \0";
__root __flash const unsigned char tb12_10[]="tbc DT10 \0";
__root __flash const unsigned char tb12_11[]="tbc DT11 \0";
__root __flash const unsigned char tb12_12[]="tbc DT12 \0";
__root __flash const unsigned char tb12_13[]="tbc DT13 \0";
__root __flash const unsigned char tb12_14[]="tbc DT14 \0";
__root __flash const unsigned char tb12_15[]="tbc DT15 \0";


__root __flash const unsigned char tb13_01[]="tbd DT01 \0";
__root __flash const unsigned char tb13_02[]="tbd DT02 \0";
__root __flash const unsigned char tb13_03[]="tbd DT03 \0";
__root __flash const unsigned char tb13_04[]="tbd DT04 \0";
__root __flash const unsigned char tb13_05[]="tbd DT05 \0";
__root __flash const unsigned char tb13_06[]="tbd DT06 \0";
__root __flash const unsigned char tb13_07[]="tbd DT07 \0";
__root __flash const unsigned char tb13_08[]="tbd DT08 \0";
__root __flash const unsigned char tb13_09[]="tbd DT09 \0";
__root __flash const unsigned char tb13_10[]="tbd DT10 \0";
__root __flash const unsigned char tb13_11[]="tbd DT11 \0";
__root __flash const unsigned char tb13_12[]="tbd DT12 \0";
__root __flash const unsigned char tb13_13[]="tbd DT13 \0";
__root __flash const unsigned char tb13_14[]="tbd DT14 \0";
__root __flash const unsigned char tb13_15[]="tbd DT15 \0";
__root __flash const unsigned char tb13_16[]="tbd DT16 \0";


__root __flash const unsigned char tb14_01[]="tbe DT01 \0";
__root __flash const unsigned char tb14_02[]="tbe DT02 \0";
__root __flash const unsigned char tb14_03[]="tbe DT03 \0";
__root __flash const unsigned char tb14_04[]="tbe DT04 \0";
__root __flash const unsigned char tb14_05[]="tbe DT05 \0";
__root __flash const unsigned char tb14_06[]="tbe DT06 \0";
__root __flash const unsigned char tb14_07[]="tbe DT07 \0";
__root __flash const unsigned char tb14_08[]="tbe DT08 \0";
__root __flash const unsigned char tb14_09[]="tbe DT09 \0";
__root __flash const unsigned char tb14_10[]="tbe DT10 \0";
__root __flash const unsigned char tb14_11[]="tbe DT11 \0";
__root __flash const unsigned char tb14_12[]="tbe DT12 \0";
__root __flash const unsigned char tb14_13[]="tbe DT13 \0";
__root __flash const unsigned char tb14_14[]="tbe DT14 \0";
__root __flash const unsigned char tb14_15[]="tbe DT15 \0";
__root __flash const unsigned char tb14_16[]="tbe DT16 \0";
//------------------------------------- end List_Command.h ---------------------------------------

