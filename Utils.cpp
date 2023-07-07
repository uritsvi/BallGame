#include "Utils.h"

const int H1NumOfCharsMultiplayer = 70;
const int H2NumOfCharsMultiplayer = 30;

int Utils::CalulcateH1TextWidth(int numOfChars) {
	return numOfChars * H1NumOfCharsMultiplayer;
}
int Utils::CalulcateH2TextWidth(int numOfChars) {
	return numOfChars * H2NumOfCharsMultiplayer;
}