#include<stm32f10x.h>

void SysClkConf(void);
void SendStart(void);
void Delay_us(uint32_t);
void Delay_ms(uint32_t);
void PinConf(void);

uint32_t get_us(uint32_t);
uint8_t ReadDHT(void);
double	*DHT11_Data(void);
double 	*DHT22_Data(void);
static uint8_t humidity_integer;
static uint8_t humidity_decimal;
static uint8_t temperature_integer;
static uint8_t temperature_decimal;
static double temp;
static double humid;
static uint8_t checksum;


int main(void){
	SysClkConf();
	PinConf();
	//wait 1s
	Delay_ms(1000);
	
	while(1){
		double *data = DHT22_Data();
    temp = data[0];
		humid = data[1];
		Delay_ms(1000);
	}
	
}

void SysClkConf(void) {
	//1.Turn on HSE to use.
	RCC->CR |= 1<<16; // HSE on
	while((RCC->CR & (1<<17)) == 0); // wait HSERDY.

	//2. config PLL (HSE, MUL9).
	RCC->CFGR |= 0x07<<18; // PLLMUL9 -> systemclock = 72MHz
	RCC->CFGR |= 1<<15; // ADC prescale 6.
	RCC->CFGR |= 1<<10; //APB1 prescale 2.

	//3. choose new clock source.
	RCC->CFGR |= (1<<16); // PLLSRC HSE

	//4. enable PLL
	RCC->CR |= 1<<24;
	while((RCC->CR & 1<<25) == 0); // wait PLLRDY.

	//5. switch sysclk to PLL
	RCC->CFGR |= 0x02;
	while((RCC->CFGR & (1<<3)) == 0); //wait SWS.

	//6.turn off original source
	RCC->CR &= ~(0x01); // off HSION
	while((RCC->CR & 0x02)==0x02);
	//7. supply clock
	RCC->APB2ENR |= 0x7<<2; //en clk for GPIOA, B, C.
	RCC->APB2ENR |= 1<<9; // en clk for ADC1.
	RCC->APB2ENR |= 0x01; // en clk for AFIO.
	RCC->APB1ENR |= 0x03; // en clk for TIM2, 3.
	RCC->APB2ENR |= 1<<14 | 1<<2; // en clk for usart1, gpio A
}

void Delay_us(uint32_t d){
	uint32_t i;
	for(i=0;i<d;i++){
		SysTick->LOAD = 9-1;
		SysTick->VAL = 0;
		SysTick->CTRL |= 1<<0;
		while(!(SysTick->CTRL & 1<<16));
		SysTick->CTRL &= ~(1<<0);
	}
}

void Delay_ms(uint32_t d){
	uint32_t i;
	for(i=0;i<d;i++){
		SysTick->LOAD = 9000-1;
		SysTick->VAL = 0;
		SysTick->CTRL |= 1<<0;
		while(!(SysTick->CTRL & 1<<16));
		SysTick->CTRL &= ~(1<<0);
	}
}

void PinConf(void){
	RCC->APB2ENR |= 1<<2; //en clock for GPIO A
	GPIOA->CRL &= ~0xF;
	GPIOA->CRL |= 0x7; //ouput open drain
	GPIOA->ODR |=1;
}

void SendStart(void){
	//send start signal and wait until DHT send data.
	GPIOA->ODR &= ~(1<<0);
	Delay_ms(20);
	GPIOA->ODR |= 1;
	while ((GPIOA->IDR & 1<<0) != 0);
	while ((GPIOA->IDR & 1<<0) == 0);
  while ((GPIOA->IDR & 1<<0) != 0);
}

uint8_t ReadDHT(void){
	uint8_t i;
	uint8_t data=0;

	for(i=0; i<8;i++){
		while((GPIOA->IDR & 1<<0)==0); // wait until GPIO A high
		//use systick to determine the time of high level pinA.
		uint16_t tick_count=0;
		SysTick->LOAD = 9-1;
		SysTick->VAL = 0;
		SysTick->CTRL |= 1<<0;
		while((GPIOA->IDR & 1<<0)!=0){
			if(SysTick->CTRL & 1<<16){
				tick_count++;
				SysTick->CTRL &= ~(1<<16);
			}
		}
		if(tick_count>60) data|=1<<(7-i);
	}
	return data;
}

double	*DHT22_Data(void){
	uint8_t i;
	uint8_t dht_data[5];
	double DHT22_Data[2];
	SendStart();
	for(i=0;i<5;i++){
		dht_data[i] = ReadDHT();
	}
	humidity_integer = dht_data[0];
  humidity_decimal = dht_data[1];
  temperature_integer = dht_data[2];
  temperature_decimal = dht_data[3];
  checksum = dht_data[4];
		
	if(checksum == humidity_integer + humidity_decimal + temperature_integer + temperature_decimal){
		DHT22_Data[0] = (double)(((uint16_t)temperature_integer<<8) + (uint16_t)temperature_decimal)/10.0;
		DHT22_Data[1] = (double)(((uint16_t)humidity_integer<<8) + (uint16_t)humidity_decimal)/10.0;
	}
	return DHT22_Data;
}

double	*DHT11_Data(void){
	uint8_t i;
	uint8_t dht_data[5];
	double DHT11_Data[2];
	SendStart();
	for(i=0;i<5;i++){
		dht_data[i] = ReadDHT();
	}
	humidity_integer = dht_data[0];
  humidity_decimal = dht_data[1];
  temperature_integer = dht_data[2];
  temperature_decimal = dht_data[3];
  checksum = dht_data[4];
	if (checksum == humidity_integer + humidity_decimal + temperature_integer + temperature_decimal){
		temp = (double)temperature_integer+(double)temperature_decimal/10.0;
		humid = (double)humidity_integer + (double)humidity_decimal/10.0;
  }
		
	return DHT11_Data;
}