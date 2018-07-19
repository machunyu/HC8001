`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Huangbiao
// 
// Create Date:    
// Design Name: 
// Module Name:    REGISTER_BLOCK_INITIAL 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: Set OV2281 CMOS Registers 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module REGISTER_BLOCK_INITIAL
(
    input          CLK  , 
    input  [ 8:0]  AD   ,
    output [23:0]  DO
);
/////////////////////////////////////////////////  
    reg [23:0] mem [290:1];

    initial begin		
		mem[1  ]= 24'h0103_01 ;//0x0103[0] -- reset,1-->reset
		mem[2  ]= 24'h0100_00 ;//mode control :[7:1] debug mode--[0] 0=software_stabdby 1=streaming
//-----------------------------PLL 1
		mem[10 ]= 24'h030a_00 ;		
        mem[3  ]= 24'h0300_04 ;
		mem[4  ]= 24'h0301_00 ;
		mem[5  ]= 24'h0302_3C ;   //mem[5  ]= 24'h030269 : 840Mbit/lane;  24'h03023C : 480Mbit/lane
		mem[6  ]= 24'h0303_00 ;
		mem[7  ]= 24'h0304_03 ;
		mem[8  ]= 24'h0305_01 ;
		mem[9  ]= 24'h0306_01 ;
//-----------------------------PLL 2
		mem[16 ]= 24'h0312_01 ;
		mem[11 ]= 24'h030b_00 ;        
		mem[12 ]= 24'h030c_00 ;
		mem[13 ]= 24'h030d_1e ;        
		mem[15 ]= 24'h030f_06 ;
		mem[14 ]= 24'h030e_00 ;        

		mem[17 ]= 24'h3000_00 ;
		mem[18 ]= 24'h3002_21 ;
		mem[19 ]= 24'h3005_f0 ;
		mem[20 ]= 24'h3007_00 ;
		mem[21 ]= 24'h3015_0f ;
        
		mem[22 ]= 24'h3018_32 ;
		mem[23 ]= 24'h301a_f0 ;
		mem[24 ]= 24'h301b_f0 ;
		mem[25 ]= 24'h301c_f0 ;
		mem[26 ]= 24'h301d_f0 ;
        
		mem[27 ]= 24'h301e_f0 ;
		mem[28 ]= 24'h3030_00 ;
		mem[29 ]= 24'h3031_0a ;
		mem[30 ]= 24'h303c_ff ;
		mem[31 ]= 24'h303e_ff ;
        
		mem[32 ]= 24'h3040_f0 ;
		mem[33 ]= 24'h3041_00 ;
		mem[34 ]= 24'h3042_f0 ;
		mem[35 ]= 24'h3106_11 ;
		mem[36 ]= 24'h3500_00 ;
        
		mem[37 ]= 24'h3501_45 ;
		mem[38 ]= 24'h3502_00 ;
		mem[39 ]= 24'h3503_04 ;
		mem[40 ]= 24'h3504_03 ;
		mem[41 ]= 24'h3505_83 ;
        
		mem[42 ]= 24'h3508_00 ;
		mem[43 ]= 24'h3509_80 ;
		mem[44 ]= 24'h350e_04 ;
		mem[45 ]= 24'h350f_00 ;
		mem[46 ]= 24'h3510_00 ;
		mem[47 ]= 24'h3511_02 ;
		mem[48 ]= 24'h3512_00 ;
		mem[49 ]= 24'h3601_c8 ;
		mem[50 ]= 24'h3610_88 ;
		mem[51 ]= 24'h3612_48 ;
		mem[52 ]= 24'h3614_5b ;
		mem[53 ]= 24'h3615_96 ;
		mem[54 ]= 24'h3621_d0 ;
		mem[55 ]= 24'h3622_00 ;
		mem[56 ]= 24'h3623_00 ;
		mem[57 ]= 24'h3633_13 ;
		mem[58 ]= 24'h3634_13 ;
		mem[59 ]= 24'h3635_13 ;
		mem[60 ]= 24'h3636_13 ;
		mem[61 ]= 24'h3645_13 ;
		mem[62 ]= 24'h3646_82 ;
		mem[63 ]= 24'h3650_00 ;
		mem[64 ]= 24'h3652_ff ;
		mem[65 ]= 24'h3655_20 ;
		mem[66 ]= 24'h3656_ff ;
		mem[67 ]= 24'h365a_ff ;
		mem[68 ]= 24'h365e_ff ;
		mem[69 ]= 24'h3668_00 ;
		mem[70 ]= 24'h366a_07 ;
		mem[71 ]= 24'h366e_10 ;
		mem[72 ]= 24'h366d_00 ;
		mem[73 ]= 24'h366f_80 ;
		mem[74 ]= 24'h3700_28 ;
		mem[75 ]= 24'h3701_10 ;
		mem[76 ]= 24'h3702_3a ;
		mem[77 ]= 24'h3703_19 ;
		mem[78 ]= 24'h3704_10 ;
		mem[79 ]= 24'h3705_00 ;
		mem[80 ]= 24'h3706_66 ;
		mem[81 ]= 24'h3707_08 ;
		mem[82 ]= 24'h3708_34 ;
		mem[83 ]= 24'h3709_40 ;
		mem[84 ]= 24'h370a_01 ;
		mem[85 ]= 24'h370b_1b ;
		mem[86 ]= 24'h3714_24 ;
		mem[87 ]= 24'h371a_3e ;
		mem[88 ]= 24'h3733_00 ;
		mem[89 ]= 24'h3734_00 ;
		mem[90 ]= 24'h373a_05 ;
		mem[91 ]= 24'h373b_06 ;
		mem[92 ]= 24'h373c_0a ;
		mem[93 ]= 24'h373f_a0 ;
		mem[94 ]= 24'h3755_00 ;
		mem[95 ]= 24'h3758_00 ;
		mem[96 ]= 24'h375b_0e ;
		mem[97 ]= 24'h3766_5f ;
		mem[98 ]= 24'h3768_00 ;
		mem[99 ]= 24'h3769_22 ;
		mem[100]= 24'h3773_08 ;
		mem[101]= 24'h3774_1f ;
		mem[102]= 24'h3776_06 ;
		mem[103]= 24'h37a0_88 ;
		mem[104]= 24'h37a1_5c ;
		mem[105]= 24'h37a7_88 ;
		mem[106]= 24'h37a8_70 ;
		mem[107]= 24'h37aa_88 ;
		mem[108]= 24'h37ab_48 ;
		mem[109]= 24'h37b3_66 ;
		mem[110]= 24'h37c2_04 ;
		mem[111]= 24'h37c5_00 ;
		mem[112]= 24'h37c8_00 ;
		mem[113]= 24'h3800_00 ;
		mem[114]= 24'h3801_0c ;
		mem[115]= 24'h3802_00 ;
		mem[116]= 24'h3803_04 ;
		mem[117]= 24'h3804_0a ;
		mem[118]= 24'h3805_33 ;
		mem[119]= 24'h3806_07 ;
		mem[120]= 24'h3807_a3 ;
		mem[121]= 24'h3808_07 ;   //
		mem[122]= 24'h3809_80 ;   // horizontal active size:0x0780 ---1920 
		mem[123]= 24'h380a_04 ;   //
		mem[124]= 24'h380b_38 ;   // vertical active size: 0x0438 ---1080 
		mem[125]= 24'h380c_08 ;   //
		mem[126]= 24'h380d_98 ;   // horizontal total size: 0x0898 ----2200 , 0x0852: ---2130
		mem[127]= 24'h380e_05 ;   //
		mem[128]= 24'h380f_dc ;   // vertical total size: 0x0465 ---1125 ,  0x05dc: ---1500
		mem[129]= 24'h3811_04 ;
		mem[130]= 24'h3813_02 ;
		mem[131]= 24'h3814_01 ;
		mem[132]= 24'h3815_01 ;
		mem[133]= 24'h3816_00 ;
		mem[134]= 24'h3817_00 ;
		mem[135]= 24'h3818_00 ;
		mem[136]= 24'h3819_00 ;
		mem[137]= 24'h3820_80 ;
		mem[138]= 24'h3821_46 ;
		mem[139]= 24'h3822_48 ;
		mem[140]= 24'h3826_00 ;
		mem[141]= 24'h3827_08 ;
		mem[142]= 24'h382a_01 ;
		mem[143]= 24'h382b_01 ;
		mem[144]= 24'h3830_08 ;
		mem[145]= 24'h3836_02 ;
		mem[146]= 24'h3837_00 ;
		mem[147]= 24'h3838_10 ;
		mem[148]= 24'h3841_ff ;
		mem[149]= 24'h3846_48 ;
		mem[150]= 24'h3861_00 ;
		mem[151]= 24'h3862_04 ;
		mem[152]= 24'h3863_06 ;
		mem[153]= 24'h3a11_01 ;
		mem[154]= 24'h3a12_78 ;
		mem[155]= 24'h3b00_00 ;
		mem[156]= 24'h3b02_00 ;
		mem[157]= 24'h3b03_00 ;
		mem[158]= 24'h3b04_00 ;
		mem[159]= 24'h3b05_00 ;
		mem[160]= 24'h3c00_89 ;
		mem[161]= 24'h3c01_ab ;
		mem[162]= 24'h3c02_01 ;
		mem[163]= 24'h3c03_00 ;
		mem[164]= 24'h3c04_00 ;
		mem[165]= 24'h3c05_03 ;
		mem[166]= 24'h3c06_00 ;
		mem[167]= 24'h3c07_05 ;
		mem[168]= 24'h3c0c_00 ;
		mem[169]= 24'h3c0d_00 ;
		mem[170]= 24'h3c0e_00 ;
		mem[171]= 24'h3c0f_00 ;
		mem[172]= 24'h3c40_00 ;
		mem[173]= 24'h3c41_a3 ;
		mem[174]= 24'h3c43_7d ;
		mem[175]= 24'h3c45_d7 ;
		mem[176]= 24'h3c47_fc ;
		mem[177]= 24'h3c50_05 ;
		mem[178]= 24'h3c52_aa ;
		mem[179]= 24'h3c54_71 ;
		mem[180]= 24'h3c56_80 ;
		mem[181]= 24'h3d85_17 ;
		mem[182]= 24'h3f03_00 ;
		mem[183]= 24'h3f0a_00 ;
		mem[184]= 24'h3f0b_00 ;
		mem[185]= 24'h4001_60 ;
		mem[186]= 24'h4009_0d ;
		mem[187]= 24'h4020_00 ;
		mem[188]= 24'h4021_00 ;
		mem[189]= 24'h4022_00 ;
		mem[190]= 24'h4023_00 ;
		mem[191]= 24'h4024_00 ;
		mem[192]= 24'h4025_00 ;
		mem[193]= 24'h4026_00 ;
		mem[194]= 24'h4027_00 ;
		mem[195]= 24'h4028_00 ;
		mem[196]= 24'h4029_00 ;
		mem[197]= 24'h402a_00 ;
		mem[198]= 24'h402b_00 ;
		mem[199]= 24'h402c_00 ;
		mem[200]= 24'h402d_00 ;
		mem[201]= 24'h402e_00 ;
		mem[202]= 24'h402f_00 ;
		mem[203]= 24'h4040_00 ;
		mem[204]= 24'h4041_03 ;
		mem[205]= 24'h4042_00 ;
		mem[206]= 24'h4043_7A ;
		mem[207]= 24'h4044_00 ;
		mem[208]= 24'h4045_7A ;
		mem[209]= 24'h4046_00 ;
		mem[210]= 24'h4047_7A ;
		mem[211]= 24'h4048_00 ;
		mem[212]= 24'h4049_7A ;
		mem[213]= 24'h4303_00 ;    // enable testpattern : 24'h430308
		mem[214]= 24'h4307_30 ;
		mem[215]= 24'h4500_58 ;
        mem[216]= 24'h4501_04 ;
		mem[217]= 24'h4502_40 ;
		mem[218]= 24'h4503_10 ;
		mem[219]= 24'h4508_aa ;
		mem[220]= 24'h4509_aa ;
		mem[221]= 24'h450a_00 ;
		mem[222]= 24'h450b_00 ;
		mem[223]= 24'h4600_00 ;
		mem[224]= 24'h4601_c0 ;
		mem[225]= 24'h4700_a4 ;
		mem[226]= 24'h4800_4c ;
		mem[227]= 24'h4816_53 ;
		mem[228]= 24'h481f_40 ;
		mem[229]= 24'h4837_13 ;
		mem[230]= 24'h5000_56 ;
		mem[231]= 24'h5001_01 ;
		mem[232]= 24'h5002_28 ;
		mem[233]= 24'h5004_0c ;
		mem[234]= 24'h5006_0c ;
		mem[235]= 24'h5007_e0 ;
		mem[236]= 24'h5008_01 ;
		mem[237]= 24'h5009_b0 ;
        mem[238]= 24'h5901_00 ;
		mem[239]= 24'h5a01_00 ;
		mem[240]= 24'h5a03_00 ;
		mem[241]= 24'h5a04_0c ;
		mem[242]= 24'h5a05_e0 ;
		mem[243]= 24'h5a06_09 ;
		mem[244]= 24'h5a07_b0 ;
		mem[245]= 24'h5a08_06 ;
		mem[246]= 24'h5e00_00 ;
		mem[247]= 24'h3734_40 ;
		mem[248]= 24'h5b00_01 ;
        mem[249]= 24'h5b01_10 ;
		mem[250]= 24'h5b02_01 ;
		mem[251]= 24'h5b03_db ;
		mem[252]= 24'h3d8c_71 ;
		mem[253]= 24'h3d8d_ea ;
		mem[254]= 24'h4017_08 ;
		mem[255]= 24'h380c_08 ;     //
		mem[256]= 24'h380d_98 ;     // horizontal total size: 0x05f8---1528, 0x0898 ----2200 , 0x0852: ---2130
		mem[257]= 24'h370b_05 ;
		mem[258]= 24'h400a_01 ;
		mem[259]= 24'h400b_62 ;
        mem[260]= 24'h3618_2a ;
		mem[261]= 24'h5780_3e ;
		mem[262]= 24'h5781_0f ;
		mem[263]= 24'h5782_44 ;
		mem[264]= 24'h5783_02 ;
		mem[265]= 24'h5784_01 ;
		mem[266]= 24'h5785_01 ;
		mem[267]= 24'h5786_00 ;
		mem[268]= 24'h5787_04 ;
		mem[269]= 24'h5788_02 ;
		mem[270]= 24'h5789_0f ;
        mem[271]= 24'h578a_fd ;
		mem[272]= 24'h578b_f5 ;
		mem[273]= 24'h578c_f5 ;
		mem[274]= 24'h578d_03 ;
		mem[275]= 24'h578e_08 ;
		mem[276]= 24'h578f_0c ;
		mem[277]= 24'h5790_08 ;
		mem[278]= 24'h5791_06 ;
		mem[279]= 24'h5792_00 ;
		mem[280]= 24'h5793_52 ;
		mem[281]= 24'h5794_a3 ;
        mem[282]= 24'h3503_00 ;
        mem[283]= 24'h380e_05 ;     //
        mem[284]= 24'h380f_dc ;     // vertical total size: 0x0460: ---1120 ,0x0465 ---1125 , 0x05dc: ---1500
        mem[285]= 24'h3002_61 ;
        mem[286]= 24'h3010_40 ;
        mem[287]= 24'h300D_00 ;
        mem[288]= 24'h5045_05 ;
        mem[289]= 24'h5048_10 ;
        mem[290]= 24'h0100_01 ;       
    end

    reg [23:0] q ;
    always @ (posedge CLK) begin
        q  <= #1  mem[AD] ;
    end
    assign DO = q ;

endmodule 






//=================================================================================
`ifdef ST7789V 
// RAM Initial
    initial begin
      ram_data[00] = 16'h0011;     // Sleep Out 
      ram_rs  [00] =  1'b0   ;
    	
      ram_data[01] = 16'h003A;     // Interface Pixel Format
      ram_rs  [01] =  1'b0   ;      	
      ram_data[02] = 16'h0005;     // 16 bits per pixel 
      ram_rs  [02] =  1'b1   ;
    			
      ram_data[03] = 16'h0036;//Memory Data Access Control,
      ram_rs  [03] =  1'b0   ;
      ram_data[04] = 16'h0000;//Top to Bottom/Left to Right---RGB set bit[3] 0:RGB 1:BGR 
      ram_rs  [04] =  1'b1   ;
      
