
#include "fxstartup.h"

//#pragma section CODE=FCODE,OFFSET $15:0000
//extern char _END_UDATA;
//void *heap_start=(void*)&_END_UDATA,*heap_end=(void*)(&_END_UDATA + 0x1000);

#define INT_PENDING_REG0  ((char far*)0x000140) 
#define INT_PENDING_REG1  ((char far*)0x000141) 
#define INT_PENDING_REG2  ((char far*)0x000142) 
#define INT_POL_REG0      ((char far*)0x000144) 
#define INT_POL_REG1      ((char far*)0x000145) 
#define INT_POL_REG2      ((char far*)0x000146) 
#define INT_EDGE_REG0     ((char far*)0x000148) 
#define INT_EDGE_REG1     ((char far*)0x000149) 
#define INT_EDGE_REG2     ((char far*)0x00014A) 
#define INT_MASK_REG0     ((char far*)0x00014C) 
#define INT_MASK_REG1     ((char far*)0x00014D) 
#define INT_MASK_REG2     ((char far*)0x00014E) 

#define FNX0_INT00_ALLONE 0x01
#define FNX0_INT01_SOF    0x02
#define FNX0_INT02_SOL    0x04
#define FNX0_INT03_TMR0   0x08
#define FNX0_INT04_TMR1   0x10
#define FNX0_INT05_TMR2   0x20
#define FNX0_INT06_RTC    0x40
#define FNX0_INT07_MOUSE  0x80

#define FNX1_INT00_KBD    0x01
#define FNX1_INT01_SC0    0x02
#define FNX1_INT02_SC1    0x04
#define FNX1_INT03_COM2   0x08
#define FNX1_INT04_COM1   0x10
#define FNX1_INT05_MPU401 0x20
#define FNX1_INT06_LPT    0x40
#define FNX1_INT07_SDCARD 0x80

#define FNX2_INT00_OPL2R  0x01
#define FNX2_INT01_OPL2L  0x02
#define FNX2_INT02_BTX_INT 0x04
#define FNX2_INT03_SDMA   0x08
#define FNX2_INT04_VDMA   0x10
#define FNX2_INT05_DACHP  0x20
#define FNX2_INT06_EXT    0x40
#define FNX2_INT07_ALLONE 0x80

#define UART_TRHB 	( 0x00)
//             ; Transmit/Receive Hold Buffer
#define UART_DLL 	( 0x00)
//        ; Divisor Latch Low Byte
#define UART_DLH 	( 0x01)
//              ; Divisor Latch High Byte
#define UART_IER 	(0x01)
//         ; Interupt Enable Register
#define UART_FCR 	(0x02)
//              ; FIFO Control Register
#define UART_IIR 	(0x02)
//         ; Interupt Indentification Register
#define UART_LCR 	(0x03)
//              ; Line Control Register
#define UART_MCR 	(0x04)
//              ; Modem Control REgister
#define UART_LSR 	(0x05)
//              ; Line Status Register
#define UART_MSR 	(0x06)
//              ; Modem Status Register
#define UART_SR 	(0x07)
//               ; Scratch Register


char cc = 0;

static char scirq0 = 0;
static char scirq00 = 0;
static char scirq01 = 0;
static char scirq02 = 0;
static char scirq03 = 0;
static char scirq04 = 0;
static char scirq05 = 0;
static char scirq06 = 0;
static char scirq07 = 0;

static char scirq1 = 0;
static char scirq10 = 0;
static char scirq11 = 0;
static char scirq12 = 0;
static char scirq13 = 0;
static char scirq14 = 0;
static char scirq15 = 0;
static char scirq16 = 0;
static char scirq17 = 0;

static char scirq2 = 0;
static char scirq20 = 0;
static char scirq21 = 0;
static char scirq22 = 0;
static char scirq23 = 0;
static char scirq24 = 0;
static char scirq25 = 0;
static char scirq26 = 0;
static char scirq27 = 0;

static char scts = 0;
static char sct1 = 0;
static char sct2 = 0;
static char taskindex = 0;

static char scsof = 0;

static char sc = 0;
static char sct = 0;
static char scto = 0;

static char sccop = 0;
static char scbrk = 0;
static long eirq = 1L;  
static char irqspinner[] = {'|','/','-','\\'};
static char qbuffer[32];

static int irqPos      		= 10;
static int irqSpinPos  		= 0;
static int irqMousePos 		= 0;
static int irqKeyPos   		= 0;
static int irqSpinnerPos 	= 20;
static int irqCOPPos     	= 0;

static char keyboardBuffer[21] = {'0'};
static char keyboardBufferIndex = 0;

unsigned char currentKeyPress = 0;
unsigned char isIRQOn = 1;
long 		  irqCount = 0;

unsigned char serialChar = 65;

long ctick = 0;
long ktick = 0;

int timeout = 0; 

int taskSwitchCount = 0;

static TASK_STACK stacks[2] = {{0x00,0x40,0x00,0x40,NULL},{0x00,0x41,0x00,0x41,NULL}};
static task_type mtasks[2] = {NULL,NULL};

static char itoaBuffer[16];

static unsigned char statusReg = 0x00;

#define CHK_KEYMOUSE_CTL  (0x02)


void disable(void)
{
	asm sei;
	k_set_border_color(255,0,0);	
}

