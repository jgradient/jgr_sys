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
 * Declarations of constants and functions for low-level system services.
 */
#ifndef JGR_SYS_SYS_H
#define JGR_SYS_SYS_H

#if defined(_WIN32) || defined(_WIN64)
	#ifdef jgr_sys_EXPORTS
		#define JGR_SYS_EXPORT_DECL __declspec(dllexport)
	#else
		#define JGR_SYS_EXPORT_DECL __declspec(dllimport)
	#endif
#else
	#ifdef jgr_sys_EXPORTS
		#define JGR_SYS_EXPORT_DECL __attribute__ ((visibility ("default")))
	#else
		#define JGR_SYS_EXPORT_DECL 
	#endif
#endif

#include <jgr/sys/version.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Directory separator character.
 */
JGR_SYS_EXPORT_DECL
extern
const char
jgr_DIRSEP_CHAR;

/**
 * Directory separator string.
 */
JGR_SYS_EXPORT_DECL
extern
const char
jgr_DIRSEP_STR[];

/**
 * Get the library version string.
 * 
 * @return the version string
 */
JGR_SYS_EXPORT_DECL
const char *
jgr_sys_version(void);

/**
 * List directory entries and filter them using a validation function.
 *
 * Subdirectories are not recursively explored. The returned entries are in no 
 * particular order.
 * 
 * The simplest filtering function is one that always returns non-zero and thus
 * allows the listing of all directory contents:
 * 
 *     int
 *     allEntries(const char *dir, const char *name)
 *     {
 *         return 1;
 *     }
 * 
 * @param[in]  path the directory to enumerate
 * @param[out] count this will store the number of directory entries (size of
 *                   the returned array)
 * @param[in]  isValid filtering function. Returns non-zero if the file name is
 *                     accepted into the result set, and zero otherwise.
 * @return an array of directory entries (filenames) that were accepted by the
 *         filtering function. The array should be freed with 
 *         jgr_freeDirEntries().
 * @return NULL, if any error occurs.
 */
JGR_SYS_EXPORT_DECL
char **
jgr_listDir(const char *path, unsigned int *count, int (*isValid)(const char *dir, const char *name));

/**
 * Deallocate the directory entries returned by jgr_listDir().
 *
 * @param[in] entries an array of directory entries (strings)
 * @param[in] count the length of the entries array
 */
JGR_SYS_EXPORT_DECL
void
jgr_freeDirEntries(char **entries, unsigned int count);

/**
 * Determine if the file path points to a directory.
 *
 * @param[in] path file path to check
 * @return non-zero if the path is a directory, zero otherwise
 */
JGR_SYS_EXPORT_DECL
int
jgr_isDirectory(const char *path);

/**
 * Returns the current time in microseconds relative to a base date.
 * 
 * The base date may differ between platforms. On UNIX, this is epoch. On 
 * Windows, this is January 1, 1601. Therefore, this function is meant to be 
 * used to measure relative time.
 * 
 * @return time in microseconds
 */
JGR_SYS_EXPORT_DECL
unsigned long long
jgr_getCurrentTimeMicros();

#ifdef __cplusplus
}
#endif

#endif
