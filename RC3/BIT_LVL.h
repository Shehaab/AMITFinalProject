#define SET_BIT(reg,pin) reg|=(1<<pin)
#define CLR_BIT(reg,pin) reg&=(~(1<<pin))

#define GET_BIT(reg,pin) ((reg>>pin)&1)