// porch setting(use default)     
      ram_data[05] = 16'h0000; //---ram_data[05] = 16'h00B2;
      ram_rs  [05] =  1'b0   ; //---ram_rs  [05] =  1'b0   ;      
      ram_data[06] = 16'h0000; //---ram_data[06] = 16'h0008;     
      ram_rs  [06] =  1'b0   ; //---ram_rs  [06] =  1'b1   ;   
      ram_data[07] = 16'h0000; //---ram_data[07] = 16'h0008;     
      ram_rs  [07] =  1'b0   ; //---ram_rs  [07] =  1'b1   ;   
      ram_data[08] = 16'h0000; //---ram_data[08] = 16'h0000;     
      ram_rs  [08] =  1'b0   ; //---ram_rs  [08] =  1'b1   ;   
      ram_data[09] = 16'h0000; //---ram_data[09] = 16'h0022;     
      ram_rs  [09] =  1'b0   ; //---ram_rs  [09] =  1'b1   ;   
      ram_data[10] = 16'h0000; //---ram_data[10] = 16'h0022;     
      ram_rs  [10] =  1'b0   ; //---ram_rs  [10] =  1'b1   ;   

//Gata Control--set"VGH","VGL"--default value "0x35"
      ram_data[11] = 16'h0000; //ram_data[11] = 16'h00B7;
      ram_rs  [11] =  1'b0   ; //ram_rs  [11] =  1'b0   ;    
      ram_data[12] = 16'h0000; //ram_data[12] = 16'h0035;     
      ram_rs  [12] =  1'b0   ; //ram_rs  [12] =  1'b1   ;

