#include "menu.h"
#include "string.h"

int line=0, page=0, menu_count=0, start_symbol=0;

uint16_t flash_data[menu_num+1]={0};


struct Menu Menu_Choose[menu_num];

void menu()
{
	int i=0;
	for(i=0;i<menu_num;i++)
	{
		flash_data[i] = flash_read(sector_num,i*2,uint16);
	}
	menu_Init();
	while(1)
	{
		 menu_key();
		 menu_display();
		 if(start_symbol==1)
			 break;
	}	
}


void menu_Init()
{
#if (menu_num >= 1)
	strcpy(Menu_Choose[0].name, name0);
	Menu_Choose[0].num = flash_data[0];
	Menu_Choose[0].multiple=multiple0;
	Menu_Choose[0].multiple_display=multiple_display0;
#endif
	
#if (menu_num >= 2)
	strcpy(Menu_Choose[1].name, name1);
	Menu_Choose[1].num = flash_data[1];
	Menu_Choose[1].multiple=multiple1;
	Menu_Choose[1].multiple_display=multiple_display1;
#endif
	
#if (menu_num >= 3)
	strcpy(Menu_Choose[2].name, name2);
	Menu_Choose[2].num = flash_data[2];
	Menu_Choose[2].multiple=multiple2;
	Menu_Choose[2].multiple_display=multiple_display2;
#endif

#if (menu_num >= 4)
	strcpy(Menu_Choose[3].name, name3);
	Menu_Choose[3].num = flash_data[3];
	Menu_Choose[3].multiple=multiple3;
	Menu_Choose[3].multiple_display=multiple_display3;
#endif

#if (menu_num >= 5)
	strcpy(Menu_Choose[4].name, name4);
	Menu_Choose[4].num = flash_data[4];
	Menu_Choose[4].multiple=multiple4;
	Menu_Choose[4].multiple_display=multiple_display4;
#endif
	
#if (menu_num >= 6)
	strcpy(Menu_Choose[5].name, name5);
	Menu_Choose[5].num = flash_data[5];
	Menu_Choose[5].multiple=multiple5;
	Menu_Choose[5].multiple_display=multiple_display5;
#endif
	
#if (menu_num >= 7)
	strcpy(Menu_Choose[6].name, name6);
	Menu_Choose[6].num = flash_data[6];
	Menu_Choose[6].multiple=multiple6;
	Menu_Choose[6].multiple_display=multiple_display6;
#endif
	
#if (menu_num >= 8)
  strcpy(Menu_Choose[7].name, name7);
	Menu_Choose[7].num = flash_data[7];
	Menu_Choose[7].multiple=multiple7;
	Menu_Choose[7].multiple_display=multiple_display7;
#endif
	
#if (menu_num >= 9)
	strcpy(Menu_Choose[8].name, name8);
	Menu_Choose[8].num = flash_data[8];
	Menu_Choose[8].multiple=multiple8;
	Menu_Choose[8].multiple_display=multiple_display8;
#endif
	
#if (menu_num >= 10)
	strcpy(Menu_Choose[9].name, name9);
	Menu_Choose[9].num = flash_data[9];
	Menu_Choose[9].multiple=multiple9;
	Menu_Choose[9].multiple_display=multiple_display9;
#endif

#if (menu_num >= 11)
	strcpy(Menu_Choose[10].name, name10);
	Menu_Choose[10].num = flash_data[10];
	Menu_Choose[10].multiple=multiple10;
	Menu_Choose[10].multiple_display=multiple_display10;
#endif
	
#if (menu_num >= 12)
	strcpy(Menu_Choose[11].name, name11);
	Menu_Choose[11].num = flash_data[11];
	Menu_Choose[11].multiple=multiple11;
	Menu_Choose[11].multiple_display=multiple_display11;
#endif

#if (menu_num >= 13)
	strcpy(Menu_Choose[12].name, name12);
	Menu_Choose[12].num = flash_data[12];
	Menu_Choose[12].multiple=multiple12;
	Menu_Choose[12].multiple_display=multiple_display12;
#endif
	
#if (menu_num >= 14)
	strcpy(Menu_Choose[13].name, name13);
	Menu_Choose[13].num = flash_data[13];
	Menu_Choose[13].multiple=multiple13;
	Menu_Choose[13].multiple_display=multiple_display13;
#endif
	
#if (menu_num >= 15)
	strcpy(Menu_Choose[14].name, name14);
	Menu_Choose[14].num = flash_data[14];
	Menu_Choose[14].multiple=multiple14;
	Menu_Choose[14].multiple_display=multiple_display14;
#endif
	
#if (menu_num >= 16)
	strcpy(Menu_Choose[15].name, name15);
	Menu_Choose[15].num = flash_data[15];
	Menu_Choose[15].multiple=multiple15;
	Menu_Choose[15].multiple_display=multiple_display15;
#endif

#if (menu_num >= 17)
	strcpy(Menu_Choose[16].name, name16);
	Menu_Choose[16].num = flash_data[16];
	Menu_Choose[16].multiple=multiple16;
	Menu_Choose[16].multiple_display=multiple_display16;
#endif
	
#if (menu_num >= 18)
	strcpy(Menu_Choose[17].name, name17);
	Menu_Choose[17].num = flash_data[17];
	Menu_Choose[17].multiple=multiple17;
	Menu_Choose[17].multiple_display=multiple_display17;
#endif
	
#if (menu_num >= 19)
	strcpy(Menu_Choose[18].name, name18);
	Menu_Choose[18].num = flash_data[18];
	Menu_Choose[18].multiple=multiple18;
	Menu_Choose[18].multiple_display=multiple_display18;
#endif
	
#if (menu_num >= 20)
	strcpy(Menu_Choose[19].name, name19);
	Menu_Choose[19].num = flash_data[19];
	Menu_Choose[19].multiple=multiple19;
	Menu_Choose[19].multiple_display=multiple_display19;
#endif

#if (menu_num >= 21)
	strcpy(Menu_Choose[20].name, name20);
	Menu_Choose[20].num = flash_data[20];
	Menu_Choose[20].multiple=multiple20;
	Menu_Choose[20].multiple_display=multiple_display20;
#endif
	
#if (menu_num >= 22)
	strcpy(Menu_Choose[21].name, name21);
	Menu_Choose[21].num = flash_data[21];
	Menu_Choose[21].multiple=multiple21;
	Menu_Choose[21].multiple_display=multiple_display21;
#endif
	
#if (menu_num >= 23)
	strcpy(Menu_Choose[22].name, name22);
	Menu_Choose[22].num = flash_data[22];
	Menu_Choose[22].multiple=multiple22;
	Menu_Choose[22].multiple_display=multiple_display22;
#endif
	
#if (menu_num >= 24)
	strcpy(Menu_Choose[23].name, name23);
	Menu_Choose[23].num = flash_data[23];
	Menu_Choose[23].multiple=multiple23;
	Menu_Choose[23].multiple_display=multiple_display23;
#endif
	
#if (menu_num >= 25)
	strcpy(Menu_Choose[24].name, name24);
	Menu_Choose[24].num = flash_data[24];
	Menu_Choose[24].multiple=multiple24;
	Menu_Choose[24].multiple_display=multiple_display24;
#endif
	
#if (menu_num >= 26)
	strcpy(Menu_Choose[25].name, name25);
	Menu_Choose[25].num = flash_data[25];
	Menu_Choose[25].multiple=multiple25;
	Menu_Choose[25].multiple_display=multiple_display25;
#endif
	
#if (menu_num >= 27)
	strcpy(Menu_Choose[26].name, name26);
	Menu_Choose[26].num = flash_data[26];
	Menu_Choose[26].multiple=multiple26;
	Menu_Choose[26].multiple_display=multiple_display26;
#endif
	
#if (menu_num >= 28)
	strcpy(Menu_Choose[27].name, name27);
	Menu_Choose[27].num = flash_data[27];
	Menu_Choose[27].multiple=multiple27;
	Menu_Choose[27].multiple_display=multiple_display27;
#endif

#if (menu_num >= 29)
	strcpy(Menu_Choose[28].name, name28);
	Menu_Choose[28].num = flash_data[28];
	Menu_Choose[28].multiple=multiple28;
	Menu_Choose[28].multiple_display=multiple_display28;
#endif
	
#if (menu_num >= 30)
	strcpy(Menu_Choose[29].name, name29);
	Menu_Choose[29].num = flash_data[29];
	Menu_Choose[29].multiple=multiple29;
	Menu_Choose[29].multiple_display=multiple_display29;
#endif
	
#if (menu_num >= 31)
	strcpy(Menu_Choose[30].name, name30);
	Menu_Choose[30].num = flash_data[30];
	Menu_Choose[30].multiple=multiple30;
	Menu_Choose[30].multiple_display=multiple_display30;
#endif
	
#if (menu_num >= 32)
	strcpy(Menu_Choose[31].name, name31);
	Menu_Choose[31].num = flash_data[31];
	Menu_Choose[31].multiple=multiple31;
	Menu_Choose[31].multiple_display=multiple_display31;
#endif

#if (menu_num >= 33)
	strcpy(Menu_Choose[32].name, name32);
	Menu_Choose[32].num = flash_data[32];
	Menu_Choose[32].multiple=multiple32;
	Menu_Choose[32].multiple_display=multiple_display32;
#endif
	
#if (menu_num >= 34)
	strcpy(Menu_Choose[33].name, name33);
	Menu_Choose[33].num = flash_data[33];
	Menu_Choose[33].multiple=multiple33;
	Menu_Choose[33].multiple_display=multiple_display33;
#endif
	
#if (menu_num >= 35)
	strcpy(Menu_Choose[34].name, name34);
	Menu_Choose[34].num = flash_data[34];
	Menu_Choose[34].multiple=multiple34;
	Menu_Choose[34].multiple_display=multiple_display34;
#endif
	
#if (menu_num >= 36)
	strcpy(Menu_Choose[35].name, name35);
	Menu_Choose[35].num = flash_data[35];
	Menu_Choose[35].multiple=multiple35;
	Menu_Choose[35].multiple_display=multiple_display35;
#endif

#if (menu_num >= 37)
	strcpy(Menu_Choose[36].name, name36);
	Menu_Choose[36].num = flash_data[36];
	Menu_Choose[36].multiple=multiple36;
	Menu_Choose[36].multiple_display=multiple_display36;
#endif
	
#if (menu_num >= 38)
	strcpy(Menu_Choose[37].name, name37);
	Menu_Choose[37].num = flash_data[37];
	Menu_Choose[37].multiple=multiple37;
	Menu_Choose[37].multiple_display=multiple_display37;
#endif
	
#if (menu_num >= 39)
	strcpy(Menu_Choose[38].name, name38);
	Menu_Choose[38].num = flash_data[38];
	Menu_Choose[38].multiple=multiple38;
	Menu_Choose[38].multiple_display=multiple_display38;
#endif
	
#if (menu_num >= 40)
	strcpy(Menu_Choose[39].name, name39);
	Menu_Choose[39].num = flash_data[39];
	Menu_Choose[39].multiple=multiple39;
	Menu_Choose[39].multiple_display=multiple_display39;
#endif

	
}

