#include "communication.h"
#include "util_comm.h"

#include <stdio.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */

    send_squanch(18); //R
    send_squanch(9);  //I
    send_squanch(3);  //C
    send_squanch(11); //K

}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    for(int i = 1; i <=5; i++)
	fprintf(stdout, "%c", recv_squanch()+64);

}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */
     char c;
 
     for(int j = 1; j <=10; j++){
        c = recv_squanch();
	send_squanch(c);
	send_squanch(c);   
     }
}

/* Task 2 - Waiting for the Message */

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */

    uint8_t length = 10;
    uint8_t length_encoded;
    length_encoded = length << 2;
    send_squanch(length_encoded); //length

    send_squanch(8);  //H
    send_squanch(5);  //E
    send_squanch(12); //L
    send_squanch(12); //L
    send_squanch(15); //O
    send_squanch(20); //T
    send_squanch(8);  //H
    send_squanch(5);  //E
    send_squanch(18); //R
    send_squanch(5);  //E

}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */

     int length_encoded;
     length_encoded = recv_squanch();
     int length, mask = 15;
     length = (length_encoded >> 2) & mask;
     fprintf(stdout, "%d", length);

     for(int i = 1; i <= length; i ++)
         fprintf(stdout, "%c", recv_squanch()+64);
}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */
     uint8_t length_sent, length_encoded_sent, length_encoded, length, mask = 15;
     uint8_t last_c, P = 16 ;     
      	
     length_encoded = recv_squanch();
     length = (length_encoded >> 2) & mask;

     for(int j = 1; j <= length; j++){  
        last_c = recv_squanch();
     }

     if(last_c == P){
       length_sent = 10;
       length_encoded_sent = length_sent << 2;
       send_squanch(length_encoded_sent); //length

       send_squanch(16);  //P
       send_squanch(9);   //I
       send_squanch(3);   //C
       send_squanch(11);  //K
       send_squanch(12);  //L
       send_squanch(5);   //E
       send_squanch(18);  //R
       send_squanch(9);   //I
       send_squanch(3);   //C
       send_squanch(11);  //K
     }
     else{
       length_sent = 11;
       length_encoded_sent = length_sent << 2;
       send_squanch(length_encoded_sent); //length

       send_squanch(22);  //V
       send_squanch(9);   //I
       send_squanch(14);  //N
       send_squanch(4);   //D
       send_squanch(9);   //I
       send_squanch(3);   //C
       send_squanch(1);   //A
       send_squanch(20);  //T
       send_squanch(15);  //O
       send_squanch(18);  //R
       send_squanch(19);  //S
    }   
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */

  uint8_t copie1 = c1, copie2 = c2, res = 0, curr_b, mask = 1;
  
  //pt caracter 1
  for(int i = 0; i < 4; i++){
     curr_b = copie1 & mask;
     res = res + (curr_b << (2 * i + 1));
     copie1 = copie1 >> 1;
  }

  //pt caracter 2
  for(int i = 0; i < 4; i++){
     curr_b = copie2 & mask;
     res = res + (curr_b << (2 * i));
     copie2 = copie2 >> 1;
  }

  send_squanch(res);  

}


uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */
    
   uint8_t c1 = 0, c2 = 0, mask = 1, curr_b;
   
   for(int i = 0; i < 8; i++){
      curr_b = c & (mask << i);
      curr_b = curr_b >> i;

      if(i % 2 == 0)
        c2 = c2 + (curr_b << (i / 2));
      else
	c1 = c1 + (curr_b << ((i - 1) / 2));
   }
   res = 0;
   res = (c1 << 4) + c2;
   
    return res;
}
