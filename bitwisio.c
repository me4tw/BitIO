/**@file bitwisio.h
@brief Bitwise I/O function implementations
*/
#include "bitwisio.h"
#include <assert.h>

void bito_open(BITO *o, PSTREAM s){
	o->pStream=s;
	o->cByte=0;
	/**must be initialized to 1*/
	o->nBitCount=1;
#ifndef NDEBUG
	o->pushed_nBitCount=12;
	o->pushed_cByte=34;
	o->pushed_pStream=56;
#endif
}               

void bito_close(BITO *o){
	bito_flush(o);
}

void bito_emitBit(BITO *o, BIT nbBit){
	o->cByte<<=1;
	o->cByte|=(unsigned int)bBit;
	o->nBitCount<<=1;
	if(!nBitCount)
	{			
		*o->pStream=cByte;
		o->pStream++;			
		o->nBitCount=1;
	}
}                

void bito_emitBits(BITO *o, DWORD ctByte, DWORD nBits){
	unsigned int nI;
	ctByte<<=(31-nBits+1);
	for(nI=0;nI<nBits;nI++)
	{
		bito_emitBit(o,(BIT)(ctByte>>31));
		ctByte<<=1;
	}
}  

void bito_emitByte(BITO *o, BYTE ctByte){
	unsigned int nI;
	for(nI=0;nI<8;nI++)
	{
		bito_emitBit(o,(BIT)(ctByte>>7));
		ctByte<<=1;
	}
}            

void bito_emitWord(BITO *o, WORD w){
	unsigned int nI;
	for(nI=0;nI<16;nI++)
	{
		bito_emitBit(o,(BIT)(w>>15));
		w<<=1;
	}
}

void bito_emitDword(BITO *o, DWORD dw){
	unsigned int nI;
	for(nI=0;nI<32;nI++)
	{
		bito_emitBit(o,(BIT)(dw>>31));
		dw<<=1;
	}
}     

void bito_flush(BITO *o){
	while(o->nBitCount!=1) {
		bito_emitBit(o,0);		
	}	
}                           

void bito_push(BITO *o){
	
	assert(o->pushed_nBitCount == 12);
	assert(o->pushed_cByte     == 34);
	assert(o->pushed_pStream   == 56);
	
	o->pushed_nBitCount = o->nBitCount;
	o->pushed_cByte     = o->cByte;
	o->pushed_pStream   = o->pStream;
}               

void bito_pop(BITO *o){
	
	assert(o->pushed_nBitCount != 12/*);*/
	/*assert(*/&& o->pushed_cByte     != 34/*);*/
	/*assert(*/&& o->pushed_pStream   != 56);
	
	o->nBitCount  = o->pushed_nBitCount;
	o->cByte      = o->pushed_cByte;
	o->pStream    = o->pushed_pStream;
#ifndef NDEBUG
	o->pushed_nBitCount=12;
	o->pushed_cByte=34;
	o->pushed_pStream=56;
#endif
}             
 
PSTREAM bito_ptr(BITO *o){
	return o->pStream;
}  



typedef struct biti BITI;

void biti_init(BITI *i, PSTREAM plStream){
	i->pStream=plStream;
	i->cByte=0;
	i->nBitCount=0;
}

BIT biti_getBit(BITI *i){
	i->nBitCount>>=1;	
	if(!i->nBitCount)
	{			
		i->cByte=*i->pStream;
		i->pStream++;				
		i->nBitCount=0x80;
	}
	return i->cByte&i->nBitCount?1:0;
}

DWORD biti_getBits(BITI *i, DWORD dwBits){
	DWORD dwR=0;
	unsigned int nI;
	
	for(nI=0;nI<dwBits;nI++)
	{
		dwR|=biti_getBit(i)<<((dwBits-1)-nI);
	}
	return dwR;
}

BYTE biti_getByte(BITI *i){
	BYTE cR=0;
	unsigned int nI;
	
	for(nI=0;nI<8;nI++)
	{
		cR|=biti_getBit(i)<<(7-nI);
	}
	return cR;
}

WORD biti_getWord(BITI *i){
	WORD w=0;
	unsigned int nI;
	
	for(nI=0;nI<16;nI++)
	{
		w|=biti_getBit(i)<<(15-nI);
	}
	return w;
}

DWORD biti_getDword(BITI *i){
	DWORD dw=0;
	unsigned int nI;
	
	for(nI=0;nI<32;nI++)
	{
		dw|=biti_getBit(i)<<(31-nI);
	}
	return dw;
}

PSTREAM *biti_ptr(BITI *i){
	return i->pStream;
}