void enable(void)
{
	asm cli;
	k_set_border_color(0,255,0);	
}



void k_init_multitasking(void)
{
	
}

void k_task_switch(void)
{
	k_put_char(9,8,irqspinner[scts++],15,0);	
	if(scts>3) scts = 0;
	
	taskindex=!taskindex;	
}

void t_make_task(task_type task,unsigned int ssize,int id)
{
	disable();
	
	mtasks[id] = task;
	
	enable();
}

void t0(void)
{
	k_put_char(11,8,irqspinner[sct1++],15,0);	
	if(sct1>3) sct1 = 0;	
}

void t1(void)
{
	k_put_char(13,8,irqspinner[sct2++],15,0);	
	if(sct2>3) sct2 = 0;	
}

void main(void)
{	
	keyboardBuffer[20] = 0;


	t_make_task(t0,100,0);
	t_make_task(t1,100,1);
	

	k_clear_screen(0);
	k_query_environment();
	k_run_loop();
}

void k_run_loop(void)
{
	char * ptest = "TEST UART";
	
	asm cli;

	k_init_keyboard();
	k_uart_enableirq_ports();

	k_print_uart_status_com1(30);
	k_print_uart_status_com2(31);

	#asm
        REP   #$20         ;16 bit registers and Clear Decimal mode
        LONGI ON
		LDA #$00
		LDX %%ptest
	#endasm
	//k_uart_putstring();

	statusReg&=CHK_KEYMOUSE_CTL;

	while(TRUE)
	{
		//asm sei;
		k_put_char(9,irqSpinPos,irqspinner[sc++],15,0);	
		if(sc>3) sc = 0;

		if(mtasks[taskindex])
		{
			//disable();
			asm sei;
			mtasks[taskindex]();
			//enable();
			asm cli;
		}
		if(currentKeyPress == 0x1F)
		{
			currentKeyPress = 0;
			
			k_set_border_color(0,0,128);
			
			while(!(UART2_BASE[5] & 0x20))
			{
					// waiting;
			}
			
			//UART1_BASE[0] = serialChar;
			//k_print_uart_status_com1(30);
			UART2_BASE[0] = serialChar++;
			//k_print_uart_status_com2(31);
			
			
			//UART1_BASE[0] = 'A';
			//asm LDA #'A'			
			//k_uart_putbyte();
			
			k_set_border_color(0,0,255);
		}
		if(currentKeyPress == 0x2E)
		{
			cc+=10;
			k_set_border_color(cc,cc,cc);
		}
		else if(currentKeyPress == 0x0C)
		{
			asm sei;
			k_set_border_color(255,0,0);
			isIRQOn = 0;
		}
		
		if(isIRQOn == 0)
		{
			irqCount++;
			if(irqCount > 65535)
			{
				irqCount = 0;
				isIRQOn = 1;
				asm cli;
				k_set_border_color(0,255,0);
			}
		}
		timeout++;
		if(timeout == 0)
		{
			if(!statusReg & CHK_KEYMOUSE_CTL)
			{
				k_put_char(9,0,irqspinner[scto++],15,0);	
				if(scto>3) scto = 0;
				k_init_keyboard();
				timeout = 0;
				
				statusReg &= ~CHK_KEYMOUSE_CTL;
			}
		}
		/*
		eirq++;			
		if(eirq > 0xFF)
		{
			asm COP;
			eirq = 0;
		}	
		*/
	}
}

int k_system_call(char far* data)
{
	asm COP;
	
	return 0;
}

void k_query_environment(void)
{
	int pos = 0;
	int line = 1;

	k_put_string(pos,line,"IRQ REGISTER DISPLAY TOOL",15,0);


	pos = 0;
	line = 5;

	
	pos = k_put_string(pos,line,"C256 Version:",15,0);
	k_get_c256_major_version(qbuffer);
	pos = k_put_string(pos,line,qbuffer,15,0);
	k_get_c256_minor_version(qbuffer);
	pos = k_put_string(pos,line,qbuffer,15,0);

	pos  = 0;
	line = 6;

	pos = k_put_string(pos,line,"FPGA Version:",15,0);
	k_get_fpga_date_month(qbuffer);
	pos = k_put_string(pos,line,qbuffer,15,0);
	pos = k_put_string(pos,line,"/",15,0);
	k_get_fpga_date_day(qbuffer);
	pos = k_put_string(pos,line,qbuffer,15,0);
	pos = k_put_string(pos,line,"/",15,0);;
	k_get_fpga_date_year(qbuffer);
	pos = k_put_string(pos,line,qbuffer,15,0);

	pos  = 0;
	line = 8;
	pos = k_put_string(pos,line,"TASKTICK:",15,0);
	
	
	pos  = 0;
	line = irqPos;
	line++;
	
	irqMousePos = line;	
	pos = k_put_string(0,line++,"MOUSE   :",15,0);
	
	irqKeyPos = line;	
	pos = k_put_string(0,line++,"KEYCODE :",15,0);
	line++;
	
	irqSpinPos = line;
	
	pos = k_put_string(0,line++,"CPU     :",15,0);
	pos = k_put_string(0,line++,"BRK     :",15,0);
	
	irqCOPPos = line;
	
	pos = k_put_string(0,line++,"COP     :",15,0);	
	line++;
	//pos = //k_put_string(17,47," > ODD SOF COUNT TRIGGER COP",15,0);	
	
	pos = k_put_string(0,irqSpinnerPos-1,"IRQ     :*01234567",15,0);
	
	//irqSpinnerPos = line;
	line = irqSpinnerPos;
	
	pos = k_put_string(0,line++,"REG0    :",15,0);
	pos = k_put_string(0,line++,"REG1    :",15,0);
	pos = k_put_string(0,line++,"REG2    :",15,0);
	
	
}

