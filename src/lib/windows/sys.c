/*
 * jgr_sys, a cross-platform library abstracting low-level system services
 * Copyright (C) 2015 J GRADIENT LLC
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * J GRADIENT LLC
 * info@jgradient.com
 */
/**
 *  @file
 *  
 *  Windows-specific implementations of functions in sys.h.
 */
#include <jgr/sys/sys.h>
#include <stdio.h>

/* Allow use of features specific to Windows 2000 or later. */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <direct.h>

const char jgr_DIRSEP_CHAR = '\\';

const char jgr_DIRSEP_STR[] = "\\";

static
void
showLastError(void);

char **
jgr_listDir(const char *path, unsigned int *count, int (*isValid)(const char *dir, const char *name))
{
	//append \\* into path
	LPSTR winPath = NULL;
	size_t len;
	BOOL hasSlash;
	HANDLE hData;
	WIN32_FIND_DATA dirData;
	DWORD err;
	char **entries = NULL;
	unsigned int i;
	
	*count = 0;
	
	len = strlen(path);
	if(path[len] == '\\') {
		++len; //only need to add a *
		hasSlash = TRUE;
	}
	else {
		len += 2; //need to add \*
		hasSlash = FALSE;
	}
	winPath = (LPSTR) malloc((len+1)*sizeof(CHAR));
	if(!winPath) {
		printf("***sys.c/jgr_listDir(): malloc returned NULL.\n");
		exit(EXIT_FAILURE);
	}
	strcpy_s(winPath, len+1, path);
	if(!hasSlash)
		winPath[len-2] = '\\';
	winPath[len-1] = '*';
	winPath[len] = '\0';
	
	/* first, count the number of entries in this directory listing */
	hData = FindFirstFile(winPath, &dirData);
	if(hData == INVALID_HANDLE_VALUE) {
		showLastError();
		free(winPath);
		return NULL;
	}
	if(isValid(path, dirData.cFileName))
		++*count;

	while(FindNextFile(hData, &dirData)) {
		if(isValid(path, dirData.cFileName))
			++*count;
	}
	err = GetLastError();
	if(err != ERROR_NO_MORE_FILES) {
		showLastError();
		free(winPath);
		return NULL;
	}
	FindClose(hData);

	entries = (LPSTR*) malloc(*count*sizeof(LPSTR));
	if(!entries) {
		printf("***sys.c/jgr_listDir(): malloc returned NULL.\n");
		exit(EXIT_FAILURE);
	}

	/* now repeat reading and do the actually storing of entries */
	i = 0;
	hData = FindFirstFile(winPath, &dirData);
	if(hData == INVALID_HANDLE_VALUE) {
		showLastError();
		free(winPath);
		free(entries);
		return NULL;
	}
	if(isValid(path, dirData.cFileName)) {
		len = strlen(dirData.cFileName);
		entries[i] = (char *) malloc((len + 1)*sizeof(char));
		strcpy_s(entries[i], len+1, dirData.cFileName);
		entries[i][len] = '\0';
		++i;
	}

	while(FindNextFile(hData, &dirData) && i < *count) {
		if(isValid(path, dirData.cFileName)) {
			len = strlen(dirData.cFileName);
			entries[i] = (char *) malloc((len + 1)*sizeof(char));
			strcpy_s(entries[i], len+1, dirData.cFileName);
			entries[i][len] = '\0';
			++i;
		}
	}
	if(i < *count) {
		err = GetLastError();
		showLastError();
		free(winPath);
		//free entries[0..i]
		free(entries);
		return NULL;
	}
	free(winPath);
	
	FindClose(hData);

	return entries;
}

int
jgr_isDirectory(const char *path)
{
	DWORD attr = GetFileAttributes(path);
	if(attr == INVALID_FILE_ATTRIBUTES)
		return 0;
	else if(attr & FILE_ATTRIBUTE_DIRECTORY)
		return 1;
	else
		return 0;
}

unsigned long long
jgr_getCurrentTimeMicros()
{
	SYSTEMTIME sysTime;
	FILETIME fileTime;
	ULARGE_INTEGER ult;
	
	GetSystemTime(&sysTime);
	if(!SystemTimeToFileTime(&sysTime, &fileTime)) {
		showLastError();
		return 0;
	}
	ult.LowPart = fileTime.dwLowDateTime;
	ult.HighPart = fileTime.dwHighDateTime;
	return (unsigned long long) ult.QuadPart / 10;
}

//we could do a MessageBox here as well
static
void
showLastError(void)
{
	PVOID msg;
	DWORD err = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
	              FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, err, 0, (LPTSTR) &msg,
                  0, NULL );
	printf("%s\n", (LPCSTR) msg);
	LocalFree(msg);
}
