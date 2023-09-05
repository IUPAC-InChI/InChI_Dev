import ctypes
from typing import Callable
from sdf_pipeline import utils
from tests.inchi_api import make_inchi_from_molfile_text


def regression_consumer(
    molfile: str, get_molfile_id: Callable, inchi_lib: ctypes.CDLL
) -> utils.ConsumerResult:
    _, inchi_string, _, _, _ = make_inchi_from_molfile_text(
        inchi_lib, molfile, "-SNon -DoNotAddH"
    )

    return utils.ConsumerResult(
        get_molfile_id(molfile),
        utils.get_current_time(),
        "consumer: regression; parameters: '-SNon -DoNotAddH'",
        inchi_string,
    )
