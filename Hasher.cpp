#include "Hasher.hpp"
/* Description: converts string into its base 256
 *
 * Big O: O(n) n = string
 * (it wont be very long ever so might as well be O(1) if we implement a username max length)
 */
int base256conversion(const std::string &s) {
	int base = 0;
	int power = 1;
	for(int i = s.length(); i > 0; i--){
		base += (s[i-1] * power);
		power *= 256;
	}
	return base;
}
/* Description: converts a given string into a hash number via base246 and seperating the string into chunks
 *
 * Big O: technically its O(n^2)
 * 		  n = string length
 * 		  but given the size of the strings it might as well be O(1)
 */
int hashString(const std::string &s, int foldNum) {
	int hashed = 0;
	for(int i = 0; i < s.length(); i += foldNum){
		hashed += base256conversion(s.substr(i, foldNum));
	}
	return hashed;
}
