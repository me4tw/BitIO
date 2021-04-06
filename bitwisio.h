/**@file bitwisio.h
@brief Bitwise I/O functions
*/
#ifndef bitwisio_h
#define bitwisio_h

/** pointer to a stream of bytes */
typedef unsigned char * PSTREAM;

/**some kind of basic type, could be an int */
typedef unsigned char BIT;

/** must be a 32bit type */
typedef unsigned long DWORD;

/** must be a 8bit type */
typedef unsigned char BYTE;

/** must be a 16bit type */
typedef unsigned short WORD;

/**bit input state struct*/
struct biti {
	/**current count of bits in cByte*/
	DWORD nBitCount;                
	/**current byte being read for input*/
	BYTE cByte;                      
	/**pointer to the input buffer*/
	PSTREAM pStream;
};
/** Bit Input State*/
typedef struct biti BITI;
/**constructor, supply pointer to input buffer*/
void biti_init(BITI *i, PSTREAM);                 
/**read a single bit*/
BIT biti_getBit(BITI *i);                   
/**read X number of bits*/
DWORD biti_getBits(BITI *i, DWORD dwBits); 
/** read a byte*/
BYTE biti_getByte(BITI *i);                 
/**read a word*/
WORD biti_getWord(BITI *i);                  
/**read a dword*/
DWORD biti_getDword(BITI *i);                
/**get a pointer to the input stream*/
PSTREAM *biti_ptr(BITI *i);                  

/**bit output state struct*/
struct bito {
	/**current count of bits in cByte*/
	BYTE nBitCount;                         
	/**holder of bits*/
	BYTE cByte;                             
	/**pointer to the output stream*/
	PSTREAM pStream;                        
	/**holder for pushed position in output stream (bit count)*/
	BYTE pushed_nBitCount;                  
	/**holder for pushed position in output stream (current bits)*/
	BYTE pushed_cByte;                      
	/**holder for pushed position in output stream (pointer)*/
	PSTREAM pushed_pStream;                 
};
/**Bit Output State*/
typedef struct bito BITO;

/**constructor, supply the output buffer*/
void bito_open(BITO *o, PSTREAM s);                
/**destructor, flushes output buffer*/
void bito_close(BITO *o);
/**emit a bit*/
void bito_emitBit(BITO *o, BIT nbBit);                
/**emit a number of bits*/
void bito_emitBits(BITO *o, DWORD dwBits, DWORD dwBitCount);  
/**emit a byte*/
void bito_emitByte(BITO *o, BYTE nbByte);             
/**emit a word*/
void bito_emitWord(BITO *o, WORD wWord);              
/**emit a dword*/
void bito_emitDword(BITO *o, DWORD dwDword);          
/**flush the output buffer */
void bito_flush(BITO *o);                           
/**
push the current position of the output stream
(only one position in stack). the following save and restore
the current stream position. Please note that this 
mechanism only allows for one push, obviously.
Since more are not needed, a more complex
structure will hinder performance. Implement
typical stack if more are needed at any point.

In a debug build it will fail an assertion check if you try
to push twice in a row without popping first.
*/
void bito_push(BITO *o);                            
/**
pop the output stream position. will fail an assertion
check on a debug build if you try to pop twice in a row.
*/
void bito_pop(BITO *o);                           
/** pointer to the output stream */  
PSTREAM bito_ptr(BITO *o);                         

#endif
