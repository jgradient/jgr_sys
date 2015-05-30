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
#include <jgr/sys/sys.h>
#include <stdio.h>
#include <stdlib.h>

int
allEntries(const char *dir, const char *name);

int
main(void)
{
	unsigned long long tic, toc;
	unsigned int i, count;
	char **entries;
	
	tic = jgr_getCurrentTimeMicros();
	printf("jgr_sys version: '%s'\n", jgr_sys_version());
	printf("jgr_sys directory separator char: '%c'\n", jgr_DIRSEP_CHAR);
	printf("jgr_sys directory separator string: '%s'\n", jgr_DIRSEP_STR);
	
	printf("Current directory file listing:\n");
	entries = jgr_listDir(".", &count, allEntries);
	for(i = 0; i < count; ++i)
		printf(" - '%s'\n", entries[i]);
	jgr_freeDirEntries(entries, count);
	
	toc = jgr_getCurrentTimeMicros();
	printf("Test took %llu microseconds\n", (toc - tic));
	
	return 0;
}

int
allEntries(const char *dir, const char *name)
{
	return 1;
}
