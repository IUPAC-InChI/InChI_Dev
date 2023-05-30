import ctypes
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

TEST_PATH: Final = Path(__file__).parent.absolute()
INCHI_LIB: Final = ctypes.CDLL(TEST_PATH.joinpath(INCHI_LIB_PATH))
INCHI_REFERENCE_LIB: Final = ctypes.CDLL(TEST_PATH.joinpath(INCHI_REFERENCE_LIB_PATH))


def _regression_consumer(
    molfile: str, get_molfile_id: Callable
) -> utils.ConsumerResult:
    _, inchi_string, _, _, _ = make_inchi_from_molfile_text(
        INCHI_LIB, molfile, "-SNon -DoNotAddH"
    )

    return utils.ConsumerResult(
        "regression",
        utils.get_current_time(),
        get_molfile_id(molfile),
        inchi_string,
    )


def _regression_reference_consumer(
    molfile: str, get_molfile_id: Callable
) -> utils.ConsumerResult:
    _, inchi_string, _, _, _ = make_inchi_from_molfile_text(
        INCHI_REFERENCE_LIB, molfile, "-SNon -DoNotAddH"
    )

    return utils.ConsumerResult(
        "regression_reference",
        utils.get_current_time(),
        get_molfile_id(molfile),
        inchi_string,
    )


if __name__ == "__main__":
    args = drivers.parse_cli_args()

    for sdf_path, log_name, get_molfile_id in zip(
        [INCHI_SDF_PATH, MCULE_SDF_PATH],
        ["inchi_regression", "mcule_regression"],
        [get_inchi_id, get_mcule_id],
    ):
        if args.test_type == "regression":
            if args.compute_reference_result:
                drivers.regression_reference(
                    sdf_path=TEST_PATH.joinpath(sdf_path),
                    log_path=TEST_PATH.joinpath("data", f"{log_name}_reference.sqlite"),
                    consumer_function=_regression_reference_consumer,
                    get_molfile_id=get_molfile_id,
                )
            else:
                drivers.regression(
                    sdf_path=TEST_PATH.joinpath(sdf_path),
                    log_path=TEST_PATH.joinpath("data", f"{log_name}.sqlite"),
                    reference_path=TEST_PATH.joinpath(
                        "data", f"{log_name}_reference.sqlite"
                    ),
                    consumer_function=_regression_consumer,
                    get_molfile_id=get_molfile_id,
                )
