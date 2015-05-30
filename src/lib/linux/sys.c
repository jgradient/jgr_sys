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
 *  Linux/Unix specific implementations of functions in sys.h.
 */

#include <jgr/sys/sys.h>
#include <string.h>
#include <stdio.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

#ifdef __APPLE__
#include <sys/sysctl.h>
#endif

const char jgr_DIRSEP_CHAR = '/';

const char jgr_DIRSEP_STR[] = "/";

char **
jgr_listDir(const char *path, unsigned int *count, int (*isValid)(const char *dir, const char *name))
{
	unsigned int i;
	size_t len;
	struct dirent *entry;
	char **entries;
	DIR *imgDir = NULL;
	
	*count = 0;
	
	errno = 0;
	imgDir = opendir(path);
	if(!imgDir) {
		perror("***sys.c/jgr_listDir(): There was an error opening a "
		       "directory");
		return NULL;
	}
	
	//first we need to count the number of entries
	errno = 0;
	entry = NULL;
	while((entry = readdir(imgDir))) {
		
		if(!isValid(path, entry->d_name)) {
			errno = 0;
			continue;
		}
		
		errno = 0;
		++*count;
	}
	if(errno) {
		perror("***sys.c/jgr_listDir(): There was an error reading a "
		       "directory");
		return NULL;
	}
	
	entries = (char **) malloc(*count*sizeof(char *));
	if(!entries) {
		printf("***sys.c/jgr_listDir(): malloc returned NULL.\n");
		exit(EXIT_FAILURE);
	}
	
	rewinddir(imgDir);
	
	//now we can store the entries
	i = 0;
	errno = 0;
	entry = NULL;
	while((entry = readdir(imgDir)) && i < *count) {
		
		if(!isValid(path, entry->d_name)) {
			errno = 0;
			continue;
		}
		
		len = strlen(entry->d_name);
		
		entries[i] = (char *) malloc((len + 1)*sizeof(char));
		if(!entries[i]) {
			printf("***sys.c/jgr_listDir(): malloc returned NULL.\n");
			exit(EXIT_FAILURE);
		}
		strncpy(entries[i], entry->d_name, len);
		entries[i][len] = '\0';
		
		++i;
		errno = 0;
	}
	if(errno) {
		perror("***sys.c/jgr_listDir(): There was an error reading a "
		       "directory");
		return NULL;
	}
	closedir(imgDir);
	
	return entries;
}

int
jgr_isDirectory(const char *path)
{
	DIR *dir = NULL;
	
	errno = 0;
	dir = opendir(path);
	if(dir == NULL && (errno == ENOTDIR || errno == ENOENT))
		return 0;
	else {
		if(dir)
			closedir(dir);
		return 1;
	}
}

unsigned long long
jgr_getCurrentTimeMicros()
{
	errno = 0;
#ifdef __APPLE__
	struct timeval tv;

	if(!gettimeofday(&tv, NULL)) {
		perror("***sys.c/jgr_getCurrentTimeMicros()");
		return 0;
	}

	return (unsigned long long) (tv.tv_sec*1000*1000 + tv.tv_usec);
#else
	struct timespec ts;

	if(clock_gettime(CLOCK_REALTIME, &ts)) {
		perror("***sys.c/jgr_getCurrentTimeMicros()");
		return 0;
	}

	return (unsigned long long) (ts.tv_sec*1000*1000 + ts.tv_nsec / 1000);
#endif
}