void k_tickManagement(void)
{
	currentKeyPress = 0;
	
	if(ktick > 0)
		ktick--;
	
	if(taskSwitchCount > 2)	
	{
		k_task_switch();
		taskSwitchCount = 0;
	}
	taskSwitchCount++;
	
	//k_print_uart_status_com1(30);
	//k_print_uart_status_com2(31);
}

void k_print_uart_status_com1(int lc)
{
	int lcp = 0;	
/*		
#define UART_TRHB 	( 0x00)
//             ; Transmit/Receive Hold Buffer
#define UART_DLL 	( 0x00)
//        ; Divisor Latch Low Byte
#define UART_DLH 	( 0x01)
//              ; Divisor Latch High Byte
#define UART_IER 	(0x01)
//         ; Interupt Enable Register
#define UART_FCR 	(0x02)
//              ; FIFO Control Register
#define UART_IIR 	(0x02)
//         ; Interupt Indentification Register
#define UART_LCR 	(0x03)
//              ; Line Control Register
#define UART_MCR 	(0x04)
//              ; Modem Control REgister
#define UART_LSR 	(0x05)
//              ; Line Status Register
#define UART_MSR 	(0x06)
//              ; Modem Status Register
#define UART_SR 	(0x07)
//               ; Scratch Register
*/
	lcp = 0;

	//k_put_string(lcp,lc,"                 ",15,0);
	//lcp = k_put_string(lcp,lc,k_itoa(UART1_BASE[UART_TRHB],itoaBuffer,16),15,0);
	lcp = k_put_string(lcp,lc,"XX",15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART1_BASE[UART_DLH] ,itoaBuffer,16),15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART1_BASE[UART_FCR] ,itoaBuffer,16),15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART1_BASE[UART_LCR] ,itoaBuffer,16),15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART1_BASE[UART_MCR] ,itoaBuffer,16),15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART1_BASE[UART_LSR] ,itoaBuffer,16),15,0);	
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART1_BASE[UART_MSR] ,itoaBuffer,16),15,0);
	//k_put_char(lcp,lc,'-',15,0);lcp++;
	//lcp = k_put_string(lcp,lc,k_itoa(UART1_BASE[UART_MSR] ,itoaBuffer,16),15,0);
	

}

void k_print_uart_status_com2(int lc)
{
	int lcp = 0;	

	//k_put_string(lcp,lc,"                 ",15,0);
	//lcp = k_put_string(lcp,lc,k_itoa(UART2_BASE[UART_TRHB],itoaBuffer,16),15,0);
	lcp = k_put_string(lcp,lc,"XX",15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART2_BASE[UART_DLH] ,itoaBuffer,16),15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART2_BASE[UART_FCR] ,itoaBuffer,16),15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART2_BASE[UART_LCR] ,itoaBuffer,16),15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART2_BASE[UART_MCR] ,itoaBuffer,16),15,0);
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART2_BASE[UART_LSR] ,itoaBuffer,16),15,0);	
	k_put_char(lcp,lc,'-',15,0);lcp++;
	lcp = k_put_string(lcp,lc,k_itoa(UART2_BASE[UART_MSR] ,itoaBuffer,16),15,0);
	//k_put_char(lcp,lc,'-',15,0);lcp++;
	//lcp = k_put_string(lcp,lc,k_itoa(UART2_BASE[UART_MSR] ,itoaBuffer,16),15,0);
}


void k_get_fpga_date_day(char *buffer)
{
	k_itoa(FPGA_DOR[0],buffer,10);
}

void k_get_fpga_date_month(char *buffer)
{
	k_itoa(FPGA_MOR[0],buffer,10);
}

void k_get_fpga_date_year(char *buffer)
{
	k_itoa(*FPGA_YOR,buffer,10);
}

void k_get_c256_major_version(char *buffer)
{
	buffer[0] = *C256F_MODEL_MAJOR;
	buffer[1] = 0;
}

void k_get_c256_minor_version(char *buffer)
{
	buffer[0] = *C256F_MODEL_MINOR;
	buffer[1] = 0;
}

char * k_itoa(unsigned int value, char *result, int base)
{
    char * ptr  = result;
	char * ptr1 = result;
	char tmp_char;
    int tmp_value;

	char *CHAR_LIST = "ZYXWVUTSRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // check that the base if valid
    if (base < 2 || base > 36)
	{	
		*result = '\0'; 
		return result; 
	}


    do 
	{
        tmp_value = value;
        value /= base;
        *ptr++ = CHAR_LIST [35 + (tmp_value - value * base)];
    }
	while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) 
	{
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}


int k_get_cols_visible(void)
{
	return *((int*)(&((COLS_VISIBLE)[0]))); //2 Bytes Columns visible per screen line. A virtual line can be longer than displayed, up to COLS_PER_LINE long. Default  80
}

