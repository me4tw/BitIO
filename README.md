# BitIO
BitWise Input Output

Usage like so
~~~{.c}
BITO o;
char dat[2];
memset(&dat[0], 0, sizeof dat);
bito_init(&o,dat);
bito_emitBit(&o,0);
bito_emitBit(&o,1);
bito_emitBit(&o,0);
bito_emitBit(&o,1);
bito_close(&o);
~~~
which will set dat to equal 0101 0000 0000 0000 for example.