//No Found registrt
      ram_data[13] = 16'h0000; //---ram_data[13] = 16'h00B8;     
      ram_rs  [13] =  1'b0   ; //---ram_rs  [13] =  1'b0   ;
      ram_data[14] = 16'h0000; //---ram_data[14] = 16'h002F;
      ram_rs  [14] =  1'b0   ; //---ram_rs  [14] =  1'b1   ;
      ram_data[15] = 16'h0000; //---ram_data[15] = 16'h002B; 
      ram_rs  [15] =  1'b0   ; //---ram_rs  [15] =  1'b1   ;
      ram_data[16] = 16'h0000; //---ram_data[16] = 16'h002F;
      ram_rs  [16] =  1'b0   ; //---ram_rs  [16] =  1'b1   ;

// VCOM Setting--default "0x20" ---0.9v ;use"0x24" --1.0v   
      ram_data[17] = 16'h0000; //---ram_data[17] = 16'h00BB;     
      ram_rs  [17] =  1'b0   ; //---ram_rs  [17] =  1'b0   ;
      ram_data[18] = 16'h0000; //---ram_data[18] = 16'h0024;
      ram_rs  [18] =  1'b0   ; //---ram_rs  [18] =  1'b1   ;
// LCM Control
      ram_data[19] = 16'h0000; //---ram_data[19] = 16'h00C0;     
      ram_rs  [19] =  1'b0   ; //---ram_rs  [19] =  1'b0   ;
      ram_data[20] = 16'h0000; //---ram_data[20] = 16'h002C;     
      ram_rs  [20] =  1'b0   ; //---ram_rs  [20] =  1'b1   ;
