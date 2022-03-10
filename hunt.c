#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = -1;

    /* TODO */

    uint64_t mask = 1, copie = memory;
    uint8_t curr_b;
    int contor = 0, a = 1, ok = 0; 
    
    while(copie && ok == 0){
	curr_b = copie & mask;
	if(curr_b == a) contor ++;
	else contor = 0;

	if(contor == 5) ok = 1;
	
	copie = copie >> 1;
    }

    uint16_t mask2 = a << 16;
    res = copie ^ mask2;

    return res;

}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = -1;

    /* TODO */

    uint64_t mask = 1, copie = memory, curr_b, one = 1, zero = 0;
    uint16_t key;
    int ok = 0, contor = 0;
    mask = (mask << 17) - 1;
    key = mask & copie;
    mask = 1;
    copie = copie >> 16;
     
    while(ok == 0 && copie){
      curr_b = copie & mask;
      copie = copie >> 1;
      if(curr_b == one){ //am gasit un 1
	contor ++; 
	if(contor == 3) //conditia de iesire din while 
	   ok = 1;
      }
      if(curr_b == zero){ // am gasit un 0
	if(contor != 0){ //am intrerupt un streak de 1
	  for(int i = 1; i <= contor; i++){ //adaugam acei 1 gasiti pana atunci
	     key = key >> 1;                //si pe care i am ignorat
	     key = key + (mask << 15);
	  }
	}
	contor = 0;
	key = key >> 1;
	}
    }
    res = key;
    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;

    /* TODO */

    res = spell ^ key;

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1;

    /* TODO */    
    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = -1;

    /* TODO */
    uint32_t antibodies_high, antibodies_low;

    antibodies_high = cocktail;
    antibodies_low = 0;
    
    res = antibodies_high;
    res = res << 16;
    res += antibodies_low;

    return res;
}



uint8_t is_Brokilon(uint64_t map){
    uint64_t copie = map, mask = 1, curr_b, one = 1, zero = 0;
    int ok = 1, contor = 0;
    uint8_t index;
    
    if(map == zero) index = 0;
    else{
      while(copie && ok == 1){
        curr_b = mask & copie; //iau fiecare bit pe rand
        copie = copie >> 1; 
        if(curr_b == one){ // am gasit un 1
          contor ++;
          for(int i = 1; i < 4; i++){ //testez urmatorii 3 biti 
            if((copie & mask) == one)
              contor ++;
            else{
              ok = 0; // am gasit o secventa care nu are 4 copaci, nu e Brokilon
              break;
            }
            copie = copie >> 1;
          }
        }
        contor = 0;
      }
    }
    if(ok == 1) index = 0;
    else index = -1;

    if(map == -1) index = -1;
    
    return index;
}

uint8_t is_Wolven(uint64_t map){
   uint64_t copie = map, mask = 1, curr_b, one = 1;
   int ok = 1;
   uint8_t index = -1;

   while(copie && ok == 1){
	curr_b = copie & mask; //iau fiecare bit pe rand
	copie = copie >> 1;
	if(curr_b != one) ok = 0;  //testam daca e 1
   }                               //daca e dif de 1 atunci nu e Wolven

   if(ok == 1) index = 2;
   return index;


}

uint8_t is_Hindar(uint64_t map){

   uint64_t copie = map, mask = 1, curr_b, one = 1;
   int ok = 1, contor = 0;
   uint8_t index;

   while(copie && ok == 1){
        curr_b = mask & copie;
        copie = copie >> 1;
        if(curr_b == one) contor ++;
        if(contor > 2) ok = 0;
      }
   if(ok == 1) index = 1;
   else index = -1;
   
   return index;

}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = -1;

    /* TODO */
     
    res = is_Brokilon(map);   //testam daca e Brokilom
    if(res == 0) return res;  
    else res = is_Hindar(map); //testam daca e Hindar

    if(res == 1) return res;  
    else res = is_Wolven(map); //testam daca e Wolven
    
    if(res == 2) return res;
    else res = 3;              //daca nu e nici una din ele, este Caed Dhu
    
    
    return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = -1;

    /* TODO */
    
    uint32_t mask = 1, copie = map, curr_b, one = 1, sec_b;
    int  ok = 0, contor = 0;
     
    while(ok == 0){
      curr_b = copie & mask;
      copie = copie >> 1;
      if(curr_b == one){
        while(ok == 0){
	  sec_b = copie & mask;
	  copie = copie >> 1;
	  if(sec_b == one)
            ok = 1;
	  else contor ++;
	 }
       }
     }

    res = contor + 1;

    return res;
}
