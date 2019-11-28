#include <thread>
#include <string>
#include <Windows.h>

#include <iostream>

#define MilliSeconds(millisecs) ((millisecs) / 10 % 100)
#define Seconds(millisecs) ((millisecs) / 1000 % 60)
#define Minutes(millisecs) ((millisecs) / 60000 % 60)
#define Hours(millisecs) ((millisecs) / 3600000 % 60)

#define digitWidth 7
#define digitHeight 7

using namespace std;




wchar_t* screen;
wstring digits[11];

int ScreenWidth = 120;
int ScreenHeight = 30;

POINT ulPointDigit;

int i;

void DrowNum(short place, unsigned int& millisec) {
	static byte N1, N2;
	static int px, py;

	ulPointDigit = { (ScreenWidth - 11 * digitWidth) / 2 + (place + place / 2 - 1) * digitWidth, (ScreenHeight - digitHeight) / 2 };
	
	switch (place)
	{
	case 1: N1 = Hours(millisec); break;
	case 3: N1 = Minutes(millisec); break;
	case 5: N1 = Seconds(millisec); break;
	case 7: N1 = MilliSeconds(millisec); break;
	default: N1 = 10; break;
	}

	if (place % 2 == 1) {
		N2 = N1 % 10;
		N1 /= 10;

		for (px = 0; px < digitWidth; px++)
			for (py = 0; py < digitHeight; py++)
				screen[(ulPointDigit.y + py) * ScreenWidth + (ulPointDigit.x + digitWidth + px)] = digits[N2][py * digitWidth + px];
	}

	for (px = 0; px < digitWidth; px++)
		for (py = 0; py < digitHeight; py++)
			screen[(ulPointDigit.y + py) * ScreenWidth + (ulPointDigit.x + px)] = digits[N1][py * digitWidth + px];
}

void DrowText(string &text) {
	for (i = 0; i < text.length(); i++) screen[((ScreenHeight - digitHeight) / 2 + 2 * digitHeight) * ScreenWidth + (ScreenWidth - text.length()) / 2 + i] = text[i];
}

int main()
{
	digits[0].append(L" ##### ");
	digits[0].append(L"##   ##");
	digits[0].append(L"##   ##");
	digits[0].append(L"##   ##");
	digits[0].append(L"##   ##");
	digits[0].append(L"##   ##");
	digits[0].append(L" ##### ");

	digits[1].append(L"   ##  ");
	digits[1].append(L"  ###  ");
	digits[1].append(L" ####  ");
	digits[1].append(L"   ##  ");
	digits[1].append(L"   ##  ");
	digits[1].append(L"   ##  ");
	digits[1].append(L"#######");

	digits[2].append(L" ##### ");
	digits[2].append(L"##   ##");
	digits[2].append(L"#    ##");
	digits[2].append(L"   ### ");
	digits[2].append(L" ####  ");
	digits[2].append(L"###    ");
	digits[2].append(L"#######");
	
	digits[3].append(L" ##### ");
	digits[3].append(L"#    ##");
	digits[3].append(L"    ## ");
	digits[3].append(L"  #### ");
	digits[3].append(L"    ## ");
	digits[3].append(L"#   ###");
	digits[3].append(L" ##### ");

	digits[4].append(L"##   ##");
	digits[4].append(L"##   ##");
	digits[4].append(L"##   ##");
	digits[4].append(L"#######");
	digits[4].append(L"     ##");
	digits[4].append(L"     ##");
	digits[4].append(L"    ###");

	digits[5].append(L"#######");
	digits[5].append(L"##     ");
	digits[5].append(L"##     ");
	digits[5].append(L"###### ");
	digits[5].append(L"    ###");
	digits[5].append(L"    ###");
	digits[5].append(L"###### ");

	digits[6].append(L" ##### ");
	digits[6].append(L"##     ");
	digits[6].append(L"##     ");
	digits[6].append(L"###### ");
	digits[6].append(L"##   ##");
	digits[6].append(L"##   ##");
	digits[6].append(L" ##### ");

	digits[7].append(L"#######");
	digits[7].append(L"     ##");
	digits[7].append(L"    ## ");
	digits[7].append(L" ##### ");
	digits[7].append(L"  ##   ");
	digits[7].append(L" ##    ");
	digits[7].append(L" ##    ");

	digits[8].append(L" ##### ");
	digits[8].append(L"#     #");
	digits[8].append(L"#     #");
	digits[8].append(L" ##### ");
	digits[8].append(L"#     #");
	digits[8].append(L"#     #");
	digits[8].append(L" ##### ");

	digits[9].append(L" ##### ");
	digits[9].append(L"#    ##");
	digits[9].append(L"#    ##");
	digits[9].append(L" ######");
	digits[9].append(L"     ##");
	digits[9].append(L"     ##");
	digits[9].append(L" ##### ");

	digits[10].append(L"       ");
	digits[10].append(L"  ###  ");
	digits[10].append(L"  ###  ");
	digits[10].append(L"       ");
	digits[10].append(L"  ###  ");
	digits[10].append(L"  ###  ");
	digits[10].append(L"       ");

	
	//			HH:MM:SS:Ms

	screen = new wchar_t[ScreenWidth * ScreenHeight];
	
	for (i = 0; i < ScreenWidth * ScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	
	unsigned int millisec;

	int state = 0;

	string text[2] = { "for start press spacebar", "for stop press spacebar" };

	while (true) {
		millisec = 0;

		for (i = 1; i <= 7; i++) DrowNum(i, millisec);
		
		DrowText(text[0]);

		if (0x8000 & GetAsyncKeyState(VK_SPACE)) {
			if (state == 0) state = 1;
		}
		else state = 0;

		while (state >= 1) {
			if (0x8000 & GetAsyncKeyState(VK_SPACE)) {
				if (state == 2) state = -1;
			}
			else state = 2;

			for (i = 1; i <= 7; i++) DrowNum(i, millisec);

			DrowText(text[1]);

			millisec++;

			WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth * ScreenHeight, { 0,0 }, &dwBytesWritten);
			this_thread::sleep_for(1ms);
		}

		WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth* ScreenHeight, { 0,0 }, & dwBytesWritten);
	}
}