// VRH Control
      ram_data[21] = 16'h0000; //---ram_data[21] = 16'h00C3;     
      ram_rs  [21] =  1'b0   ; //---ram_rs  [21] =  1'b0   ;
      ram_data[22] = 16'h0000; //---ram_data[22] = 16'h0010;    
      ram_rs  [22] =  1'b0   ; //---ram_rs  [22] =  1'b1   ;
// VDV Setting 
      ram_data[23] = 16'h0000; //---ram_data[23] = 16'h00C4;     
      ram_rs  [23] =  1'b0   ; //---ram_rs  [23] =  1'b0   ;
      ram_data[24] = 16'h0000; //---ram_data[24] = 16'h0020;     
      ram_rs  [24] =  1'b0   ; //---ram_rs  [24] =  1'b1   ;

      
      ram_data[25] = 16'h00C6;     // Frame Rate Control
      ram_rs  [25] =  1'b0   ;
      ram_data[26] = 16'h0009;     // 16'H0011 
      ram_rs  [26] =  1'b1   ;

      ram_data[27] = 16'h00D0;     // Power Control 1
      ram_rs  [27] =  1'b0   ;
      ram_data[28] = 16'h00A4;
      ram_rs  [28] =  1'b1   ;
      ram_data[29] = 16'h00A1;
      ram_rs  [29] =  1'b1   ; 

      ram_data[30] = 16'h00E8;     // Power Control 2
      ram_rs  [30] =  1'b0   ;
      ram_data[31] = 16'h0003;
      ram_rs  [31] =  1'b1   ;

      ram_data[32] = 16'h00E9;     // Equalize Time Control
      ram_rs  [32] =  1'b0   ;
      ram_data[33] = 16'h000D;
      ram_rs  [33] =  1'b1   ;
      ram_data[34] = 16'h0012;
      ram_rs  [34] =  1'b1   ;
      ram_data[35] = 16'h0000;
      ram_rs  [35] =  1'b1   ;