int k_get_cols_per_line(void)
{
	return *((int*)COLS_PER_LINE); //2 Bytes Columns visible per screen line. A virtual line can be longer than displayed, up to COLS_PER_LINE long. Default  80
}

int k_get_lines_visible(void)
{
	return *((int*)LINES_VISIBLE); //2 Bytes Columns visible per screen line. A virtual line can be longer than displayed, up to COLS_PER_LINE long. Default  80
}

int k_get_lines_max(void)
{
	return *((int*)LINES_MAX); //2 Bytes Columns visible per screen line. A virtual line can be longer than displayed, up to COLS_PER_LINE long. Default  80
}

void k_enable_text_mode(void)
{
	MASTER_CTRL_REG_L[0] = MSTR_CTRL_TEXT_MODE_EN;
}

void k_enable_border(void)
{
	BORDER_CTRL_REG[0] = BORDER_CTRL_ENABLE;
}

void k_disable_border(void)
{
	BORDER_CTRL_REG[0] = 0x00 ;
}

void k_set_border_color(char r,char g,char b)
{
	BORDER_COLOR_B[0] = b;
	BORDER_COLOR_G[0] = g;
	BORDER_COLOR_R[0] = r;
}

void k_clear_screen(int bcolor)
{
	memset((unsigned char far *)0xAFA000,0,0xAFA000 + 0xC000);
	memset((unsigned char far *)0xAFC000,bcolor,0xAFA000 + 0xC000);
}

int k_put_string(int col,int row,char * text,int fcolor,int bcolor)
{
	char * ptr = text;
	while(*ptr)
	{
		k_put_char(col,row,*ptr,fcolor,bcolor);
		col++;
		ptr++;
	}
	
	return col;
}

void k_put_char(int col,int row,char c,int fcolor,int bcolor)
{
	CS_TEXT_MEM_PTR[128 * row + col] = c;
	CS_COLOR_MEM_PTR[128 * row + col] = (fcolor & 0x0F) << 4 + (bcolor & 0x0F);
}



void k_set_background(int col,int row,int bcolor)
{
	((unsigned char far *)(0xAFC000 + (128 * row) + col))[0] =  bcolor;
}

//
// STRING LIB
//
char *strupr(char *s)
{
  char	*p;

  for (p = s; *p; ++p)
    *p = toupper(*p);

  return(s);

}	/* END STRUPR */

/* -------------------------------------------------------------------- */
char * strlower(char * s)
{
  char	*p;

  for (p = s; *p; ++p)
    *p = tolower(*p);

  return(s);

}	/* END STRLOWER */


void BRKHandler(void)
{
	k_put_char(9,irqCOPPos - 1,irqspinner[scbrk++],15,0);	
	if(scbrk>3) scbrk = 0;
	//asm sei;	
}

void COPHandler(void)
{
	k_put_char(9,irqCOPPos,irqspinner[sccop++],15,0);	
	if(sccop>3) sccop = 0;
	//asm sei;	
}

void k_dispatch_reg0(PIRQDATA pIRQ)
{
	int line = pIRQ->line;
	
	char far *keyCode = pIRQ->keycode;

	
	k_put_char(9,line,irqspinner[scirq0],15,0);	
	scirq0++;
	
	if(scirq0>3)
	{
		scirq0 = 0;
	}
	
	
	if(INT_PENDING_REG0[0] & FNX0_INT00_ALLONE)
	{
		k_put_char(10,line,irqspinner[scirq00++],15,0);	
		if(scirq00>3) scirq00 = 0;

		INT_PENDING_REG0[0] &=  FNX0_INT00_ALLONE;
	}
	
	if(INT_PENDING_REG0[0] & FNX0_INT01_SOF)
	{
		k_put_char(11,line,irqspinner[scirq01++],15,0);	
		if(scirq01>3) scirq01 = 0;
		
		k_tickManagement();
		
		INT_PENDING_REG0[0] &= FNX0_INT01_SOF;
	}
	if(INT_PENDING_REG0[0] & FNX0_INT02_SOL)
	{
		//k_put_char(3,0,'X',15,0);
		//k_put_char(3,0,'2',15,0);

		k_put_char(12,line,irqspinner[scirq02++],15,0);	
		if(scirq02>3) scirq02 = 0;

		INT_PENDING_REG0[0] &=  FNX0_INT02_SOL;
	}
	if(INT_PENDING_REG0[0] & FNX0_INT03_TMR0)
	{

		k_put_char(13,line,irqspinner[scirq03++],15,0);	
		if(scirq03>3) scirq03 = 0;

		INT_PENDING_REG0[0] &=  FNX0_INT03_TMR0;
	}
	if(INT_PENDING_REG0[0] & FNX0_INT04_TMR1)
	{
		k_put_char(14,line,irqspinner[scirq04++],15,0);	
		if(scirq04>3) scirq04 = 0;


		//k_put_char(5,0,'X',15,0);
		//k_put_char(5,0,'4',15,0);
		INT_PENDING_REG0[0] &=  FNX0_INT04_TMR1;
	}
	if(INT_PENDING_REG0[0] & FNX0_INT05_TMR2)
	{
		k_put_char(15,line,irqspinner[scirq05++],15,0);	
		if(scirq05>3) scirq05 = 0;


		//k_put_char(6,0,'X',15,0);
		//k_put_char(6,0,'5',15,0);
		INT_PENDING_REG0[0]&=FNX0_INT05_TMR2;
	}
	if(INT_PENDING_REG0[0] & FNX0_INT06_RTC)
	{
		k_put_char(16,line,irqspinner[scirq06++],15,0);	
		if(scirq06>3) scirq06 = 0;


		//k_put_char(7,0,'X',15,0);
		//k_put_char(7,0,'6',15,0);
		INT_PENDING_REG0[0]&=FNX0_INT06_RTC;
	}
	if(INT_PENDING_REG0[0] & FNX0_INT07_MOUSE)
	{
		k_put_char(17,line,irqspinner[scirq07++],15,0);	
		if(scirq07>3) scirq07 = 0;

		//k_put_char(11,41,KBD_INPT_BUF[0],15,0);
		
		k_itoa(KBD_INPT_BUF[0],keyCode,10);
		
		k_put_string(11,irqMousePos,"     ",15,0);
		k_put_string(11,irqMousePos,keyCode,15,0);
		
		
		INT_PENDING_REG0[0] &= FNX0_INT07_MOUSE;
	}
	//*INT_PENDING_REG0 = *INT_PENDING_REG0;
	INT_PENDING_REG0[0] = 0xFF;
	INT_PENDING_REG0[0] = 0x00;
	
}

