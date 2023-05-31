import ctypes
from functools import partial
from pathlib import Path
from typing import Final, Callable
from inchi_api import make_inchi_from_molfile_text
from sdf_pipeline import drivers, utils
from config import (
    INCHI_LIB_PATH,
    INCHI_REFERENCE_LIB_PATH,
    INCHI_SDF_PATH,
    MCULE_SDF_PATH,
    get_inchi_id,
    get_mcule_id,
)


def _regression_consumer(
    molfile: str, get_molfile_id: Callable, inchi_lib: ctypes.CDLL
) -> utils.ConsumerResult:
    _, inchi_string, _, _, _ = make_inchi_from_molfile_text(
        inchi_lib, molfile, "-SNon -DoNotAddH"
    )

    return utils.ConsumerResult(
        "regression",
        utils.get_current_time(),
        get_molfile_id(molfile),
        inchi_string,
    )


if __name__ == "__main__":
    TEST_PATH: Final = Path(__file__).parent.absolute()

    args = drivers.parse_cli_args()

    for sdf_path, log_name, get_molfile_id in zip(
        [INCHI_SDF_PATH, MCULE_SDF_PATH],
        ["inchi_regression", "mcule_regression"],
        [get_inchi_id, get_mcule_id],
    ):
        if args.test_type == "regression":
            if args.compute_reference_result:
                INCHI_REFERENCE_LIB: Final = ctypes.CDLL(
                    TEST_PATH.joinpath(INCHI_REFERENCE_LIB_PATH)
                )

                drivers.regression_reference(
                    sdf_path=TEST_PATH.joinpath(sdf_path),
                    log_path=TEST_PATH.joinpath("data", f"{log_name}_reference.sqlite"),
                    consumer_function=partial(
                        _regression_consumer, inchi_lib=INCHI_REFERENCE_LIB
                    ),
                    get_molfile_id=get_molfile_id,
                )
            else:
                INCHI_LIB: Final = ctypes.CDLL(TEST_PATH.joinpath(INCHI_LIB_PATH))

                drivers.regression(
                    sdf_path=TEST_PATH.joinpath(sdf_path),
                    log_path=TEST_PATH.joinpath("data", f"{log_name}.sqlite"),
                    reference_path=TEST_PATH.joinpath(
                        "data", f"{log_name}_reference.sqlite"
                    ),
                    consumer_function=partial(
                        _regression_consumer, inchi_lib=INCHI_LIB
                    ),
                    get_molfile_id=get_molfile_id,
                )
