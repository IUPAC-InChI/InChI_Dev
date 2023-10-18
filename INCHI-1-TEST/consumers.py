import ctypes
from typing import Callable
from sdf_pipeline import drivers
from .inchi_api import make_inchi_from_molfile_text, get_inchi_key_from_inchi
from .config import INCHI_API_PARAMETERS


def regression_consumer(
    molfile: str, get_molfile_id: Callable, inchi_lib: ctypes.CDLL
) -> drivers.ConsumerResult:
    _, inchi_string, _, message, aux_info = make_inchi_from_molfile_text(
        inchi_lib, molfile, INCHI_API_PARAMETERS
    )
    _, inchi_key = get_inchi_key_from_inchi(inchi_lib, inchi_string)

    return drivers.ConsumerResult(
        get_molfile_id(molfile),
        f"consumer: regression; parameters: {INCHI_API_PARAMETERS}",
        f"<inchi>: {inchi_string}\t<aux>: {aux_info}\t<key>: {inchi_key}\t<message>: {message}",
    )