void k_dispatch_reg1(PIRQDATA pIRQ)
{
	int line = pIRQ->line;
	
	char far *keyCode = pIRQ->keycode;
	char none = 0;
	char data = 0;
	//char null = 0;
	int dp = 20;
	
	line++;
	
	k_put_char(9,line,irqspinner[scirq1++],15,0);	
	if(scirq1>3)scirq1 = 0;
	
	if(irqKeyPos!=0)
	k_put_string(11,irqKeyPos,"    ",15,0);
	
	//k_put_char(0,1,'1',15,0);
	if(INT_PENDING_REG1[0] & FNX1_INT00_KBD)
	{

		k_put_char(10,line,irqspinner[scirq10++],15,0);	
		if(scirq10>3)scirq10 = 0;

		if(ktick == 0)
		{
			ktick = 2;

			//if(KBD_INPT_BUF[0]!=currentKeyPress)
			//	currentKeyPress = KBD_INPT_BUF[0];
			currentKeyPress = KBD_INPT_BUF[0];

			keyboardBuffer[keyboardBufferIndex++] = currentKeyPress;//KBD_INPT_BUF[0];
			if(keyboardBufferIndex > 19)
				keyboardBufferIndex = 0;

			//k_itoa(KBD_INPT_BUF[0],keyCode,16);
			k_itoa(currentKeyPress,keyCode,16);
			
			//k_put_char(11,42,KBD_INPT_BUF[0],15,0);
			//k_put_string(11,42,"    ",15,0);
			k_put_string(16,irqKeyPos,keyboardBuffer,15,0);
			k_put_string(11,irqKeyPos,keyCode,15,0);
		}				
		else
		{
			currentKeyPress = 0;
			none = KBD_INPT_BUF[0];
		}
	
		statusReg&=CHK_KEYMOUSE_CTL;
		
		INT_PENDING_REG1[0] &= FNX1_INT00_KBD;
	}
	
	if(INT_PENDING_REG1[0] & FNX1_INT01_SC0)
	{
		k_put_char(11,line,irqspinner[scirq11++],15,0);	
		if(scirq11>3)scirq11 = 0;

		//k_put_char(2,1,' ',15,0);
		//k_put_char(2,1,'1',15,0);
		INT_PENDING_REG1[0]&=FNX1_INT01_SC0;
	}
	if(INT_PENDING_REG1[0] & FNX1_INT02_SC1)
	{
		k_put_char(12,line,irqspinner[scirq12++],15,0);	
		if(scirq12>3)scirq12 = 0;
		
		//k_put_char(3,1,' ',15,0);
		//k_put_char(3,1,'2',15,0);
		INT_PENDING_REG1[0]&=FNX1_INT02_SC1;
	}
	if(INT_PENDING_REG1[0] & FNX1_INT03_COM2)
	{
		k_put_char(13,line,irqspinner[scirq13++],15,0);	
		if(scirq13>3)scirq13 = 0;
		
		k_print_uart_status_com2(31);
		data = UART2_BASE[0];
		k_put_char(dp++,31,data+64,15,0);
		while(UART2_BASE[UART_LSR] & 0x01)
		{
			data = UART2_BASE[0];
			k_put_char(dp++,31,data+64,15,0);
		}
		k_print_uart_status_com2(32);
		
		
		//k_put_char(20,31,data+64,15,0);
		//k_put_char(4,1,' ',15,0);
		//k_put_char(4,1,'3',15,0);
		INT_PENDING_REG1[0]&=FNX1_INT03_COM2;
	}
	if(INT_PENDING_REG1[0] & FNX1_INT04_COM1)
	{

		k_put_char(14,line,irqspinner[scirq14++],15,0);	
		if(scirq14>3)scirq14 = 0;

		k_print_uart_status_com1(30);
		k_put_char(20,301,UART1_BASE[0],15,0);
		//k_put_char(5,1,' ',15,0);
		//k_put_char(5,1,'4',15,0);
		INT_PENDING_REG1[0]&=FNX1_INT04_COM1;
	}
	if(INT_PENDING_REG1[0] & FNX1_INT05_MPU401)
	{
		k_put_char(15,line,irqspinner[scirq15++],15,0);	
		if(scirq15>3)scirq15 = 0;


		//k_put_char(6,1,' ',15,0);
		//k_put_char(6,1,'5',15,0);
		INT_PENDING_REG1[0]&=FNX1_INT05_MPU401;
	}
	if(INT_PENDING_REG1[0] & FNX1_INT06_LPT)
	{
		k_put_char(16,line,irqspinner[scirq16++],15,0);	
		if(scirq16>3)scirq16 = 0;

		//k_put_char(6,1,' ',15,0);
		//k_put_char(6,1,'6',15,0);
		INT_PENDING_REG1[0]&=FNX1_INT06_LPT;
	}
	if(INT_PENDING_REG1[0] & FNX1_INT07_SDCARD)
	{
		k_put_char(17,line,irqspinner[scirq17++],15,0);	
		if(scirq17>3)scirq17 = 0;


		//k_put_char(7,1,' ',15,0);
		//k_put_char(7,1,'7',15,0);
		INT_PENDING_REG1[0]&=FNX1_INT07_SDCARD;
	}
	//*INT_PENDING_REG1=*INT_PENDING_REG1;
	INT_PENDING_REG1[0]=0xFF;
	INT_PENDING_REG1[0]=0x00;
	
}

