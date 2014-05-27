#include "stdafx.h"
#include "Headers\\gengine.h"


void CGEngine::rebuildMp3List(const char* baseDir)
{
	mpFiles.clear();
	WIN32_FIND_DATAA fData;

	char lookMask[256];
	sprintf_s(lookMask, "%s\\*.mp3", baseDir);
		
	HANDLE hFind = FindFirstFileA(lookMask, &fData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return;
	}
	do
	{
		if (!(fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			CMP3File nf;
			sprintf_s(nf.fName, "%s\\%s", baseDir, fData.cFileName);
			mpFiles.push_back(nf);
		}
	} while (FindNextFileA(hFind, &fData) != 0);
	FindClose(hFind);

	lastSong = 0;
}

void CGEngine::updateSong()
{
	if (curStream)
	{
		if (BASS_ChannelIsActive(curStream) != BASS_ACTIVE_PLAYING)
		{
			BASS_StreamFree(curStream);
			curStream = 0;
		}
		return;
	}

	lastSong++;
	if (lastSong >= int(mpFiles.size())) lastSong = 0;
	switchMp3(lastSong);
}

void CGEngine::switchMp3(int i)
{
	if (!mpFiles.size()) return;
	if (curStream)
	{
		BASS_ChannelStop(curStream);
		Sleep(0);
		BASS_StreamFree(curStream);
		curStream = 0;
	}
	CMP3File& f = mpFiles[i];
	curStream = BASS_StreamCreateFile(FALSE, f.fName, 0, 0, 0);
	BASS_ChannelPlay(curStream, FALSE);
	Sleep(0);
	lastSong = i;
}

void CGEngine::startPlaying()
{
	if (mpFiles.size())
		/*switchMp3*/(rand() % ((int)mpFiles.size()));
}