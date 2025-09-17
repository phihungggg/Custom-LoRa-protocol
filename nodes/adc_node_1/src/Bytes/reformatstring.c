



#include "Work_with_bytes/reformatstring.h"

uint8_t* reformatstring (uint8_t *inputstring,uint16_t sizeofstring );


uint8_t* reformatstring (uint8_t *inputstring,uint16_t sizeofstring ){

uint8_t *outputstring ;

printf(" reformating \n");


printf(" size %d \n",sizeofstring);

outputstring=(uint8_t*)malloc((sizeofstring+1) * sizeof(uint8_t));

outputstring[0] = sizeofstring;

for ( int i=1;i<=sizeofstring;++i)
{
outputstring[i] = inputstring[i-1];
}

printf(" test reformatstring \n");



for ( int i =0;i<=sizeofstring;++i)
{

    printf(" %d ", outputstring[i]);


}

return outputstring;
}