void k_dispatch_reg2(PIRQDATA pIRQ)
{
	int line = pIRQ->line;
	
	char far *keyCode = pIRQ->keycode;
	
	line++;
	
	k_put_char(9,line,irqspinner[scirq2++],15,0);	
	if(scirq2>3) scirq2 = 0;

	if(INT_PENDING_REG2[0] & FNX2_INT00_OPL2R)
	{
		k_put_char(10,line,irqspinner[scirq20++],15,0);	
		if(scirq20>3) scirq20 = 0;
		//k_put_char(2,2,' ',15,0);
		//k_put_char(2,2,'0',15,0);
		INT_PENDING_REG2[0]&=FNX2_INT00_OPL2R;
	}
	if(INT_PENDING_REG2[0] & FNX2_INT01_OPL2L)
	{
		k_put_char(11,line,irqspinner[scirq21++],15,0);	
		if(scirq21>3) scirq21 = 0;
		//k_put_char(3,2,' ',15,0);
		//k_put_char(3,2,'1',15,0);
		INT_PENDING_REG2[0]&=FNX2_INT01_OPL2L;
	}
	if(INT_PENDING_REG2[0] & FNX2_INT02_BTX_INT)
	{
		k_put_char(12,line,irqspinner[scirq22++],15,0);	
		if(scirq22>3) scirq22 = 0;
		//k_put_char(4,2,' ',15,0);
		//k_put_char(4,2,'2',15,0);
		INT_PENDING_REG2[0]&=FNX2_INT02_BTX_INT;
	}
	if(INT_PENDING_REG2[0] & FNX2_INT03_SDMA)
	{
		k_put_char(13,line,irqspinner[scirq23++],15,0);	
		if(scirq23>3) scirq23 = 0;
		//k_put_char(5,2,' ',15,0);
		//k_put_char(5,2,'3',15,0);
		INT_PENDING_REG2[0]&=FNX2_INT03_SDMA;
	}
	if(INT_PENDING_REG2[0] & FNX2_INT04_VDMA)
	{
		k_put_char(14,line,irqspinner[scirq24++],15,0);	
		if(scirq24>3) scirq24 = 0;
		//k_put_char(6,2,' ',15,0);
		//k_put_char(6,2,'4',15,0);
		INT_PENDING_REG2[0]&=FNX2_INT04_VDMA;
	}
	if(INT_PENDING_REG2[0] & FNX1_INT06_LPT)
	{
		k_put_char(16,line,irqspinner[scirq26++],15,0);	
		if(scirq26>3) scirq26 = 0;
		//k_put_char(7,2,' ',15,0);
		//k_put_char(7,2,'6',15,0);
		INT_PENDING_REG2[0]&=FNX1_INT06_LPT;
	}
	
	INT_PENDING_REG2[0]=0xFF;
	INT_PENDING_REG2[0]=0x00;
	
}

void IRQHandler(void)
{
	char keyCode[16] = {0,0,0,0,0,0,0,0,
							0,0,0,0,0,0,0,0};	
	IRQDATA data;
		
	data.keycode = keyCode;	
	data.line = irqSpinnerPos;
	
	if(INT_PENDING_REG0[0]!=0)
	{
		k_dispatch_reg0(&data);
	}
	
	if(INT_PENDING_REG1[0]!=0)
	{
		k_dispatch_reg1(&data);	
	}
	
	if(INT_PENDING_REG2[0]!=0)
	{
		k_dispatch_reg2(&data);
	}
	
	return;
}