// Positive Voltage Gamma Control
      ram_data[36] = 16'h0000; //---ram_data[36] = 16'h00E0;     
      ram_rs  [36] =  1'b0   ; //---ram_rs  [36] =  1'b0   ;
      ram_data[37] = 16'h0000; //---ram_data[37] = 16'h00D0;   
      ram_rs  [37] =  1'b0   ; //---ram_rs  [37] =  1'b1   ;
      ram_data[38] = 16'h0000; //---ram_data[38] = 16'h0000;   
      ram_rs  [38] =  1'b0   ; //---ram_rs  [38] =  1'b1   ;
      ram_data[39] = 16'h0000; //---ram_data[39] = 16'h0000;   
      ram_rs  [39] =  1'b0   ; //---ram_rs  [39] =  1'b1   ;
      ram_data[40] = 16'h0000; //---ram_data[40] = 16'h0008;   
      ram_rs  [40] =  1'b0   ; //---ram_rs  [40] =  1'b1   ;
      ram_data[41] = 16'h0000; //---ram_data[41] = 16'h0011;   
      ram_rs  [41] =  1'b0   ; //---ram_rs  [41] =  1'b1   ;
      ram_data[42] = 16'h0000; //---ram_data[42] = 16'h001A;   
      ram_rs  [42] =  1'b0   ; //---ram_rs  [42] =  1'b1   ;
      ram_data[43] = 16'h0000; //---ram_data[43] = 16'h002B;   
      ram_rs  [43] =  1'b0   ; //---ram_rs  [43] =  1'b1   ;
      ram_data[44] = 16'h0000; //---ram_data[44] = 16'h0033;   
      ram_rs  [44] =  1'b0   ; //---ram_rs  [44] =  1'b1   ;
      ram_data[45] = 16'h0000; //---ram_data[45] = 16'h0042;   
      ram_rs  [45] =  1'b0   ; //---ram_rs  [45] =  1'b1   ;
      ram_data[46] = 16'h0000; //---ram_data[46] = 16'h0026;   
      ram_rs  [46] =  1'b0   ; //---ram_rs  [46] =  1'b1   ;
      ram_data[47] = 16'h0000; //---ram_data[47] = 16'h0012;   
      ram_rs  [47] =  1'b0   ; //---ram_rs  [47] =  1'b1   ;
      ram_data[48] = 16'h0000; //---ram_data[48] = 16'h0021;   
      ram_rs  [48] =  1'b0   ; //---ram_rs  [48] =  1'b1   ;
      ram_data[49] = 16'h0000; //---ram_data[49] = 16'h002F;   
      ram_rs  [49] =  1'b0   ; //---ram_rs  [49] =  1'b1   ;      
      ram_data[50] = 16'h0000; //---ram_data[50] = 16'h0011;   
      ram_rs  [50] =  1'b0   ; //---ram_rs  [50] =  1'b1   ;

// Negative Voltage Gamma Control      
      ram_data[51] = 16'h0000; //---ram_data[51] = 16'h00E1;     
      ram_rs  [51] =  1'b0   ; //---ram_rs  [51] =  1'b0   ;
      ram_data[52] = 16'h0000; //---ram_data[52] = 16'h00D0;   
      ram_rs  [52] =  1'b0   ; //---ram_rs  [52] =  1'b1   ;
      ram_data[53] = 16'h0000; //---ram_data[53] = 16'h0002;   
      ram_rs  [53] =  1'b0   ; //---ram_rs  [53] =  1'b1   ;
      ram_data[54] = 16'h0000; //---ram_data[54] = 16'h0009;   
      ram_rs  [54] =  1'b0   ; //---ram_rs  [54] =  1'b1   ;
      ram_data[55] = 16'h0000; //---ram_data[55] = 16'h000D;   
      ram_rs  [55] =  1'b0   ; //---ram_rs  [55] =  1'b1   ;
      ram_data[56] = 16'h0000; //---ram_data[56] = 16'h000D;   
      ram_rs  [56] =  1'b0   ; //---ram_rs  [56] =  1'b1   ;
      ram_data[57] = 16'h0000; //---ram_data[57] = 16'h0027;   
      ram_rs  [57] =  1'b0   ; //---ram_rs  [57] =  1'b1   ;
      ram_data[58] = 16'h0000; //---ram_data[58] = 16'h002B;   
      ram_rs  [58] =  1'b0   ; //---ram_rs  [58] =  1'b1   ;
      ram_data[59] = 16'h0000; //---ram_data[59] = 16'h0033;   
      ram_rs  [59] =  1'b0   ; //---ram_rs  [59] =  1'b1   ;
      ram_data[60] = 16'h0000; //---ram_data[60] = 16'h0042;   
      ram_rs  [60] =  1'b0   ; //---ram_rs  [60] =  1'b1   ;
      ram_data[61] = 16'h0000; //---ram_data[61] = 16'h0017;   
      ram_rs  [61] =  1'b0   ; //---ram_rs  [61] =  1'b1   ;
      ram_data[62] = 16'h0000; //---ram_data[62] = 16'h0012;   
      ram_rs  [62] =  1'b0   ; //---ram_rs  [62] =  1'b1   ;
      ram_data[63] = 16'h0000; //---ram_data[63] = 16'h0011;   
      ram_rs  [63] =  1'b0   ; //---ram_rs  [63] =  1'b1   ;
      ram_data[64] = 16'h0000; //---ram_data[64] = 16'h002F;   
      ram_rs  [64] =  1'b0   ; //---ram_rs  [64] =  1'b1   ;      
      ram_data[65] = 16'h0000; //---ram_data[65] = 16'h0031;   
      ram_rs  [65] =  1'b0   ; //---ram_rs  [65] =  1'b1   ;

      
      ram_data[66] = 16'h0021;     // Display Inversion On
      ram_rs  [66] =  1'b0   ;
  
      ram_data[67] = 16'h002A;     // Column Address Set
      ram_rs  [67] =  1'b0   ;
      ram_data[68] = 16'h0000;   
      ram_rs  [68] =  1'b1   ;
      ram_data[69] = 16'h0000;   
      ram_rs  [69] =  1'b1   ;
      ram_data[70] = 16'h0000;   
      ram_rs  [70] =  1'b1   ;      
      ram_data[71] = 16'h00EF;   
      ram_rs  [71] =  1'b1   ;      
      
      ram_data[72] = 16'h002B;     // Row Address Set
      ram_rs  [72] =  1'b0   ;
      ram_data[73] = 16'h0000;   
      ram_rs  [73] =  1'b1   ;
      ram_data[74] = 16'h0000;   
      ram_rs  [74] =  1'b1   ;
      ram_data[75] = 16'h0001;   
      ram_rs  [75] =  1'b1   ;      
      ram_data[76] = 16'h003F;   
      ram_rs  [76] =  1'b1   ; 
		
      ram_data[77] = 16'h0029;     // Display Inversion Off
      ram_rs  [77] =  1'b0   ;  

    end
    
