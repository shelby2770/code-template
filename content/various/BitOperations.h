/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Common bit manipulation operations and bitset usage.
 * Usage: See examples below
 * Time: O(1) for most operations
 */
#pragma once

//Bitwise operations
num |= (1 << pos); //Set bit at position pos
num &= (~(1 << pos)); //Unset bit at position pos
num ^= (1 << pos); //Toggle bit at position pos
int ret = num & (-num); //Extract lowest set bit
bool bit = num & (1 << pos); //Check if bit at position pos is set
int ones = __builtin_popcountll(num); //Count set bits (long long)
int tz = __builtin_ctzll(num); //Count trailing zeros (long long)
int lz = __builtin_clzll(num); //Count leading zeros (long long)

//Bitset operations
bitset<32> bs; //Create a bitset of size 32 (all 0s)
bitset<32> bs(42); //From decimal number (101010)
bitset<32> bs("101010"); //From binary string
bs.set(i);  //Set bit at position i to 1
bs.reset(i); //Set bit at position i to 0
bs.flip(i); //Flip bit at position i
int count = bs.count(); //Count number of set bits
bool test = bs.test(i); //Check if bit at position i is set
bool any = bs.any(); //Check if any bit is set
bool none = bs.none(); //Check if no bit is set
bool all = bs.all(); //Check if all bits are set
size_t size = bs.size(); //Get size of bitset
string s = bs.to_string(); //Convert to string
unsigned long ul = bs.to_ulong(); //Convert to unsigned long
unsigned long long ull = bs.to_ullong(); //Convert to unsigned long long
size_t first = bs._Find_first(); //Position of first set bit
size_t next = bs._Find_next(i); //Position of first set bit after i 