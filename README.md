# BitIO
BitWise Input Output

Usage like so
~~~{.c}
BITO o;
char dat[2]; //our output data buffer
memset(dat, 0, sizeof dat);
bito_init(&o,dat);
//the binary we want to send into our output buffer
bito_emitBit(&o,0);
bito_emitBit(&o,1);
bito_emitBit(&o,0);
bito_emitBit(&o,1);
bito_close(&o);
~~~
which will set dat to equal 0101 0000 0000 0000 for example.
