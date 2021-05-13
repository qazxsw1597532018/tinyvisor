#include "Log.h"

#define BAUD_RATE 11520

extern EFI_BOOT_SERVICES* gBS;

EFI_SERIAL_IO_PROTOCOL* gSerialIoProtocol = NULL;

EFI_STATUS InitializeLogging() {
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GUID SerialIoProtocolGuid = EFI_SERIAL_IO_PROTOCOL_GUID;
    EFI_CHECK(gBS->LocateProtocol(&SerialIoProtocolGuid, NULL, (VOID**)&gSerialIoProtocol));

    EFI_CHECK(gSerialIoProtocol->Reset(gSerialIoProtocol));
    EFI_CHECK(gSerialIoProtocol->SetAttributes(gSerialIoProtocol, BAUD_RATE, 0, 0, 0, 0, 0));

Cleanup:
    return Status;
}

EFI_STATUS LogCharacter(CHAR8 Char) {
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Size = 1;
    EFI_CHECK(gSerialIoProtocol->Write(gSerialIoProtocol, &Size, &Char));

Cleanup:
    return Status;
}

EFI_STATUS LogString(const CHAR8* String) {
    EFI_STATUS Status = EFI_SUCCESS;
    while (*String) {
        EFI_CHECK(LogCharacter(*String++));
    }

Cleanup:
    return Status;
}

/**
 * @brief Write a string representation of num to buffer
 * @param Buffer the buffer the string is written to
 * @param Size the size of the buffer
 * @param Sign Whether or not the value was originally of a signed type
 * @param Number the value cast to a UINTN
 * @param Base the base the representation should be in
 * @return where in the string the representation starts
 */
UINTN ToString(CHAR8* Buffer, UINTN Size, BOOLEAN Sign, UINTN Number, int Base) {
    static const CHAR8* Representation = "0123456789abcdef";
    CHAR8* Ptr = &Buffer[Size - 1];
    *Ptr = '\0';

    // Optimization: use sign to say if the value is negative
    if (Sign) {
        Sign = ((INTN)Number) < 0;
        if (Sign) {
            // If it's negative, we need to turn it positive or our logic breaks
            Number *= -1;
        }
    }

    do {
        *--Ptr = Representation[Number % Base];
        Number /= Base;
    } while (Number != 0);

    // Append a '-' if num was originally negative
    if (Sign) {
        *--Ptr = '-';
    }

    return Ptr - Buffer;
}

EFI_STATUS LogFormat(const CHAR8* Format, ...) {
    EFI_STATUS Status = EFI_SUCCESS;
    const CHAR8* Current = NULL;
    UINTN CurrentArg = 0;
    CHAR8 Buffer[32] = { 0 };
    int Length = 0;

    __builtin_va_list Arg;
    __builtin_va_start(Arg, Format);
    for (Current = Format; *Current; Current++) {
        while (*Current != '%') {
            if (*Current != '\n') {
                EFI_CHECK(LogCharacter(*Current));
            } else {
                EFI_CHECK(LogString("\r\n"));
            }

            Current++;
            if (!*Current) {
                EFI_SUCCEED();
            }
        }

        Current++;
        if (!*Current) {
            EFI_SUCCEED();
        }

        while (*Current == 'l') {
            Length++;
            Current++;
            if (!*Current) {
                EFI_SUCCEED();
            }
        }

        switch (*Current) {
            case 'c':
                CurrentArg = __builtin_va_arg(Arg, int);
                EFI_CHECK(LogCharacter(CurrentArg));
                break;
            case 's':
                CurrentArg = (UINTN)__builtin_va_arg(Arg, CHAR16*);
                EFI_CHECK(LogString((const CHAR8*)CurrentArg));
                break;
            case 'd':
                switch (Length) {
                    case 2:
                        CurrentArg = __builtin_va_arg(Arg, long long int);
                        break;
                    case 1:
                        CurrentArg = __builtin_va_arg(Arg, long int);
                        break;
                    default:
                        CurrentArg = __builtin_va_arg(Arg, int);
                }
                EFI_CHECK(LogString(Buffer + ToString(Buffer, COUNT_OF(Buffer), TRUE, CurrentArg, 10)));
                break;
            case 'u':
                switch (Length) {
                    case 2:
                        CurrentArg = __builtin_va_arg(Arg, long long unsigned int);
                        break;
                    case 1:
                        CurrentArg = __builtin_va_arg(Arg, long unsigned int);
                        break;
                    default:
                        CurrentArg = __builtin_va_arg(Arg, unsigned int);
                }
                EFI_CHECK(LogString(Buffer + ToString(Buffer, COUNT_OF(Buffer), FALSE, CurrentArg, 10)));
                break;
            case 'x':
                switch (Length) {
                    case 2:
                        CurrentArg = __builtin_va_arg(Arg, long long unsigned int);
                        break;
                    case 1:
                        CurrentArg = __builtin_va_arg(Arg, long unsigned int);
                        break;
                    default:
                        CurrentArg = __builtin_va_arg(Arg, unsigned int);
                }
                EFI_CHECK(LogString(Buffer + ToString(Buffer, COUNT_OF(Buffer), FALSE, CurrentArg, 16)));
                break;
            case 'p':
                CurrentArg = (UINTN)__builtin_va_arg(Arg, void*);
                EFI_CHECK(LogString(Buffer + ToString(Buffer, COUNT_OF(Buffer), FALSE, CurrentArg, 16)));
                break;
        }

        gBS->SetMem(Buffer, 0, sizeof(Buffer));
        Length = 0;
    }

Cleanup:
    __builtin_va_end(Arg);
    return Status;
}