`else

  initial begin
//002C is write memory!!
//003C IS CONTINUE WRITE MEMORY

//------  software reset,power up,must reset     
//ram_data  [1 ] = 16'h0001  ; 
//ram_rs    [1 ] = 1'h0      ;    
     ram_data  [1 ] = 16'h0011  ; 
     ram_rs    [1 ] = 1'h0      ;//####       delay 120ms    #####      
//------  Exit Sleep                 
     ram_data  [2 ] = 16'h0000  ; //'h0011
	 ram_rs    [2 ] = 1'h0      ;
     
//------  power  control B           ----                        
     ram_data  [3 ] = 16'h00CF    ;//my: 16'h00CF  
	 ram_rs    [3 ] =  1'h0       ;//my:  1'h0                                      
     ram_data  [4 ] = 16'h0000    ;//my: 16'h0000  
	 ram_rs    [4 ] =  1'h1       ;//my:  1'h1         
     ram_data  [5 ] = 16'h00C1    ;//my: 16'h0081  
	 ram_rs    [5 ] =  1'h1       ;//my:  1'h1                                     
     ram_data  [6 ] = 16'h0030    ;//my: 16'h00C0 
	 ram_rs    [6 ] =  1'h1       ;//my:  1'h1    
     
//------  power sequnece control     -----     
     ram_data  [7 ] = 16'h00ED    ;//my:  16'h00ED 
	 ram_rs    [7 ] =  1'h0       ;//my:   1'h0   
     ram_data  [8 ] = 16'h0064    ;//my:  16'h0064 
	 ram_rs    [8 ] =  1'h1       ;//my:   1'h1   
     ram_data  [9 ] = 16'h0003    ;//my:  16'h0003 
	 ram_rs    [9 ] =  1'h1       ;//my:   1'h1   
     ram_data  [10] = 16'h0012    ;//my:  16'h0012 
	 ram_rs    [10] =  1'h1       ;//my:   1'h1   
     ram_data  [11] = 16'h0081    ;//my:  16'h0081 
	 ram_rs    [11] =  1'h1       ;//my:   1'h1   
     
//------  driver timing  control A   -----
     ram_data  [12] = 16'h00E8    ;//my:  16'h00E8 ----
	 ram_rs    [12] =  1'h0       ;//my:   1'h0    ----
     ram_data  [13] = 16'h0085    ;//my:  16'h0085 ---- // EQ timing for internal clock
	 ram_rs    [13] =  1'h1       ;//my:   1'h1    ----
     ram_data  [14] = 16'h0000    ;//my:  16'h0001 ---- // EQ timing control 
	 ram_rs    [14] =  1'h1       ;//my:   1'h1    ----
     ram_data  [15] = 16'h007A    ;//my:  16'h0798 ---- // pre-charge timing control 
	 ram_rs    [15] =  1'h1       ;//my:   1'h1    ----
     
//------  power  control A           ----         
     ram_data  [16] = 16'h00CB    ;//my:  16'h00CB    
	 ram_rs    [16] =  1'h0       ;//my:   1'h0                                       
     ram_data  [17] = 16'h0039    ;//my:  16'h0039   
	 ram_rs    [17] =  1'h1       ;//my:   1'h1                                      
     ram_data  [18] = 16'h002C    ;//my:  16'h002C   
	 ram_rs    [18] =  1'h1       ;//my:   1'h1     
     ram_data  [19] = 16'h0000    ;//my:  16'h0000   
	 ram_rs    [19] =  1'h1       ;//my:   1'h1                                      
     ram_data  [20] = 16'h0034    ;//my:  16'h0034   
	 ram_rs    [20] =  1'h1       ;//my:   1'h1                                       
     ram_data  [21] = 16'h0002    ;//my:  16'h0002   
	 ram_rs    [21] =  1'h1       ;//my:   1'h1     
     
//------  pump ratio control         ----              
     ram_data  [22] = 16'h00F7    ;//my:  16'h00F7 
	 ram_rs    [22] =  1'h0       ;//my:   1'h0                                    
     ram_data  [23] = 16'h0020    ;//my:  16'h0020 
	 ram_rs    [23] =  1'h1       ;//my:   1'h1    
     
//------  driver timing  control B   -----             
     ram_data  [24] = 16'h00EA    ;//my:  16'h00EA   
	 ram_rs    [24] =  1'h0       ;//my:   1'h0                                       
     ram_data  [25] = 16'h0000    ;//my:  16'h0000   
	 ram_rs    [25] =  1'h1       ;//my:   1'h1     
     ram_data  [26] = 16'h0000    ;//my:  16'h0000   
	 ram_rs    [26] =  1'h1       ;//my:   1'h1     

//------  frame rate control (in normal mode/full colors)     
     ram_data  [27] = 16'h00B1    ;//my:  16'h00B1  ---- 
	 ram_rs    [27] =  1'h0       ;//my:   1'h0     ----
     ram_data  [28] = 16'h0000    ;//my:  16'h0000  ----//00:fosc 
	 ram_rs    [28] =  1'h1       ;//my:   1'h1     ----                                 
     ram_data  [29] = 16'h001B    ;//my:  16'h001B  ----//default `b11011 
	 ram_rs    [29] =  1'h1       ;//my:   1'h1     ----

