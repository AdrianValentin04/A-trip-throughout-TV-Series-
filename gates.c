#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */ 

    uint64_t temp;

    if(i == 0)             
	temp = nr; 
    else temp = nr >> i; //shiftam la stanga cu i pozitii ca sa avem bitul
    			 //cerut pe pozitia de LSB
    if(temp & 1)         //testam daca bitul cerut e 0 sau 1
	res = 1;
    else res = 0; 

    return res;
}

uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;
    uint64_t one = 1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */ 
    
    res = nr ^ (one << i);

    return res;

}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;
    uint64_t one = 1;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    res = nr | (one << i);


    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;
    uint64_t one = 1;
    
    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    res = nr & ~(one << i);
     
    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */

    uint8_t temp; 
    temp = nand_gate(a, b);
    res = nand_gate(temp, temp);

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */
   
    res = nand_gate(a, a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */

    uint8_t temp1, temp2;
    temp1 = nand_gate(a, a);
    temp2 = nand_gate(b, b);
    res = nand_gate(temp1, temp2);

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */
    
    uint8_t temp1, temp2, temp3;
    temp1 = nand_gate(a, b);
    temp2 = nand_gate(temp1, a);
    temp3 = nand_gate(temp1, b);
    res = nand_gate(temp2, temp3);

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */

    return res;
}
