#ifndef _TINYVISOR_LOG_H
#define _TINYVISOR_LOG_H

#include <Uefi.h>

/*************************************
 * Functionallity related to logging *
 *************************************/

/**
 * @brief Initializes serial logging
 * @return a status code
 */
EFI_STATUS InitializeLogging();

/**
 * @brief Logs a single character
 * @param Char the character to log
 * @return a status code
 */
EFI_STATUS LogCharacter(CHAR8 Char);

/**
 * @brief Logs a null-terminated string
 * @param String the string to log
 * @return a status code
 */
EFI_STATUS LogString(const CHAR8* String);

/**
 * @brief Logs a format string
 * @param Format the format string
 * @param ... additional arguments
 * @return a status code
 */
EFI_STATUS LogFormat(const CHAR8* Format, ...);

#define LOG(Fmt, ...) LogFormat("[tinyvisor] " Fmt "\n", ##__VA_ARGS__)

#endif // _TINYVISOR_LOG_H