//------  display function control  ----        
     ram_data  [30] = 16'h00B6    ;//my:  16'h00B6  
	 ram_rs    [30] =  1'h0       ;//my:   1'h0                                      
     ram_data  [31] = 16'h000A    ;//my:  16'h000A  
	 ram_rs    [31] =  1'h1       ;//my:   1'h1    
     ram_data  [32] = 16'h00A2    ;//my:  16'h00A2  
	 ram_rs    [32] =  1'h1       ;//my:   1'h1    

//------  power control 1            ----       
     ram_data  [33] = 16'h00C0    ;//my:   16'h00C0 ----
	 ram_rs    [33] =  1'h0       ;//my:    1'h0    ----
     ram_data  [34] = 16'h0021    ;//my:   16'h0005 ---- //VRH[5:0]
	 ram_rs    [34] =  1'h1       ;//my:    1'h1    ----

//------  power control 2            ----      
     ram_data  [35] = 16'h00C1    ;//my:   16'h00C1---- 
	 ram_rs    [35] =  1'h0       ;//my:    1'h0   ----
     ram_data  [36] = 16'h0011    ;//my:   16'h0011---- //SAP[2:0];BT[3:0] 
	 ram_rs    [36] =  1'h1       ;//my:    1'h1   ----
     
//-- 0xC5 -- VCOM control 1          
     ram_data  [37] = 16'h00C5    ;//my:   16'h00C5 ---- 
	 ram_rs    [37] =  1'h0       ;//my:    1'h0    ----
     ram_data  [38] = 16'h0031    ;//my:   16'h0045 ---- //3f
	 ram_rs    [38] =  1'h1       ;//my:    1'h1    ----
     ram_data  [39] = 16'h001B    ;//my:   16'h0045 ---- //3c----for image display fine(light)
	 ram_rs    [39] =  1'h1       ;//my:    1'h1    ----

//------  VCOM control 2             ----       
     ram_data  [40] = 16'h00C7    ;//my:   16'h00C7 ---- //DISPLAY FUNCTION CONTROL
	 ram_rs    [40] =  1'h0       ;//my:    1'h0    ----
     ram_data  [41] = 16'h009F    ;//my:   16'h00A2 ---- ----for image display fine
	 ram_rs    [41] =  1'h1       ;//my:    1'h1    ----
     
//------  memory access control      ----                   
     ram_data  [42] = 16'h0036    ;//my:  16'h0036   
	 ram_rs    [42] =  1'h0       ;//my:   1'h0     
     ram_data  [43] = 16'h0039    ;//my:  16'h0008   
	 ram_rs    [43] =  1'h1       ;//my:   1'h1     
     
//------  enable 3G--unuse             
     ram_data  [44] = 16'h00F2    ;//my:   16'h00F2  
	 ram_rs    [44] = 1'h0        ;//my:   1'h0                                        
     ram_data  [45] = 16'h0000    ;//my:   16'h0000  ---//Disable 
	 ram_rs    [45] = 1'h1        ;//my:   1'h1      

//------  Gamma curve selected       ----     
     ram_data  [46] = 16'h0026    ;//my:  16'h0026 
	 ram_rs    [46] =  1'h0       ;//my:   1'h0                                     
     ram_data  [47] = 16'h0001    ;//my:  16'h0001 
	 ram_rs    [47] =  1'h0       ;//my:   1'h1    
     
//------  Set Gamma   1              ----               
     ram_data  [48] = 16'h00E0    ;//my: 16'h00E0   
	 ram_rs    [48] =  1'h0       ;//my:  1'h0                                       
     ram_data  [49] = 16'h000F    ;//my: 16'h000F   
	 ram_rs    [49] =  1'h1       ;//my:  1'h1     
     ram_data  [50] = 16'h0020    ;//my: 16'h0026   
	 ram_rs    [50] =  1'h1       ;//my:  1'h1                                      
     ram_data  [51] = 16'h001d    ;//my: 16'h0024   
	 ram_rs    [51] =  1'h1       ;//my:  1'h1     
     ram_data  [52] = 16'h000B    ;//my: 16'h000B   
	 ram_rs    [52] =  1'h1       ;//my:  1'h1                                       
     ram_data  [53] = 16'h0010    ;//my: 16'h000E   
	 ram_rs    [53] =  1'h1       ;//my:  1'h1     
     ram_data  [54] = 16'h000A    ;//my: 16'h0008   
	 ram_rs    [54] =  1'h1       ;//my:  1'h1                                       
     ram_data  [55] = 16'h0049    ;//my: 16'h004B   
	 ram_rs    [55] =  1'h1       ;//my:  1'h1     
     ram_data  [56] = 16'h00A9    ;//my: 16'h00A8   
	 ram_rs    [56] =  1'h1       ;//my:  1'h1                                       
     ram_data  [57] = 16'h003B    ;//my: 16'h003B   
	 ram_rs    [57] =  1'h1       ;//my:  1'h1     
     ram_data  [58] = 16'h000A    ;//my: 16'h000A   
	 ram_rs    [58] =  1'h1       ;//my:  1'h1                                       
     ram_data  [59] = 16'h0015    ;//my: 16'h0014   
	 ram_rs    [59] =  1'h1       ;//my:  1'h1     
     ram_data  [60] = 16'h0006    ;//my: 16'h0006   
	 ram_rs    [60] =  1'h1       ;//my:  1'h1                                       
     ram_data  [61] = 16'h000C    ;//my: 16'h0010  
	 ram_rs    [61] =  1'h1       ;//my:  1'h1     
     ram_data  [62] = 16'h0006    ;//my: 16'h0009   
	 ram_rs    [62] =  1'h1       ;//my:  1'h1                                       
     ram_data  [63] = 16'h0000    ;//my: 16'h0000   
	 ram_rs    [63] =  1'h1       ;//my:  1'h1     
     
