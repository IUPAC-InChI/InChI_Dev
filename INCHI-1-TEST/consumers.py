import ctypes
from typing import Callable
from sdf_pipeline import utils
from .inchi_api import make_inchi_from_molfile_text, get_inchi_key_from_inchi
from .config import INCHI_API_PARAMETERS


def regression_consumer(
    molfile: str, get_molfile_id: Callable, inchi_lib: ctypes.CDLL
) -> utils.ConsumerResult:
    _, inchi_string, _, message, aux_info = make_inchi_from_molfile_text(
        inchi_lib, molfile, INCHI_API_PARAMETERS
    )
    _, inchi_key = get_inchi_key_from_inchi(inchi_lib, inchi_string)

    return utils.ConsumerResult(
        get_molfile_id(molfile),
        utils.get_current_time(),
        f"consumer: regression; parameters: {INCHI_API_PARAMETERS}",
        f"<inchi>: {inchi_string}\n<aux>: {aux_info}\n<key>: {inchi_key}\n<message>: {message}",
    )
