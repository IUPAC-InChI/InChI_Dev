"""`INCHI-1-SRC/INCHI_API/demos/python_sample` stripped to the essentials."""
import ctypes
from pathlib import Path


class InChIOutput(ctypes.Structure):
    # zero-terminated C-strings allocated by GetINCHI()
    # to deallocate all of them call FreeINCHI() (see below)
    _fields_ = [
        ("szInChI", ctypes.POINTER(ctypes.c_char)),
        ("szAuxInfo", ctypes.POINTER(ctypes.c_char)),
        ("szMessage", ctypes.POINTER(ctypes.c_char)),
        ("szLog", ctypes.POINTER(ctypes.c_char)),
    ]


if __name__ == "__main__":
    molfile = (
        "\n\n\n  0  0  0     0  0            999 V3000\n"
        "M  V30 BEGIN CTAB\n"
        "M  V30 COUNTS 3 2 0 0 0\n"
        "M  V30 BEGIN ATOM\n"
        "M  V30 1 H 0 0 0 0\n"
        "M  V30 2 O 0 0 0 0\n"
        "M  V30 3 H 0 0 0 0\n"
        "M  V30 END ATOM\n"
        "M  V30 BEGIN BOND\n"
        "M  V30 1 1 1 2\n"
        "M  V30 2 1 3 2\n"
        "M  V30 END BOND\n"
        "M  V30 END CTAB\n"
        "M  END"
    )
    c_molfile = ctypes.c_char_p(molfile.encode("utf-8"))

    inchi_options = "-W60"  # set max runtime to 60 seconds
    c_inchi_options = ctypes.c_char_p(inchi_options.encode("utf-8"))

    szInChI = ctypes.create_string_buffer(1)
    szAuxInfo = ctypes.create_string_buffer(1)
    szMessage = ctypes.create_string_buffer(1)
    szLog = ctypes.create_string_buffer(1)
    c_inchi_output = InChIOutput(szInChI, szAuxInfo, szMessage, szLog)

    inchi_lib_path = Path().absolute() / "libinchi.so.1"
    inchi_lib = ctypes.CDLL(inchi_lib_path)
    make_inchi_from_molfile_text = inchi_lib.MakeINCHIFromMolfileText
    free_inchi = inchi_lib.FreeINCHI

    inchi_exit_code = make_inchi_from_molfile_text(
        c_molfile, c_inchi_options, ctypes.byref(c_inchi_output)
    )

    standard_inchi = ctypes.cast(c_inchi_output.szInChI, ctypes.c_char_p).value.decode(
        "utf-8"
    )
    standard_log = (
        ctypes.cast(c_inchi_output.szLog, ctypes.c_char_p).value.decode("utf-8").strip()
    )
    standard_message = (
        ctypes.cast(c_inchi_output.szMessage, ctypes.c_char_p)
        .value.decode("utf-8")
        .strip()
    )
    standard_aux = ctypes.cast(c_inchi_output.szAuxInfo, ctypes.c_char_p).value.decode(
        "utf-8"
    )

    # Deallocate memory reallocated by inchi dll
    #
    # Note the trick with None (Python's NULL) assignment to pointers
    # which have not been actually allocated (related strings are zero-length)
    # within C library libinchi.
    # We passed Python buffer_strings casted to char *, not real pointers
    # so they could not be initialized with NULL (as they would be in C)...
    # So if say szLog or szMessage were actually not used in libinchi.dll
    # and were not allocated, they should be massaged to become NULL at the end,
    # in order to avoid unnecessary/illegal freeing upon call of freeinchi().
    if not standard_inchi:
        c_inchi_output.szInChI = None
    if not standard_log:
        c_inchi_output.szLog = None
    if not standard_message:
        c_inchi_output.szMessage = None

    free_inchi(ctypes.byref(c_inchi_output))

    print(
        f"exit code: {inchi_exit_code}\nsinchi: {standard_inchi}\nslog: {standard_log}\nsmessage: {standard_message}\nsaux: {standard_aux}"
    )