//------  Set Gamma   2              ----        
     ram_data  [64] = 16'h00E1    ;//my:  16'h00E1  
	 ram_rs    [64] =  1'h0       ;//my:   1'h0                                      
     ram_data  [65] = 16'h0000    ;//my:  16'h0000  
	 ram_rs    [65] =  1'h1       ;//my:   1'h1    
     ram_data  [66] = 16'h001F    ;//my:  16'h001C  
	 ram_rs    [66] =  1'h1       ;//my:   1'h1    
     ram_data  [67] = 16'h0022    ;//my:  16'h0020  
	 ram_rs    [67] =  1'h1       ;//my:   1'h1                                     
     ram_data  [68] = 16'h0004    ;//my:  16'h0004  
	 ram_rs    [68] =  1'h1       ;//my:   1'h1    
     ram_data  [69] = 16'h000F    ;//my:  16'h0010  
	 ram_rs    [69] =  1'h1       ;//my:   1'h1                                      
     ram_data  [70] = 16'h0005    ;//my:  16'h0008 
	 ram_rs    [70] =  1'h1       ;//my:   1'h1    
     ram_data  [71] = 16'h0036    ;//my:  16'h0034  
	 ram_rs    [71] =  1'h1       ;//my:   1'h1    
     ram_data  [72] = 16'h0046    ;//my:  16'h0047  
	 ram_rs    [72] =  1'h1       ;//my:   1'h1    
     ram_data  [73] = 16'h0046    ;//my:  16'h0044  
	 ram_rs    [73] =  1'h1       ;//my:   1'h1                                     
     ram_data  [74] = 16'h0005    ;//my:  16'h0005  
	 ram_rs    [74] =  1'h1       ;//my:   1'h1    
     ram_data  [75] = 16'h000B    ;//my:  16'h000B  
	 ram_rs    [75] =  1'h1       ;//my:   1'h1                                      
     ram_data  [76] = 16'h0009    ;//my:  16'h0009  
	 ram_rs    [76] =  1'h1       ;//my:   1'h1    
     ram_data  [77] = 16'h0033    ;//my:  16'h002F  
	 ram_rs    [77] =  1'h1       ;//my:   1'h1    
     ram_data  [78] = 16'h0039    ;//my:  16'h0036  
	 ram_rs    [78] =  1'h1       ;//my:   1'h1                                     
     ram_data  [79] = 16'h000F    ;//my:  16'h000F  
	 ram_rs    [79] =  1'h1       ;//my:   1'h1    
     
//------  column address sel       ----               
     ram_data  [80] = 16'h002A    ;//my:  16'h002A 
	 ram_rs    [80] =  1'h0       ;//my:   1'h0                                     
     ram_data  [81] = 16'h0000    ;//my:  16'h0000
	 ram_rs    [81] =  1'h1       ;//my:   1'h1   
     ram_data  [82] = 16'h0000    ;//my:  16'h0000 
	 ram_rs    [82] =  1'h1       ;//my:   1'h1   
     ram_data  [83] = 16'h0000    ;//my:  16'h0000 
	 ram_rs    [83] =  1'h1       ;//my:   1'h1   
     ram_data  [84] = 16'h00EF    ;//my:  16'h00EF 
	 ram_rs    [84] =  1'h1       ;//my:   1'h1    

//------  page address sel         ----      
     ram_data  [85] = 16'h002B    ;//my:  16'h002B 
	 ram_rs    [85] =  1'h0       ;//my:   1'h0        
     ram_data  [86] = 16'h0000    ;//my:  16'h0000 
	 ram_rs    [86] =  1'h1       ;//my:   1'h1        
     ram_data  [87] = 16'h0000    ;//my:  16'h0000 
	 ram_rs    [87] =  1'h1       ;//my:   1'h1        
     ram_data  [88] = 16'h0001    ;//my:  16'h0001 
	 ram_rs    [88] =  1'h1       ;//my:   1'h1        
     ram_data  [89] = 16'h003F    ;//my:  16'h003F 
	 ram_rs    [89] =  1'h1       ;//my:   1'h1    
 
//------  COLMOD:Pixel format set  ----  
     ram_data  [90] = 16'h003A    ;//my: 16'h003A   
	 ram_rs    [90] =  1'h0       ;//my:  1'h0           
     ram_data  [91] = 16'h0055    ;//my: 16'h0005   
	 ram_rs    [91] =  1'h1       ;//my:  1'h1     

//------  COLMOD:Pixel format set  ----      
     ram_data  [92] =  16'h00f6   ;//my:  16'h00f6
	 ram_rs    [92] =   1'h0      ;//my:   1'h0       
     ram_data  [93] =  16'h0001   ;//my:  16'h0001 
	 ram_rs    [93] =   1'h1      ;//my:   1'h1        
     ram_data  [94] =  16'h0030   ;//my:  16'h0030 
	 ram_rs    [94] =   1'h1      ;//my:   1'h1        
     ram_data  [95] =  16'h0000   ;//my:  16'h0000 
	 ram_rs    [95] =   1'h1      ;//my:   1'h1   

//------  display ON               ----      
     ram_data  [96] = 16'h0029    ; 
	 ram_rs    [96] =  1'h0       ;
     
//------  display memory write     ----      
     ram_data  [97] = 16'h002c    ;
	 ram_rs    [97] =  1'h0       ;          
//------add register --------------
     ram_data  [98] = 16'h00B1    ;
	 ram_rs    [98] =  1'h0       ; 
     ram_data  [99] = 16'h0000    ;
	 ram_rs    [99] =  1'h1       ;      
     ram_data  [100]= 16'h001B    ;
	 ram_rs    [100]=  1'h1       ;      
     
     ram_data  [101] = 16'h00B6   ;
	 ram_rs    [101] =  1'h0      ;      
     
  end
`endif
  
endmodule


















    