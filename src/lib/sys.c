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
 * @file
 * 
 * Implementations of functions in sys.h. 
 */
#include <jgr/sys/sys.h>
#include <stdlib.h>

/* OS-specific implementations */
#if defined(_WIN32) || defined(_WIN64)
	#include "windows/sys.c"
#else
	#include "linux/sys.c"
#endif

const char *
jgr_sys_version(void)
{
	return JGR_SYS_VERSION_STR;
}

void
jgr_freeDirEntries(char **entries, unsigned int count)
{
	unsigned int i;
	
	for(i = 0; i < count; ++i)
		free(entries[i]);
	free(entries);
}