void menu_key()
{
	if(KEY4==0)                     //下移
	 {
		 systick_delay_ms(10);
		 if(KEY4==0) 
		 { 
			 while(KEY4==0);
			 menu_count+=1;
			 if(menu_count>menu_num-1)
				 menu_count=0;
			 if(line>=3 || menu_count == 0)
				 OLED_Clear();
			 else
				OLED_Clear_Part(2*line,0,2,8);
		 }
	 }
	 if(KEY6==0)                     //上移
	 {
		 systick_delay_ms(10);
		 if(KEY6==0) 
		 { 
			 while(KEY6==0); 
			 menu_count-=1;
			 if(menu_count<0)
				 menu_count=menu_num-1;
			 if(line<=0 || menu_count==menu_num-1)
				 OLED_Clear();
			 else
				 OLED_Clear_Part(2*line,0,2,8);
		 }
	 }
	 
	 if(KEY5==0)                     //增加
	 {
		 systick_delay_ms(10);
		 if(KEY5==0) 
		 { 
			 Menu_Choose[menu_count].num+=1;
		 }
	 }
	 
	 if(KEY3==0)                     //减少
	 {
		 systick_delay_ms(60);
		 if(KEY3==0) 
		 { 	
			 Menu_Choose[menu_count].num-=1;
		 }
	 }
	 
	 if(KEY2==0)                     //确定
	 {
		 systick_delay_ms(10);
		 if(KEY2==0) 
		 {
			 while(KEY2==0){;}
			 #if (menu_num >= 1)
				 flash_data[0] = Menu_Choose[0].num;
				 variable0=Menu_Choose[0].num*Menu_Choose[0].multiple;
			 #endif
			 
			 #if (menu_num >= 2)
				 flash_data[1] = Menu_Choose[1].num;
				 variable1=Menu_Choose[1].num*Menu_Choose[1].multiple;
			 #endif
			 
			 #if (menu_num >= 3)
				 flash_data[2] = Menu_Choose[2].num;
				 variable2=Menu_Choose[2].num*Menu_Choose[2].multiple;
			 #endif

			 #if (menu_num >= 4)
				 flash_data[3] = Menu_Choose[3].num;
				 variable3=Menu_Choose[3].num*Menu_Choose[3].multiple;
			 #endif
			 
			 #if (menu_num >= 5)
				 flash_data[4] = Menu_Choose[4].num;
				 variable4=Menu_Choose[4].num*Menu_Choose[4].multiple;
			 #endif
			 
			 #if (menu_num >= 6)
				 flash_data[5] = Menu_Choose[5].num;
				 variable5=Menu_Choose[5].num*Menu_Choose[5].multiple;
			 #endif
			 
			 #if (menu_num >= 7)
				 flash_data[6] = Menu_Choose[6].num;
				 variable6=Menu_Choose[6].num*Menu_Choose[6].multiple;
			 #endif
			 
			 #if (menu_num >= 8)
				 flash_data[7] = Menu_Choose[7].num;
				 variable7=Menu_Choose[7].num*Menu_Choose[7].multiple;
			 #endif
		
			 #if (menu_num >= 9)
				 flash_data[8] = Menu_Choose[8].num;
				 variable8=Menu_Choose[8].num*Menu_Choose[8].multiple;
			 #endif		

			 #if (menu_num >= 10)
				 flash_data[9] = Menu_Choose[9].num;
				 variable9=Menu_Choose[9].num*Menu_Choose[9].multiple;
			 #endif		

			 #if (menu_num >= 11)
				 flash_data[10] = Menu_Choose[10].num;
				 variable10=Menu_Choose[10].num*Menu_Choose[10].multiple;
			 #endif

			 #if (menu_num >= 12)
				 flash_data[11] = Menu_Choose[11].num;
				 variable11=Menu_Choose[11].num*Menu_Choose[11].multiple;
			 #endif
			 
			 #if (menu_num >= 13)
				 flash_data[12] = Menu_Choose[12].num;
				 variable12=Menu_Choose[12].num*Menu_Choose[12].multiple;
			 #endif
			 
			 #if (menu_num >= 14)
				 flash_data[13] = Menu_Choose[13].num;
				 variable13=Menu_Choose[13].num*Menu_Choose[13].multiple;
			 #endif
			 
			 #if (menu_num >= 15)
				 flash_data[14] = Menu_Choose[14].num;
				 variable14=Menu_Choose[14].num*Menu_Choose[14].multiple;
			 #endif
			 
			 #if (menu_num >= 16)
				 flash_data[15] = Menu_Choose[15].num;
				 variable15=Menu_Choose[15].num*Menu_Choose[15].multiple;
			 #endif
			 
			 #if (menu_num >= 17)
				 flash_data[16] = Menu_Choose[16].num;
				 variable16=Menu_Choose[16].num*Menu_Choose[16].multiple;
			 #endif				 
			 
			 #if (menu_num >= 18)
				 flash_data[17] = Menu_Choose[17].num;
				 variable17=Menu_Choose[17].num*Menu_Choose[17].multiple;
			 #endif
			 
			 #if (menu_num >= 19)
				 flash_data[18] = Menu_Choose[18].num;
				 variable18=Menu_Choose[18].num*Menu_Choose[18].multiple;
			 #endif		

			 #if (menu_num >= 20)
				 flash_data[19] = Menu_Choose[19].num;
				 variable19=Menu_Choose[19].num*Menu_Choose[19].multiple;
			 #endif
			 
			 #if (menu_num >= 21)
				 flash_data[20] = Menu_Choose[20].num;
				 variable20=Menu_Choose[20].num*Menu_Choose[20].multiple;
			 #endif
			 
			 #if (menu_num >= 22)
				 flash_data[21] = Menu_Choose[21].num;
				 variable21=Menu_Choose[21].num*Menu_Choose[21].multiple;
			 #endif
			 
			 #if (menu_num >= 23)
				 flash_data[22] = Menu_Choose[22].num;
				 variable22=Menu_Choose[22].num*Menu_Choose[22].multiple;
			 #endif
			 
			 #if (menu_num >= 24)
				 flash_data[23] = Menu_Choose[23].num;
				 variable23=Menu_Choose[23].num*Menu_Choose[23].multiple;
			 #endif
			 
			 #if (menu_num >= 25)
				 flash_data[24] = Menu_Choose[24].num;
				 variable24=Menu_Choose[24].num*Menu_Choose[24].multiple;
			 #endif
			 
			 #if (menu_num >= 26)
				 flash_data[25] = Menu_Choose[25].num;
				 variable25=Menu_Choose[25].num*Menu_Choose[25].multiple;
			 #endif
			 
			 #if (menu_num >= 27)
				 flash_data[26] = Menu_Choose[26].num;
				 variable26=Menu_Choose[26].num*Menu_Choose[26].multiple;
			 #endif
			 
			 #if (menu_num >= 28)
				 flash_data[27] = Menu_Choose[27].num;
				 variable27=Menu_Choose[27].num*Menu_Choose[27].multiple;
			 #endif
			 
			 #if (menu_num >= 29)
				 flash_data[28] = Menu_Choose[28].num;
				 variable28=Menu_Choose[28].num*Menu_Choose[28].multiple;
			 #endif
			 
			 #if (menu_num >= 30)
				 flash_data[29] = Menu_Choose[29].num;
				 variable29=Menu_Choose[29].num*Menu_Choose[29].multiple;
			 #endif
			 
			 #if (menu_num >= 31)
				 flash_data[30] = Menu_Choose[30].num;
				 variable30=Menu_Choose[30].num*Menu_Choose[30].multiple;
			 #endif
			 
			 #if (menu_num >= 32)
				 flash_data[31] = Menu_Choose[31].num;
				 variable31=Menu_Choose[31].num*Menu_Choose[31].multiple;
			 #endif
			 
			  #if (menu_num >= 33)
				 flash_data[32] = Menu_Choose[32].num;
				 variable32=Menu_Choose[32].num*Menu_Choose[32].multiple;
			 #endif
			 
			 #if (menu_num >= 34)
				 flash_data[33] = Menu_Choose[33].num;
				 variable33=Menu_Choose[33].num*Menu_Choose[33].multiple;
			 #endif
			 
			 #if (menu_num >= 35)
				 flash_data[34] = Menu_Choose[34].num;
				 variable34=Menu_Choose[34].num*Menu_Choose[34].multiple;
			 #endif

			 #if (menu_num >= 36)
				 flash_data[35] = Menu_Choose[35].num;
				 variable35=Menu_Choose[35].num*Menu_Choose[35].multiple;
			 #endif
			 
			 #if (menu_num >= 37)
				 flash_data[36] = Menu_Choose[36].num;
				 variable36=Menu_Choose[36].num*Menu_Choose[36].multiple;
			 #endif
			 
			 #if (menu_num >= 38)
				 flash_data[37] = Menu_Choose[37].num;
				 variable37=Menu_Choose[37].num*Menu_Choose[37].multiple;
			 #endif
			 
			 #if (menu_num >= 39)
				 flash_data[38] = Menu_Choose[38].num;
				 variable38=Menu_Choose[38].num*Menu_Choose[38].multiple;
			 #endif

			 #if (menu_num >= 40)
				 flash_data[39] = Menu_Choose[39].num;
				 variable39=Menu_Choose[39].num*Menu_Choose[39].multiple;
			 #endif
			 
			 FLASH_EraseSector(sector_num);
			 FLASH_WriteSector(sector_num,(const uint8 *)flash_data,2*menu_num,0);             //写入四个字节到最后一个扇区 偏移0字节
			 start_symbol=1;
		 }
	 }
}



