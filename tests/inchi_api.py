import ctypes
from pathlib import Path
from typing import Callable, Final

INCHI_LIB_PATH: Final = Path().absolute() / "libinchi.so.1"
INCHI_LIB: Final = ctypes.CDLL(INCHI_LIB_PATH)
MAKE_INCHI_FROM_MOLFILE_TEXT: Final[Callable] = INCHI_LIB.MakeINCHIFromMolfileText
FREE_INCHI: Final[Callable] = INCHI_LIB.FreeINCHI


class InChIOutput(ctypes.Structure):
    # zero-terminated C-strings allocated by GetINCHI()
    # to deallocate all of them call FreeINCHI() (see below)
    _fields_ = [
        ("szInChI", ctypes.POINTER(ctypes.c_char)),
        ("szAuxInfo", ctypes.POINTER(ctypes.c_char)),
        ("szMessage", ctypes.POINTER(ctypes.c_char)),
        ("szLog", ctypes.POINTER(ctypes.c_char)),
    ]


def make_inchi_from_molfile_text(
    molfile: str, inchi_options: str = ""
) -> tuple[int, str, str, str, str]:
    """`INCHI-1-SRC/INCHI_API/demos/python_sample` stripped to the essentials."""

    c_molfile = ctypes.c_char_p(molfile.encode("utf-8"))
    c_inchi_options = ctypes.c_char_p(inchi_options.encode("utf-8"))

    szInChI = ctypes.create_string_buffer(1)
    szAuxInfo = ctypes.create_string_buffer(1)
    szMessage = ctypes.create_string_buffer(1)
    szLog = ctypes.create_string_buffer(1)
    c_inchi_output = InChIOutput(szInChI, szAuxInfo, szMessage, szLog)

    inchi_exit_code = MAKE_INCHI_FROM_MOLFILE_TEXT(
        c_molfile, c_inchi_options, ctypes.byref(c_inchi_output)
    )

    standard_inchi = (
        ctypes.cast(c_inchi_output.szInChI, ctypes.c_char_p)
        .value.decode("utf-8")
        .strip()
    )
    standard_log = (
        ctypes.cast(c_inchi_output.szLog, ctypes.c_char_p).value.decode("utf-8").strip()
    )
    standard_message = (
        ctypes.cast(c_inchi_output.szMessage, ctypes.c_char_p)
        .value.decode("utf-8")
        .strip()
    )
    standard_aux = (
        ctypes.cast(c_inchi_output.szAuxInfo, ctypes.c_char_p)
        .value.decode("utf-8")
        .strip()
    )

    # Deallocate memory reallocated by inchi dll
    #
    # Note the trick with None (Python's NULL) assignment to pointers
    # which have not been actually allocated (respective strings are zero-length)
    # within C library libinchi.
    # We passed Python buffer_strings casted to char *, not real pointers
    # so they could not be initialized with NULL (as they would be in C).
    # Therefore, if say szLog or szMessage were actually not used in libinchi.dll
    # and were not allocated, they should be massaged to become NULL at the end,
    # in order to avoid unnecessary/illegal freeing upon call in freeinchi().
    if not standard_inchi:
        c_inchi_output.szInChI = None
    if not standard_log:
        c_inchi_output.szLog = None
    if not standard_message:
        c_inchi_output.szMessage = None
    if not standard_aux:
        c_inchi_output.szAuxInfo = None

    FREE_INCHI(ctypes.byref(c_inchi_output))

    return inchi_exit_code, standard_inchi, standard_log, standard_message, standard_aux