void IRQHandler_old(void)
{
	int line = irqSpinnerPos;
	
	char keyCode[16] = {0,0,0,0,0,0,0,0,
	                    0,0,0,0,0,0,0,0};
	
	if(INT_PENDING_REG0[0]!=0)
	{
		k_put_char(9,line,irqspinner[scirq0],15,0);	
		scirq0++;
		
		if(scirq0>3)
		{
			scirq0 = 0;
		}
		
		
		if(INT_PENDING_REG0[0] & FNX0_INT00_ALLONE)
		{
			k_put_char(10,line,irqspinner[scirq00++],15,0);	
			if(scirq00>3) scirq00 = 0;

			INT_PENDING_REG0[0] &=  FNX0_INT00_ALLONE;
		}
		
		if(INT_PENDING_REG0[0] & FNX0_INT01_SOF)
		{
			k_put_char(11,line,irqspinner[scirq01++],15,0);	
			if(scirq01>3) scirq01 = 0;
			
			k_tickManagement();
			
			INT_PENDING_REG0[0] &= FNX0_INT01_SOF;
		}
		if(INT_PENDING_REG0[0] & FNX0_INT02_SOL)
		{
			//k_put_char(3,0,'X',15,0);
			//k_put_char(3,0,'2',15,0);

			k_put_char(12,line,irqspinner[scirq02++],15,0);	
			if(scirq02>3) scirq02 = 0;

			INT_PENDING_REG0[0] &=  FNX0_INT02_SOL;
		}
		if(INT_PENDING_REG0[0] & FNX0_INT03_TMR0)
		{

			k_put_char(13,line,irqspinner[scirq03++],15,0);	
			if(scirq03>3) scirq03 = 0;

			INT_PENDING_REG0[0] &=  FNX0_INT03_TMR0;
		}
		if(INT_PENDING_REG0[0] & FNX0_INT04_TMR1)
		{
			k_put_char(14,line,irqspinner[scirq04++],15,0);	
			if(scirq04>3) scirq04 = 0;


			//k_put_char(5,0,'X',15,0);
			//k_put_char(5,0,'4',15,0);
			INT_PENDING_REG0[0] &=  FNX0_INT04_TMR1;
		}
		if(INT_PENDING_REG0[0] & FNX0_INT05_TMR2)
		{
			k_put_char(15,line,irqspinner[scirq05++],15,0);	
			if(scirq05>3) scirq05 = 0;


			//k_put_char(6,0,'X',15,0);
			//k_put_char(6,0,'5',15,0);
			INT_PENDING_REG0[0]&=FNX0_INT05_TMR2;
		}
		if(INT_PENDING_REG0[0] & FNX0_INT06_RTC)
		{
			k_put_char(16,line,irqspinner[scirq06++],15,0);	
			if(scirq06>3) scirq06 = 0;


			//k_put_char(7,0,'X',15,0);
			//k_put_char(7,0,'6',15,0);
			INT_PENDING_REG0[0]&=FNX0_INT06_RTC;
		}
		if(INT_PENDING_REG0[0] & FNX0_INT07_MOUSE)
		{
			k_put_char(17,line,irqspinner[scirq07++],15,0);	
			if(scirq07>3) scirq07 = 0;

			//k_put_char(11,41,KBD_INPT_BUF[0],15,0);
			
			k_itoa(KBD_INPT_BUF[0],keyCode,10);
			
			k_put_string(11,irqMousePos,"     ",15,0);
			k_put_string(11,irqMousePos,keyCode,15,0);
			
			
			INT_PENDING_REG0[0] &= FNX0_INT07_MOUSE;
		}
		//*INT_PENDING_REG0 = *INT_PENDING_REG0;
		INT_PENDING_REG0[0] = 0xFF;
		INT_PENDING_REG0[0] = 0x00;
	}
	
	if(INT_PENDING_REG1[0]!=0)
	{
		line++;
		
		k_put_char(9,line,irqspinner[scirq1++],15,0);	
		if(scirq1>3)scirq1 = 0;
		
		if(irqKeyPos!=0)
		k_put_string(11,irqKeyPos,"    ",15,0);
		
		//k_put_char(0,1,'1',15,0);
		if(INT_PENDING_REG1[0] & FNX1_INT00_KBD)
		{
			k_put_char(10,line,irqspinner[scirq10++],15,0);	
			if(scirq10>3)scirq10 = 0;

			if(KBD_INPT_BUF[0]!=currentKeyPress)
				currentKeyPress = KBD_INPT_BUF[0];

			keyboardBuffer[keyboardBufferIndex++] = KBD_INPT_BUF[0];
			if(keyboardBufferIndex > 19)
				keyboardBufferIndex = 0;

			k_itoa(KBD_INPT_BUF[0],keyCode,16);
			
			//k_put_char(11,42,KBD_INPT_BUF[0],15,0);
			//k_put_string(11,42,"    ",15,0);
			k_put_string(16,irqKeyPos,keyboardBuffer,15,0);
			k_put_string(11,irqKeyPos,keyCode,15,0);
			
			INT_PENDING_REG1[0] &= FNX1_INT00_KBD;
		}
		
		if(INT_PENDING_REG1[0] & FNX1_INT01_SC0)
		{
			k_put_char(11,line,irqspinner[scirq11++],15,0);	
			if(scirq11>3)scirq11 = 0;

			//k_put_char(2,1,' ',15,0);
			//k_put_char(2,1,'1',15,0);
			INT_PENDING_REG1[0]&=FNX1_INT01_SC0;
		}
		if(INT_PENDING_REG1[0] & FNX1_INT02_SC1)
		{
			k_put_char(12,line,irqspinner[scirq12++],15,0);	
			if(scirq12>3)scirq12 = 0;
			
			//k_put_char(3,1,' ',15,0);
			//k_put_char(3,1,'2',15,0);
			INT_PENDING_REG1[0]&=FNX1_INT02_SC1;
		}
		if(INT_PENDING_REG1[0] & FNX1_INT03_COM2)
		{
			k_put_char(13,line,irqspinner[scirq13++],15,0);	
			if(scirq13>3)scirq13 = 0;
			
			k_print_uart_status_com2(31);
			//k_put_char(4,1,' ',15,0);
			//k_put_char(4,1,'3',15,0);
			INT_PENDING_REG1[0]&=FNX1_INT03_COM2;
		}
		if(INT_PENDING_REG1[0] & FNX1_INT04_COM1)
		{

			k_put_char(14,line,irqspinner[scirq14++],15,0);	
			if(scirq14>3)scirq14 = 0;

			k_print_uart_status_com1(30);
			//k_put_char(5,1,' ',15,0);
			//k_put_char(5,1,'4',15,0);
			INT_PENDING_REG1[0]&=FNX1_INT04_COM1;
		}
		if(INT_PENDING_REG1[0] & FNX1_INT05_MPU401)
		{
			k_put_char(15,line,irqspinner[scirq15++],15,0);	
			if(scirq15>3)scirq15 = 0;


			//k_put_char(6,1,' ',15,0);
			//k_put_char(6,1,'5',15,0);
			INT_PENDING_REG1[0]&=FNX1_INT05_MPU401;
		}
		if(INT_PENDING_REG1[0] & FNX1_INT06_LPT)
		{
			k_put_char(16,line,irqspinner[scirq16++],15,0);	
			if(scirq16>3)scirq16 = 0;

			//k_put_char(6,1,' ',15,0);
			//k_put_char(6,1,'6',15,0);
			INT_PENDING_REG1[0]&=FNX1_INT06_LPT;
		}
		if(INT_PENDING_REG1[0] & FNX1_INT07_SDCARD)
		{
			k_put_char(17,line,irqspinner[scirq17++],15,0);	
			if(scirq17>3)scirq17 = 0;


			//k_put_char(7,1,' ',15,0);
			//k_put_char(7,1,'7',15,0);
			INT_PENDING_REG1[0]&=FNX1_INT07_SDCARD;
		}
		//*INT_PENDING_REG1=*INT_PENDING_REG1;
		INT_PENDING_REG1[0]=0xFF;
		INT_PENDING_REG1[0]=0x00;
	}
	if(INT_PENDING_REG2[0]!=0)
	{
		line++;
		
		k_put_char(9,line,irqspinner[scirq2++],15,0);	
		if(scirq2>3) scirq2 = 0;

		if(INT_PENDING_REG2[0] & FNX2_INT00_OPL2R)
		{
			k_put_char(10,line,irqspinner[scirq20++],15,0);	
			if(scirq20>3) scirq20 = 0;
			//k_put_char(2,2,' ',15,0);
			//k_put_char(2,2,'0',15,0);
			INT_PENDING_REG2[0]&=FNX2_INT00_OPL2R;
		}
		if(INT_PENDING_REG2[0] & FNX2_INT01_OPL2L)
		{
			k_put_char(11,line,irqspinner[scirq21++],15,0);	
			if(scirq21>3) scirq21 = 0;
			//k_put_char(3,2,' ',15,0);
			//k_put_char(3,2,'1',15,0);
			INT_PENDING_REG2[0]&=FNX2_INT01_OPL2L;
		}
		if(INT_PENDING_REG2[0] & FNX2_INT02_BTX_INT)
		{
			k_put_char(12,line,irqspinner[scirq22++],15,0);	
			if(scirq22>3) scirq22 = 0;
			//k_put_char(4,2,' ',15,0);
			//k_put_char(4,2,'2',15,0);
			INT_PENDING_REG2[0]&=FNX2_INT02_BTX_INT;
		}
		if(INT_PENDING_REG2[0] & FNX2_INT03_SDMA)
		{
			k_put_char(13,line,irqspinner[scirq23++],15,0);	
			if(scirq23>3) scirq23 = 0;
			//k_put_char(5,2,' ',15,0);
			//k_put_char(5,2,'3',15,0);
			INT_PENDING_REG2[0]&=FNX2_INT03_SDMA;
		}
		if(INT_PENDING_REG2[0] & FNX2_INT04_VDMA)
		{
			k_put_char(14,line,irqspinner[scirq24++],15,0);	
			if(scirq24>3) scirq24 = 0;
			//k_put_char(6,2,' ',15,0);
			//k_put_char(6,2,'4',15,0);
			INT_PENDING_REG2[0]&=FNX2_INT04_VDMA;
		}
		if(INT_PENDING_REG2[0] & FNX1_INT06_LPT)
		{
			k_put_char(16,line,irqspinner[scirq26++],15,0);	
			if(scirq26>3) scirq26 = 0;
			//k_put_char(7,2,' ',15,0);
			//k_put_char(7,2,'6',15,0);
			INT_PENDING_REG2[0]&=FNX1_INT06_LPT;
		}
		
		INT_PENDING_REG2[0]=0xFF;
		INT_PENDING_REG2[0]=0x00;
	}
	
	return;
}