void menu_display()
{
	   page=menu_count/4;
		 line=menu_count%4;
		 switch(line)
		 {
			 case 0:	OLED_Write_Char(0,0,'>');break;
			 case 1:	OLED_Write_Char(0,2,'>');break;
			 case 2:	OLED_Write_Char(0,4,'>');break;
			 case 3:	OLED_Write_Char(0,6,'>');break;			 
		 }

		 switch(menu_num-4*page-1)
		 {
			 case 0: 		 OLED_Write_String(2,0,(uint8_t *)Menu_Choose[page*4].name);
									 OLED_Write_Num4(12,0,Menu_Choose[page*4].num*Menu_Choose[page*4].multiple_display);
									 break;
			 case 1:     OLED_Write_String(2,0,(uint8_t *)Menu_Choose[page*4].name);
									 OLED_Write_Num4(12,0,Menu_Choose[page*4].num*Menu_Choose[page*4].multiple_display);
									 OLED_Write_String(2,2,(uint8_t *)Menu_Choose[page*4+1].name);
									 OLED_Write_Num4(12,2,Menu_Choose[page*4+1].num*Menu_Choose[page*4+1].multiple_display);
									 break;
			 case 2:     OLED_Write_String(2,0,(uint8_t *)Menu_Choose[page*4].name);
									 OLED_Write_Num4(12,0,Menu_Choose[page*4].num*Menu_Choose[page*4].multiple_display);
									 OLED_Write_String(2,2,(uint8_t *)Menu_Choose[page*4+1].name);
									 OLED_Write_Num4(12,2,Menu_Choose[page*4+1].num*Menu_Choose[page*4+1].multiple_display);
									 OLED_Write_String(2,4,(uint8_t *)Menu_Choose[page*4+2].name);
									 OLED_Write_Num4(12,4,Menu_Choose[page*4+2].num*Menu_Choose[page*4+2].multiple_display);
									 break;
			 default:		 OLED_Write_String(2,0,(uint8_t *)Menu_Choose[page*4].name);
									 OLED_Write_Num4(12,0,Menu_Choose[page*4].num*Menu_Choose[page*4].multiple_display);
									 OLED_Write_String(2,2,(uint8_t *)Menu_Choose[page*4+1].name);
									 OLED_Write_Num4(12,2,Menu_Choose[page*4+1].num*Menu_Choose[page*4+1].multiple_display);
									 OLED_Write_String(2,4,(uint8_t *)Menu_Choose[page*4+2].name);
									 OLED_Write_Num4(12,4,Menu_Choose[page*4+2].num*Menu_Choose[page*4+2].multiple_display);
									 OLED_Write_String(2,6,(uint8_t *)Menu_Choose[page*4+3].name);
									 OLED_Write_Num4(12,6,Menu_Choose[page*4+3].num*Menu_Choose[page*4+3].multiple_display);
		 }
}

